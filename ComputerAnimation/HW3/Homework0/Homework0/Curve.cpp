#include "Curve.h"
#include "glm/ext.hpp"

Curve::Curve()
{
}

Curve::~Curve()
{
}

void Curve::init()
{
	this->control_points_pos = {
		{ 0.0, 8.5, -2.0 },
		{ -3.0, 11.0, 2.3 },
		{ -6.0, 8.5, -2.5 },
		{ -4.0, 5.5, 2.8 },
		{ 1.0, 2.0, -4.0 },
		{ 4.0, 2.0, 3.0 },
		{ 7.0, 8.0, -2.0 },
		{ 3.0, 10.0, 3.7 }
	};
	calculate_curve();
}

void Curve::calculate_curve()
{
	std::vector<glm::vec3> temp;
	float cur_len = 0;
	for (int j = 0; j < this->control_points_pos.size(); j++) {
		temp.push_back(this->control_points_pos[j]);
		for (float i = 1; i < this->num_points_per_segment + 1; i++) {
			float time = i / float(num_points_per_segment + 1);
			temp.push_back(this->CatmullRoll(time, this->control_points_pos[(j - 1) % this->control_points_pos.size()], this->control_points_pos[j], this->control_points_pos[(j + 1) % this->control_points_pos.size()], this->control_points_pos[(j + 2) % this->control_points_pos.size()]));
			cur_len += glm::distance(temp[temp.size() - 2], temp[temp.size() - 1]);
			this->segment_length.push_back(cur_len);

		}
	}
	
	this->total_segment_length = segment_length[segment_length.size() - 1];
	//Normalize segment length table

	for (int i = 0; i < this->segment_length.size(); i++) {
		segment_length[i] = segment_length[i] / this->total_segment_length;
	}
	this->curve_points_pos = temp;
}
