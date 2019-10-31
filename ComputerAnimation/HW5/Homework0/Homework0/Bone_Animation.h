#pragma once

#include <string>
#include <vector>
#include <iostream>
#include <algorithm>

#define GLM_ENABLE_EXPERIMENTAL
#include <glm/glm.hpp>
#include <glm/gtc/matrix_transform.hpp>
#include <glm/gtc/type_ptr.hpp>	
#include <glm/gtx/quaternion.hpp>

class Bone_Animation
{
public:
	Bone_Animation();
	~Bone_Animation();

	void init();
	void update(float delta_time);
	void reset();

public:

	// Here the head of each vector is the root bone
	std::vector<glm::vec3> position_vector;
	std::vector<glm::vec3> scale_vector;
	std::vector<glm::vec3> rotation_degree_vector;
	std::vector<glm::vec4> colors;

	glm::vec3 root_position;
	glm::mat4 rotate_bone(glm::mat4 bone, glm::vec3 rotate_vec);

};

