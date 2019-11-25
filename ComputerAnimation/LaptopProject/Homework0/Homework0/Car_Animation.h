#pragma once

#include <iostream>

#define GLM_ENABLE_EXPERIMENTAL
#include <glm/glm.hpp>
#include <glm/gtc/matrix_transform.hpp>
#include <glm/gtc/type_ptr.hpp>	
#include <glm/gtx/quaternion.hpp>
#include <glm/gtx/string_cast.hpp>
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
	void move_car(int direction, double delta_time, Wheel_Animation* m_wheel_animation);
	void update(float delta_time);
	void rotate_car(float angle, float delta_time, Wheel_Animation* m_wheel_animation);

	bool has_updated = false;
	const double mass = 2689.6;
	const double engine_force = 2000;
	const double aero_drag = .34;
	const double roll_res = 8.1;
	glm::dvec3 velocity = { 0.0, 0.0, 0.0 };

	glm::dvec3 position;
	glm::dvec3 scale;
	glm::dvec3 rotation;

	
};

