#include "Car_Animation.h"

Car_Animation::Car_Animation(){}

Car_Animation::~Car_Animation(){}

void Car_Animation::init() {
	position = { 0.0f, 0.0f, 0.0f };
	scale = { 1.0f, 1.0f, 1.0f };
	rotation = { 0, -90.0f, 0.0f };
	
}

void Car_Animation::move_car(int direction, float delta_time, Camera* m_camera) {
	
	glm::vec3 rotation_mat = glm::vec3(-rotation.y, 0, 0);
	if(glm::length(rotation_mat) != 0)
		rotation_mat = rotation_mat / glm::length(rotation_mat);

	std::cout << glm::to_string(rotation_mat) << '\n';
	glm::vec3 front_traction = rotation_mat * engine_force;
	glm::vec3 right_traction = glm::vec3(1, 0, 0) * engine_force;
	glm::vec3 drag_force;
	float speed = glm::length(velocity);
	drag_force.z = -aero_drag * velocity.z * speed;
	drag_force.x = -aero_drag * velocity.x * speed;
	glm::vec3 roll_force = -roll_res * velocity;
	
	glm::vec3 long_force;
	glm::vec3 accel;
	switch (direction)
	{
		case FORWARD:
			long_force = front_traction + drag_force + roll_force;
			accel = long_force / mass;
			velocity = velocity + (10 * delta_time * accel);
			std::cout << velocity.z << "  " << accel.z << "\n";
			position = position + (delta_time * velocity);
			m_camera->move_camera(delta_time * velocity);
			break;
		case BACKWARD:
			long_force = -front_traction + drag_force + roll_force;
			accel = long_force / mass;
			velocity = velocity + (10 * delta_time * accel);
			std::cout << velocity.z << "  " << accel.z << "\n";
			position = position + (delta_time * velocity);
			m_camera->move_camera(delta_time * velocity);
			break;
		case BRAKE:
			if (velocity.z > 0) {
				long_force = front_traction + drag_force + roll_force;
				accel = long_force / mass;
				velocity = velocity + (10 * delta_time * accel);
				if (velocity.z < 0) {
					velocity.z = 0;
				}
			}
			else if (velocity.z < 0) {
				long_force = -front_traction + drag_force + roll_force;
				accel = long_force / mass;
				velocity = velocity + (10 * delta_time * accel);
				if (velocity.z > 0) {
					velocity.z = 0;
				}
			}
			
			std::cout << velocity.z << "  " << accel.z << "\n";
			position = position + (delta_time * velocity);
			m_camera->move_camera(delta_time * velocity);
			break;
		case NONE:
			long_force = glm::vec3(0, 0, 0) + drag_force + roll_force;
			accel = long_force / mass;
			velocity = velocity + (10 * delta_time * accel);
			std::cout << velocity.z << "  " << accel.z << "\n";
			position = position + (delta_time * velocity);
			m_camera->move_camera(delta_time * velocity);
			break;
		default:
			break;
	}
	
}

void Car_Animation::reset(){}

void Car_Animation::update(float delta_time, Camera* m_camera) {
	position = position + (delta_time * velocity);
	m_camera->move_camera(delta_time * velocity);
};