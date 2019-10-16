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

	this->control_points_quaternion = {
		{0.13964   , 0.0481732 , 0.831429 , 0.541043 , },
		{0.0509038 , -0.033869 , -0.579695, 0.811295 , },
		{-0.502889 , -0.366766 , 0.493961 , 0.592445 , },
		{-0.636    , 0.667177  , -0.175206, 0.198922 , },
		{0.693492  , 0.688833  , -0.152595, -0.108237, },
		{0.752155  , -0.519591 , -0.316988, 0.168866 , },
		{0.542054  , 0.382705  , 0.378416 , 0.646269 , },
		{0.00417342, -0.0208652, -0.584026, 0.810619   }
	};
}

void Curve::calculate_curve()
{
	std::vector<glm::vec3> temp;
	float cur_len = 0;
	float control_len = 0;
	for (int j = 0; j < this->control_points_pos.size(); j++) {
		temp.push_back(this->control_points_pos[j]);
		for (float i = 1; i < this->num_points_per_segment + 1; i++) {
			float time = i / float(num_points_per_segment + 1);
			temp.push_back(this->CatmullRoll(time, this->control_points_pos[(j - 1) % this->control_points_pos.size()], this->control_points_pos[j], this->control_points_pos[(j + 1) % this->control_points_pos.size()], this->control_points_pos[(j + 2) % this->control_points_pos.size()]));
			cur_len += glm::distance(temp[temp.size() - 2], temp[temp.size() - 1]);
			this->segment_length.push_back(cur_len);

		}
		if (j == 0) {
			this->control_points_length.push_back(0);
			continue;
		}
		control_len += glm::distance(this->control_points_pos[j-1], this->control_points_pos[j]);
		this->control_points_length.push_back(control_len);
	}
	
	this->total_segment_length = segment_length[segment_length.size() - 1];

	//Normalize segment length tables
	for (int i = 0; i < this->segment_length.size(); i++) {
		this->segment_length[i] = this->segment_length[i] / this->total_segment_length;
	}

	for (int i = 0; i < this->control_points_length.size(); i++) {
		this->control_points_length[i] = this->control_points_length[i] / this->total_segment_length;
	}
	this->curve_points_pos = temp;
}

glm::vec3 Curve::CatmullRoll(float t, glm::vec3 p1, glm::vec3 p2, glm::vec3 p3, glm::vec3 p4)
{
	/* Catmull Rom spline Calculation */
	glm::mat4 coefM = {
		{-1, 3, -3, 1},
		{2, -5, 4, -1},
		{-1, 0, 1, 0},
		{0, 2, 0, 0}
	};
	glm::vec4 u = { t * t * t, t * t, t, 1 };
	glm::mat4x3 points = { p1, p2, p3, p4 };
	glm::vec3 v = u * glm::transpose(coefM * tau) * glm::transpose(points);
	return v;
}
