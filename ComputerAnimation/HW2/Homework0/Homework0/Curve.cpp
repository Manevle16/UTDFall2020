#include "Curve.h"

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
}

void Curve::calculate_curve()
{
	std::vector<glm::vec3> temp;
	for (int j = 0; j < this->control_points_pos.size(); j++) {
		temp.push_back(this->control_points_pos[j]);
		for (float i = 0; i < this->num_points_per_segment; i++) {
			float time = i / float(num_points_per_segment);
			temp.push_back(this->CatmullRoll(time, this->control_points_pos[(j-1)%this->control_points_pos.size()], this->control_points_pos[j], this->control_points_pos[(j + 1) % this->control_points_pos.size()], this->control_points_pos[(j + 2) % this->control_points_pos.size()]));
		}
	}
	this->curve_points_pos = temp;
}

