#pragma once

#include <vector>
#include <iostream>

#define GLM_ENABLE_EXPERIMENTAL
#include <glm/glm.hpp>
#include <glm/gtc/matrix_transform.hpp>
#include <glm/gtc/type_ptr.hpp>
#include <glm/gtx/string_cast.hpp>
#include <cmath>
#include <glm/gtx/quaternion.hpp>

#include "Curve.h"

class Aircraft_Animation
{

public:
	float total_moving_time = 10;
	float t1 = .1;
	float t2 = .9;
	float total_time_elapsed;
	float current_velocity;
	float dist_traveled;
	float current_index;
	bool isMoving = false;
	
private:
	glm::mat4 m_model_mat;
	Curve* m_animation_curve = nullptr;
	float ease(float t);
	glm::quat slerp(glm::quat q1, glm::quat q2, float u);

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

