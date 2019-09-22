#pragma once
#include <vector>
#include <iostream>

#include <glm/glm.hpp>
#include <glm/gtc/matrix_transform.hpp>
#include <glm/gtc/type_ptr.hpp>
#include <glm/gtx/string_cast.hpp>

class Curve
{
public:
	Curve();
	~Curve();
	
	void init();
	void calculate_curve();
	
public:
	float tau = 0.5; // Coefficient for catmull-rom spline
	int num_points_per_segment = 200;

	std::vector<glm::vec3> control_points_pos;
	std::vector<glm::vec3> curve_points_pos;

private:
	glm::vec3 CatmullRoll(float t, glm::vec3 p1, glm::vec3 p2, glm::vec3 p3, glm::vec3 p4)
	{
		glm::mat4 coefM = {
			{-1, 3, -3, 1},
			{2, -5, 4, -1},
			{-1, 0, 1, 0},
			{0, 2, 0, 0}
		};
		glm::vec4 u =  {t * t * t, t * t, t, 1 };
		glm::mat4x3 points = { p1, p2, p3, p4 };
		std::cout << glm::to_string(u * glm::transpose(coefM*tau)) << "\n" ;
		glm::vec3 v = u * glm::transpose(coefM*tau) * glm::transpose(points) ;

		/* Catmull Rom spline Calculation */

		
		return v;
	}
};