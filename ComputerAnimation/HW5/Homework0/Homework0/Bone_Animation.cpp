#include "Bone_Animation.h"



Bone_Animation::Bone_Animation()
{
}


Bone_Animation::~Bone_Animation()
{
}

void Bone_Animation::init()
{
	root_position = { 2.0f,1.0f,2.0f };

	position_vector = {
		{ 2.0f, 1.0f, 2.0f },
		{ 2.0f, 3.5f, 2.0f },
		{ 2.0f, 7.0f, 2.0f },
		{ 2.0f, 9.5f, 2.0f }
	};

	scale_vector =
	{
		{1.0f,1.0f,1.0f},
		{0.5f,4.0f,0.5f},
		{0.5f,3.0f,0.5f},
		{0.5f,2.0f,0.5f}
	};

	rotation_degree_vector = 
	{
		{0.0f,0.0f,0.0f},
		{0.0f,0.0f,0.0f},
		{0.0f,0.0f,0.0f},
		{0.0f,0.0f,0.0f}
	};

	colors = 
	{
		{0.7f,0.0f,0.0f,1.0f},
		{0.7f,0.7f,0.0f,1.0f},
		{0.7f,0.0f,0.7f,1.0f},
		{0.0f,0.7f,0.7f,1.0f}
	};

}

void Bone_Animation::update(float delta_time)
{
}

void Bone_Animation::reset()
{
	rotation_degree_vector =
	{
		{0.0f,0.0f,0.0f},
		{0.0f,0.0f,0.0f},
		{0.0f,0.0f,0.0f},
		{0.0f,0.0f,0.0f}
	};
}


glm::mat4 Bone_Animation::rotate_bone(glm::mat4 bone, glm::vec3 rotate_vec) {
	glm::quat quaternion = glm::quat(glm::radians(rotate_vec));
	glm::mat4 rotateMatrix = glm::toMat4(quaternion);
	return bone * rotateMatrix;
}

