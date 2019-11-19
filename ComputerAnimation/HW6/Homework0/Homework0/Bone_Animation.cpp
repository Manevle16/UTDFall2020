#include "Bone_Animation.h"



Bone_Animation::Bone_Animation()
{
}


Bone_Animation::~Bone_Animation()
{
}

void Bone_Animation::init()
{
	root_position = { 2.0f,.5f,1.0f };
	end_effector = {0, 0, 0};

	position_vector = {
		{ 2.0f, .5f, 1.0f },
		{ 2.0f, 3.0f, 1.0f },
		{ 2.0f, 6.5f, 1.0f },
		{ 2.0f, 9.0f, 1.0f }
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
		{0.0f,0.0f,30.0f},
		{0.0f,0.0f,30.0f},
		{0.0f,0.0f,30.0f}
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

std::vector<glm::vec3> Bone_Animation::compute_jacob() {
	
	jacob_mat.clear();
	for (int i = 0; i < 3; i++) {
		jacob_mat[i * 3][0] = end_effector.x / rotation_degree_vector[i].x;
		jacob_mat[i * 3 + 1][0] = end_effector.x / rotation_degree_vector[i].y;
		jacob_mat[i * 3 + 2][0] = end_effector.x / rotation_degree_vector[i].z;

		jacob_mat[i * 3][1] = end_effector.y / rotation_degree_vector[i].x;
		jacob_mat[i * 3 + 1][1] = end_effector.y / rotation_degree_vector[i].y;
		jacob_mat[i * 3 + 2][1] = end_effector.y / rotation_degree_vector[i].z;

		jacob_mat[i * 3][2] = end_effector.z / rotation_degree_vector[i].x;
		jacob_mat[i * 3 + 1][2] = end_effector.z / rotation_degree_vector[i].y;
		jacob_mat[i * 3 + 2][2] = end_effector.z / rotation_degree_vector[i].z;
	}
}

