#include "Car_Animation.h"

Car_Animation::Car_Animation(){}

Car_Animation::~Car_Animation(){}

void Car_Animation::init() {
	position = { 0.0f, 0.0f, 0.0f };
	scale = { 1.0f, 1.0f, 1.0f };
	rotation = { 0.0f, 0.0f, 0.0f };
	
}

void Car_Animation::move_car(int direction, float delta_time, Camera* m_camera, Wheel_Animation* m_wheel_animation) {
	
	glm::vec3 rotation_mat = glm::vec3(-sin(glm::radians(m_wheel_animation->rotation_vector[0].y)), 0, -cos(glm::radians(m_wheel_animation->rotation_vector[0].y)));
	if(glm::length(rotation_mat) != 0)
		rotation_mat = rotation_mat / glm::length(rotation_mat);

	glm::vec3 front_traction = rotation_mat * engine_force;
	glm::vec3 braking_force = rotation_mat * 4000.0f;
	glm::vec3 right_traction = glm::vec3(1, 0, 0) * engine_force;
	glm::vec3 drag_force;
	float speed = glm::length(velocity);
	drag_force.z = -aero_drag * velocity.z * speed;
	drag_force.x = -aero_drag * velocity.x * speed;
	glm::vec3 roll_force = -roll_res * velocity;
	
	glm::vec3 long_force;
	glm::vec3 accel;
	float dir;

	switch (direction)
	{
		case FORWARD:
			long_force = front_traction + drag_force + roll_force;
			accel = long_force / mass;
			velocity = velocity + (10 * delta_time * accel);
			//std::cout << velocity.z << "  " << accel.z << "\n";
			position = position + (delta_time * velocity);
			m_wheel_animation->rotateWheelsByVelocity(velocity, 1);
			m_camera->move_camera(delta_time * velocity);
			has_updated = true;
			break;
		case BACKWARD:
			long_force = -front_traction + drag_force + roll_force;
			accel = long_force / mass;
			velocity = velocity + (10 * delta_time * accel);
			//std::cout << velocity.z << "  " << accel.z << "\n";
			m_wheel_animation->rotateWheelsByVelocity(velocity, -1);
			position = position + (delta_time * velocity);
			m_camera->move_camera(delta_time * velocity);
			has_updated = true;
			break;
		case BRAKE:
			if (glm::length(velocity) == 0)
				break;
			dir = glm::dot(rotation_mat, velocity) / (glm::length(rotation_mat) * glm::length(velocity));
			std::cout << dir << " ";
			if (dir == 1) {
				long_force = -braking_force + drag_force + roll_force;
				accel = long_force / mass;
				velocity = velocity + (10 * delta_time * accel);
				if ((int)(glm::dot(rotation_mat, velocity) / (glm::length(rotation_mat) * glm::length(velocity))) == -1) {
					velocity = { 0, 0, 0 };
				}
			}
			else if(dir == -1) {
				long_force = braking_force + drag_force + roll_force;
				accel = long_force / mass;
				velocity = velocity + (10 * delta_time * accel);
				if ((int)(glm::dot(rotation_mat, velocity) / (glm::length(rotation_mat) * glm::length(velocity))) == 1) {
					velocity = { 0, 0, 0 };
				}
			}
			else if (dir == 0) {
				velocity = { 0, 0, 0 };
			}
			std::cout << glm::to_string(velocity) << '\n';
			position = position + (delta_time * velocity);
			m_camera->move_camera(delta_time * velocity);
			break;
		case LEFT:
			if (m_wheel_animation->rotation_vector[0].y != 35) {

				m_wheel_animation->rotation_vector[0].y += delta_time * 70;
				m_wheel_animation->rotation_vector[1].y += delta_time * 70;
				if (m_wheel_animation->rotation_vector[0].y > 35) {
					m_wheel_animation->rotation_vector[0].y = 35;
					m_wheel_animation->rotation_vector[1].y = 215;
				}
			}

			if (has_updated == false) {
				long_force = drag_force + roll_force;
				accel = long_force / mass;
				velocity = (velocity + (10 * delta_time * accel));
				velocity = rotation_mat * (glm::dot(velocity, rotation_mat) / (pow(glm::length(rotation_mat), 2)));
				dir = glm::dot(rotation_mat, velocity) / (glm::length(rotation_mat) * glm::length(velocity));
				
				if (dir > 0) {
					for (int i = 0; i < 4; i++)
						m_wheel_animation->rotation_vector[i].x -= glm::length(velocity) / 2;
				}
				else if (dir < -0) {
					for (int i = 0; i < 4; i++)
						m_wheel_animation->rotation_vector[i].x += glm::length(velocity) / 2;
				}
				position = position + (delta_time * velocity);
				m_camera->move_camera(delta_time * velocity);
			}

			has_updated = true;
			break;
		case RIGHT:
			if (m_wheel_animation->rotation_vector[0].y != -35) {
				m_wheel_animation->rotation_vector[0].y -= delta_time * 70;
				m_wheel_animation->rotation_vector[1].y -= delta_time * 70;
				if (m_wheel_animation->rotation_vector[0].y < -35) {
					m_wheel_animation->rotation_vector[0].y = -35;
					m_wheel_animation->rotation_vector[1].y = 145;
				}
			}

			if (has_updated == false) {
				long_force = drag_force + roll_force;
				accel = long_force / mass;
				velocity = (velocity + (10 * delta_time * accel));
				velocity = rotation_mat * (glm::dot(velocity, rotation_mat) / (pow(glm::length(rotation_mat), 2)));
				dir = glm::dot(rotation_mat, velocity) / (glm::length(rotation_mat) * glm::length(velocity));
				//	std::cout << glm::to_string(velocity) << "  " << accel.z << " " << dir << "\n";
				if (dir > 0) {
					for (int i = 0; i < 4; i++)
						m_wheel_animation->rotation_vector[i].x -= glm::length(velocity) / 2;
				}
				else if (dir < -0) {
					for (int i = 0; i < 4; i++)
						m_wheel_animation->rotation_vector[i].x += glm::length(velocity) / 2;
				}
				position = position + (delta_time * velocity);
				m_camera->move_camera(delta_time * velocity);
			}
			has_updated = true;
			break;
		case NONE:
			if (glm::length(velocity) == 0)
				break;

			long_force = drag_force + roll_force;
			accel = long_force / mass;
			velocity = (velocity + (10 * delta_time * accel));
			velocity = rotation_mat*(glm::dot(velocity, rotation_mat) / (pow(glm::length(rotation_mat), 2)));
			dir = glm::dot(rotation_mat, velocity) / (glm::length(rotation_mat) * glm::length(velocity));
		//	std::cout << glm::to_string(velocity) << "  " << accel.z << " " << dir << "\n";
			if (dir > 0) {
				for (int i = 0; i < 4; i++)
					m_wheel_animation->rotation_vector[i].x -= glm::length(velocity) / 2;
			}
			else if (dir < -0) {
				for (int i = 0; i < 4; i++)
					m_wheel_animation->rotation_vector[i].x += glm::length(velocity) / 2;
			}
			position = position + (delta_time * velocity );
			m_camera->move_camera(delta_time * velocity);
			break;
		default:
			break;
	}
	std::cout << glm::to_string(velocity) << "  " << accel.z << " " << dir << " " << glm::to_string(position) << "\n";
	
}

void Car_Animation::reset(){}

void Car_Animation::update(float delta_time, Camera* m_camera) {
	//position = position + (delta_time * velocity);
	
	//m_camera->move_camera(delta_time * velocity);
};