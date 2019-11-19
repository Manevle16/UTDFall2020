#pragma once

#include <algorithm> 

#define GLM_ENABLE_EXPERIMENTAL
#include <GL/glew.h>
#include <glm/glm.hpp>
#include <glm/gtc/matrix_transform.hpp>

class Camera {
public:
	// Camera view parameters
	glm::vec3 ori_position;
	glm::vec3 ori_front;
	glm::vec3 ori_up;
	glm::vec3 ori_right;

	glm::vec3 position;
	glm::vec3 front;
	glm::vec3 up;
	glm::vec3 right;

	// Camera projection parameters
	float ori_zoom;
	float zoom;

	float near;
	float far;

	unsigned int width;
	unsigned int height;

	// Camera projection matrix: used for projection
	glm::mat4 proj_mat;

	// Camera view matrix: used for changing camera rotation and position
	glm::mat4 view_mat;

	// Camera parameter initialization
	Camera(
		glm::vec3 position_ = glm::vec3(0, 3, 10),
		glm::vec3 front_ = glm::vec3(0, 0, -1),
		glm::vec3 up_ = glm::vec3(0, 1, 0),
		glm::vec3 right_ = glm::vec3(1, 0, 0),
		float zoom_ = 45.0,
		float near_ = 0.1,
		float far_ = 100,
		unsigned int width_ = 1600,
		unsigned int height_ = 900
		)
	{
		this->ori_position = position_;
		this->ori_front = front_;
		this->ori_up = up_;
		this->ori_right = right_;
		this->ori_zoom = zoom_;
		this->near = near_;
		this->far = far_;
		this->width = width_;
		this->height = height_;
	}

	void init() {
		reset();
	};

	void reset() {
		this->position = ori_position;

		this->front = ori_front;
		this->up = ori_up;
		this->right = ori_right;
		this->zoom = ori_zoom;
	//	rotate_y(-90);
	}

	

	void move_camera(glm::vec3 movement) {
		this->position += movement;
	}

	// Rotate specific angle along local camera system(LCS)
	void rotate_x(float angle) 
	{
		glm::vec3 up = this->up;
		glm::mat4 rotation_mat(1);
		rotation_mat = glm::rotate(rotation_mat, glm::radians(angle), this->right);
		this->up = glm::normalize(glm::vec3(rotation_mat * glm::vec4(up, 1.0)));
		this->front = glm::normalize(glm::cross(this->up, this->right));
	}

	void rotate_y(float angle) 
	{
		glm::vec3 front = this->front;
		glm::mat4 rotation_mat(1);
		rotation_mat = glm::rotate(rotation_mat, glm::radians(angle), this->up);
		this->front = glm::normalize(glm::vec3(rotation_mat * glm::vec4(front, 1.0)));
		this->right = glm::normalize(glm::cross(this->front, this->up));
	}

	void rotate_z(float angle) 
	{
		glm::vec3 right = this->right;
		glm::mat4 rotation_mat(1);
		rotation_mat = glm::rotate(rotation_mat, glm::radians(angle), this->front);
		this->right = glm::normalize(glm::vec3(rotation_mat * glm::vec4(right, 1.0)));
		this->up = glm::normalize(glm::cross(this->right, this->front));
	}

	// Get camera view matrix
	glm::mat4 get_view_mat()
	{
		this->view_mat = glm::lookAt(this->position, this->position + this->front, this->up);
		return this->view_mat;
	}

	// Get camera projection matrix
	glm::mat4 get_projection_mat()
	{
		this->proj_mat = glm::perspective(this->zoom, (float)this->width / (float)this->height, this->near, this->far);
		return this->proj_mat;
	}
};