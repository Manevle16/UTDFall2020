#include "Car_Animation.h"

Car_Animation::Car_Animation(){}

Car_Animation::~Car_Animation(){}

void Car_Animation::init() {
	position = { 0.0, 0.0, 0.0 };
	scale = { 1.0, 1.0, 1.0 };
	rotation = { 0.0, 0.0, 0.0 };
	
}

void Car_Animation::move_car(int direction, double delta_time, Wheel_Animation* m_wheel_animation) {
	
	glm::dvec3 car_rotation_mat = glm::dvec3(-sin(glm::radians(rotation.y)), 0, -cos(glm::radians(rotation.y)));
	glm::dvec3 wheel_rotation_mat = glm::dvec3(-sin(glm::radians(m_wheel_animation->rotation_vector[0].y + rotation.y)), 0, -cos(glm::radians(m_wheel_animation->rotation_vector[0].y + rotation.y)));
	if(glm::length(wheel_rotation_mat) != 0)
		wheel_rotation_mat = wheel_rotation_mat / glm::length(wheel_rotation_mat);
	glm::dvec3 velocity_dir(velocity / glm::length(velocity));

	glm::dvec3 front_traction = wheel_rotation_mat * engine_force;
	glm::dvec3 braking_force = velocity_dir * 4000.0;
	glm::dvec3 right_traction = glm::dvec3(1, 0, 0) * engine_force;
	glm::dvec3 drag_force;
	double speed = glm::length(velocity);
	drag_force.z = -aero_drag * velocity.z * speed;
	drag_force.x = -aero_drag * velocity.x * speed;
	glm::dvec3 roll_force = -roll_res * velocity;
	
	glm::dvec3 long_force;
	glm::dvec3 accel;
	float dir;

	switch (direction)
	{
		case FORWARD:
			long_force = front_traction + drag_force + roll_force;
			accel = long_force / mass;
			velocity = velocity + (10 * delta_time * accel);
			velocity = wheel_rotation_mat * (glm::dot(velocity, wheel_rotation_mat) / (pow(glm::length(wheel_rotation_mat), 2)));
			rotate_car(m_wheel_animation->rotation_vector[0].y, delta_time, m_wheel_animation);
			//std::cout << glm::to_string(velocity) << "\n";
			position = position + (delta_time * velocity);
			m_wheel_animation->rotateWheelsByVelocity(velocity, 1);
			has_updated = true;
			break;
		case BACKWARD:
			long_force = -front_traction + drag_force + roll_force;
			accel = long_force / mass;
			velocity = velocity + (10 * delta_time * accel);
			velocity = wheel_rotation_mat * (glm::dot(velocity, wheel_rotation_mat) / (pow(glm::length(wheel_rotation_mat), 2)));
			//std::cout << velocity.z << "  " << accel.z << "\n";
			rotate_car(m_wheel_animation->rotation_vector[0].y, delta_time, m_wheel_animation);
			m_wheel_animation->rotateWheelsByVelocity(velocity, -1);
			position = position + (delta_time * velocity);
			has_updated = true;
			break;
		case BRAKE: {
			if (glm::length(velocity) == 0)
				break;
			dir = glm::dot(wheel_rotation_mat, velocity) / (glm::length(wheel_rotation_mat) * glm::length(velocity));
			long_force = -braking_force + drag_force + roll_force;
			accel = long_force / mass;
			glm::dvec3 temp = velocity;
			velocity = velocity + (10 * delta_time * accel);

			if (signbit(temp.x) != signbit(velocity.x)) {
				velocity.x = 0;
			}

			if (signbit(temp.z) != signbit(velocity.z)) {
				velocity.z = 0;
			}

			std::cout << glm::to_string(velocity) << " " << glm::to_string(accel) << "\n";
			rotate_car(m_wheel_animation->rotation_vector[0].y, delta_time, m_wheel_animation);

			position = position + (delta_time * velocity);
			break;
		}
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
				velocity = wheel_rotation_mat * (glm::dot(velocity, wheel_rotation_mat) / (pow(glm::length(wheel_rotation_mat), 2)));
				dir = glm::dot(wheel_rotation_mat, velocity) / (glm::length(wheel_rotation_mat) * glm::length(velocity));
				
				if (dir > 0) {
					for (int i = 0; i < 4; i++)
						m_wheel_animation->rotation_vector[i].x -= glm::length(velocity) / 2;
				}
				else if (dir < -0) {
					for (int i = 0; i < 4; i++)
						m_wheel_animation->rotation_vector[i].x += glm::length(velocity) / 2;
				}
				rotate_car(m_wheel_animation->rotation_vector[0].y, delta_time, m_wheel_animation);
				position = position + (delta_time * velocity);
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
				velocity = wheel_rotation_mat * (glm::dot(velocity, wheel_rotation_mat) / (pow(glm::length(wheel_rotation_mat), 2)));
				dir = glm::dot(wheel_rotation_mat, velocity) / (glm::length(wheel_rotation_mat) * glm::length(velocity));
				//	std::cout << glm::to_string(velocity) << "  " << accel.z << " " << dir << "\n";
				if (dir > 0) {
					for (int i = 0; i < 4; i++)
						m_wheel_animation->rotation_vector[i].x -= glm::length(velocity) / 2;
				}
				else if (dir < -0) {
					for (int i = 0; i < 4; i++)
						m_wheel_animation->rotation_vector[i].x += glm::length(velocity) / 2;
				}
				rotate_car(m_wheel_animation->rotation_vector[0].y, delta_time, m_wheel_animation);
				position = position + (delta_time * velocity);
			}
			has_updated = true;
			break;
			
		case NONE:
			if (glm::length(velocity) == 0)
				break;

			long_force = drag_force + roll_force;
			accel = long_force / mass;
			velocity = (velocity + (10 * delta_time * accel));
			velocity = wheel_rotation_mat*(glm::dot(velocity, wheel_rotation_mat) / (pow(glm::length(wheel_rotation_mat), 2)));
			dir = glm::dot(wheel_rotation_mat, velocity) / (glm::length(wheel_rotation_mat) * glm::length(velocity));
			//std::cout << glm::to_string(velocity) << "\n";
			if (dir > 0) {
				for (int i = 0; i < 4; i++)
					m_wheel_animation->rotation_vector[i].x -= glm::length(velocity) / 2;

			}
			else if (dir < 0) {
				for (int i = 0; i < 4; i++)
					m_wheel_animation->rotation_vector[i].x += glm::length(velocity) / 2;
			}
			rotate_car(m_wheel_animation->rotation_vector[0].y, delta_time, m_wheel_animation);
			position = position + (delta_time * velocity );
			break;
			
		default:
			break;
	}
	//std::cout << glm::to_string(velocity) << "  " << accel.z << " " << dir << " " << glm::to_string(position) << "\n";
	
}

void Car_Animation::reset(){}

void Car_Animation::update(float delta_time) {
	//position = position + (delta_time * velocity);
	
	//m_camera->move_camera(delta_time * velocity);
};

void Car_Animation::rotate_car(float angle, float delta_time, Wheel_Animation* m_wheel_animation) {
	glm::dvec3 wheel_rotation_mat = glm::dvec3(-sin(glm::radians(m_wheel_animation->rotation_vector[0].y + rotation.y)), 0, -cos(glm::radians(m_wheel_animation->rotation_vector[0].y + rotation.y)));
	if (glm::length(wheel_rotation_mat) != 0)
		wheel_rotation_mat = wheel_rotation_mat / glm::length(wheel_rotation_mat);
	float dir = glm::dot(wheel_rotation_mat, velocity) / (glm::length(wheel_rotation_mat) * glm::length(velocity));
	if(dir > 0)
		rotation.y += (angle * delta_time * sqrt(glm::length(velocity)));
	else
		rotation.y -= (angle * delta_time * sqrt(glm::length(velocity)));
}