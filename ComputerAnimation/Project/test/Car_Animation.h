#pragma once

#include <iostream>

#define GLM_ENABLE_EXPERIMENTAL
#include <glm/glm.hpp>
#include <glm/gtc/matrix_transform.hpp>
#include <glm/gtc/type_ptr.hpp>	
#include <glm/gtx/quaternion.hpp>
#include <glm/gtx/string_cast.hpp>
#include "Camera.h";
#include "Wheel_Animation.h";

enum Car_Movement {
	FORWARD,
	BACKWARD,
	LEFT,
	RIGHT,
	BRAKE,
	NONE
};

class Car_Animation
{
public:
	Car_Animation();
	~Car_Animation();

	void init();
	void reset();
	void move_car(int direction, float delta_time, Camera* m_camera, Wheel_Animation* m_wheel_animation);
	void update(float delta_time, Camera* m_camera);

	const float mass = 2689.6;
	const float engine_force = 2000;
	const float aero_drag = .34;
	const float roll_res = 8.1;
	glm::vec3 velocity = { 0.0f, 0.0f, 0.0f };

	glm::vec3 position;
	glm::vec3 scale;
	glm::vec3 rotation;

	
};

