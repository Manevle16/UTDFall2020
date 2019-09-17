#pragma once

#include <iostream>

#include <glm/glm.hpp>
#include <glm/gtc/matrix_transform.hpp>
#include <glm/gtc/type_ptr.hpp>

class Animation
{
public:

	Animation();
	~Animation();

	void init();
	void update(float delta_time);

	void reset();
	glm::mat4 get_model_mat() { return m_model_mat; };
	float m_angles[2] = { 45, 45 };

	void rotateX(const float alpha) {
		m_model_mat = glm::rotate(m_model_mat, glm::radians(alpha), glm::vec3(1.0, 0.0, 0.0));
	}

	void rotateY(const float alpha) {
		glm::mat4 rotationMatrix = glm::rotate(glm::mat4(1.0f), glm::radians(alpha), glm::vec3(0.0, 1.0, 0.0));
		m_model_mat = rotationMatrix * m_model_mat;
	}

private:
	glm::mat4 m_model_mat;
};

