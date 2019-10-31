#pragma once

#include<vector>

#define GLM_ENABLE_EXPERIMENTAL
#include <glm/glm.hpp>
#include <glm/gtc/matrix_transform.hpp>
#include <glm/gtc/type_ptr.hpp>	
#include <glm/gtx/quaternion.hpp>

class Wheel_Animation
{
public:
	Wheel_Animation();
	~Wheel_Animation();

	void init();
	void update(float delta_time);

	glm::vec3 scale;

	std::vector<glm::vec3> position_vector;
	std::vector<glm::vec3> rotation_vector;
};

