#pragma once

#include <vector>
#include <iostream>

#define GLM_ENABLE_EXPERIMENTAL
#include <glm/glm.hpp>
#include <glm/gtc/matrix_transform.hpp>
#include <glm/gtc/type_ptr.hpp>

#include "Curve.h"

class Aircraft_Animation
{

public:
	float total_moving_time;
	float t1;
	float t2;
	float total_time_elapsed = 0;
	float current_velocity = 0;
	float dist_traveled = 0;
	bool isMoving = false;
	
private:
	glm::mat4 m_model_mat;
	Curve* m_animation_curve = nullptr;
	float ease(float t);

public:
	Aircraft_Animation();
	~Aircraft_Animation();

	void init();
	void init(Curve* animation_curve);

	void moveAircraft();
	void update(float delta_time);

	void reset();
	glm::mat4 get_model_mat() { return m_model_mat; };
};

