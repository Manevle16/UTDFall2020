#include "Aircraft_Animation.h"


Aircraft_Animation::Aircraft_Animation()
{
	this->m_model_mat = glm::mat4(1.0f);
}


Aircraft_Animation::~Aircraft_Animation()
{
}

void Aircraft_Animation::init()
{
	reset();
}

void Aircraft_Animation::init(Curve* animation_curve)
{
	m_animation_curve = animation_curve;
	reset();
}

void Aircraft_Animation::update(float delta_time)
{
	if (this->isMoving) {

		if (this->current_index == -1) {
			this->isMoving = false;
			this->total_time_elapsed = 0;
			this->dist_traveled = 0;
			this->current_velocity = 0;
			this->current_index = 0;
			m_model_mat = glm::translate(glm::mat4(1.0f), m_animation_curve->control_points_pos[0]);
			return;
		}

		this->total_time_elapsed += delta_time;
		float s = ease(delta_time);
		this->dist_traveled += s;
		float norm_dist = this->dist_traveled / m_animation_curve->total_segment_length;
		glm::vec3 translateMatrix = { 1, 1, 1 };
		

		for (int i = this->current_index; i < m_animation_curve->segment_length.size(); i++) {
			if ((i == m_animation_curve->segment_length.size() - 1 && norm_dist >= m_animation_curve->segment_length[1]) || s <= 0) {
				translateMatrix = m_animation_curve->curve_points_pos[i];
				this->current_index = -1;
				break;
			}

			else if (norm_dist >= m_animation_curve->segment_length[i] && norm_dist <= m_animation_curve->segment_length[i + 1]) {
				translateMatrix = m_animation_curve->curve_points_pos[i];
				this->current_index = i;
				break;
			}
			else if (norm_dist < m_animation_curve->segment_length[0]) {
				return;
			}
		}

		glm::quat q;
		for (int i = 0; i < m_animation_curve->control_points_length.size(); i++) {
			if (norm_dist > m_animation_curve->control_points_length[m_animation_curve->control_points_length.size() - 1]) {
				float u = (norm_dist - m_animation_curve->control_points_length[m_animation_curve->control_points_length.size() - 1]) /
					( 1 - m_animation_curve->control_points_length[m_animation_curve->control_points_length.size() - 1]);
				q = slerp(m_animation_curve->control_points_quaternion[m_animation_curve->control_points_quaternion.size() - 1], m_animation_curve->control_points_quaternion[0], u);
				break;

			}
			else if (norm_dist < m_animation_curve->control_points_length[1]) {
				float u = norm_dist / (m_animation_curve->control_points_length[1]);
				q = slerp(m_animation_curve->control_points_quaternion[0], m_animation_curve->control_points_quaternion[1], u);
				
				break;
			}
			else if (norm_dist >= m_animation_curve->control_points_length[i] && norm_dist <= m_animation_curve->control_points_length[i+1]){
				float u = (norm_dist - m_animation_curve->control_points_length[i]) / (m_animation_curve->control_points_length[i+1] - m_animation_curve->control_points_length[i]);
				q = slerp(m_animation_curve->control_points_quaternion[i], m_animation_curve->control_points_quaternion[i+1], u);
				break;
			}
		}
		glm::mat4 temp = glm::translate(glm::mat4(1.0f), translateMatrix);
		glm::mat4 rotateMatrix = glm::toMat4(q);
		m_model_mat = temp * rotateMatrix;
	}
}

float Aircraft_Animation::ease(float t) {
	float time_norm = this->total_time_elapsed / this->total_moving_time;
	float stop_acc_dist = m_animation_curve->total_segment_length * t1;
	float start_dec_dist = m_animation_curve->total_segment_length * t2;
	float v_max = m_animation_curve->total_segment_length / (this->total_moving_time - ((this->t1 * this->total_moving_time) / 2) -
		((this->total_moving_time - (this->t2 * this->total_moving_time)) / 2));

	if (time_norm < this->t1) {
		float acc = v_max / (this->t1 * this->total_moving_time);
		float s = current_velocity * t + .5 * acc * pow(t, 2);
		this->current_velocity = this->current_velocity + acc * t;
		return s;
	}
	else if (time_norm > this->t2) {
		float dec = -v_max / (this->total_moving_time - (this->t2 * this->total_moving_time));
		float s = current_velocity * t + .5 * dec * pow(t, 2);
		this->current_velocity = this->current_velocity + dec * t;
		if (s <= 0) {
			return 0.0009;
		}
		return s;
	}
	else if (time_norm >= this->t1 && time_norm <= this->t2) {
		float s = v_max * t;
		return s;
	}
}

glm::quat Aircraft_Animation::slerp(glm::quat q1, glm::quat q2, float u) {
	float dot = glm::dot(q1, q2);
	float theta = acos(dot);
	return glm::normalize((q1 * (sin(1 - u) * theta) + (q2 * sin(u * theta))) / sin(theta));
}

void Aircraft_Animation::reset()
{
	this->m_model_mat = glm::mat4(1.0f);
	this->isMoving = false;
	this->total_time_elapsed = 0;
	this->dist_traveled = 0;
	this->current_velocity = 0;
	this->current_index = 0;

	if (m_animation_curve != nullptr && m_animation_curve->control_points_pos.size() > 0)
	{
		m_model_mat = glm::translate(m_model_mat, m_animation_curve->control_points_pos[0]);
		m_model_mat = m_model_mat*glm::toMat4(m_animation_curve->control_points_quaternion[0]);
	}
}

void Aircraft_Animation::moveAircraft()
{

}
