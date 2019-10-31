#pragma once

#define GLM_ENABLE_EXPERIMENTAL
#include <glm/glm.hpp>
#include <glm/gtc/matrix_transform.hpp>
#include <glm/gtc/type_ptr.hpp>	
#include <glm/gtx/quaternion.hpp>

class Car_Animation
{
public:
	Car_Animation();
	~Car_Animation();

	void init();
	void reset();
	void update(float delta_time);

	glm::vec3 position;
	glm::vec3 scale;
	glm::vec3 rotation;
};

