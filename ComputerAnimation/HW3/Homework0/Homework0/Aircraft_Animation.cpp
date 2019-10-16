#include "Aircraft_Animation.h"
#include<cmath>


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
		this->total_time_elapsed += delta_time;
		float s = ease(delta_time);
		this->dist_traveled += s;
		float norm_dist = this->dist_traveled / m_animation_curve->total_segment_length;
		
		for (int i = 1; i < m_animation_curve->segment_length.size(); i++) {
			if (i == m_animation_curve->segment_length.size() - 1 && norm_dist >= m_animation_curve->segment_length[1]) {
				glm::translate(glm::mat4(1.0f), m_animation_curve->curve_points_pos[0]);
				this->isMoving = false;
				this->total_time_elapsed = 0;
				this->dist_traveled = 0;
				this->current_velocity = 0;
				break;
			}

			else if(norm_dist >= m_animation_curve->segment_length[i] && norm_dist <= m_animation_curve->segment_length[i+1]) {
				m_model_mat = glm::translate(glm::mat4(1.0f), m_animation_curve->curve_points_pos[i]);
				break;
			}
			else if (norm_dist < m_animation_curve->segment_length[0]) {
				break;
			}
		}
	}
}

float Aircraft_Animation::ease(float t) {
	float time_norm = this->total_time_elapsed / this->total_moving_time;
	float stop_acc_dist = m_animation_curve->total_segment_length * t1;
	float start_dec_dist = m_animation_curve->total_segment_length * (1 - t2);

	if (time_norm < this->t1) {	
		float acc = 2*(stop_acc_dist) / pow(this->t1*this->total_moving_time, 2);
		float s = current_velocity * t + .5 * acc * pow(t, 2);
		this->current_velocity = this->current_velocity + acc * t;
		std::cout << "s " << v << "\n";
		return s;
	}
	else if (time_norm > 1 - this->t2 && time_norm <= 1) {
		float dec = -2 * (m_animation_curve->total_segment_length - start_dec_dist) / pow(this->t2 * this->total_moving_time, 2);
		float s = current_velocity * t + .5 * dec * pow(t, 2);
		this->current_velocity = this->current_velocity + dec * t;
		std::cout << "e " << current_velocity << "\n";
		return s;
	}
	else if (time_norm >= this->t1 && time_norm <= 1 - this->t2) {
		float v = (start_dec_dist - stop_acc_dist) / ((1 - (this->t2 + this->t1)) * this->total_moving_time);
		float s = v * t;
		std::cout << "m " << v << "\n";
		return s;
	}
}

void Aircraft_Animation::reset()
{
	m_model_mat = glm::mat4(1.0f);

	this->t1 = .1;
	this->t2 = .9;
	this->total_moving_time = 10;
	this->isMoving = false;
	this->total_time_elapsed = 0;
	this->dist_traveled = 0;
	this->current_velocity = 0;

	if (m_animation_curve != nullptr && m_animation_curve->control_points_pos.size() > 0)
	{
		m_model_mat = glm::translate(m_model_mat, m_animation_curve->control_points_pos[0]);
	}
}

void Aircraft_Animation::moveAircraft()
{

}
