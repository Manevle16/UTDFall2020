#include "Wheel_Animation.h"

Wheel_Animation::Wheel_Animation(){}

Wheel_Animation::~Wheel_Animation(){}

void Wheel_Animation::init() {
	position_vector = {
		{-.8, 0.0, -1.4 },
		{0.79, 0.0, -1.4 },
		{-.8, 0.0, 1.21 },
		{0.79, 0.0, 1.21 }
	};

	scale = { 1.0f, 1.0f, 1.0f };

	rotation_vector = {
		{0.0, 0.0, 0.0 },
		{0.0, 180.0, 0.0 },
		{0.0, 0.0, 0.0 },
		{0.0, 180.0, 0.0 }
	};
}

void Wheel_Animation::update(float delta_time) {};

void Wheel_Animation::rotateWheelsByVelocity(glm::dvec3 v, int dir) {
	if (dir == 1) {
		for (int i = 0; i < 4; i++) {
			if (i % 2 != 0)
				rotation_vector[i].x += glm::length(v) / 2;
			else
				rotation_vector[i].x -= glm::length(v) / 2;
			rotation_vector[i].x = fmod(rotation_vector[i].x, 360);
		}
		
	}
	else {
		for (int i = 0; i < 4; i++) {
			if (i % 2 == 0)
				rotation_vector[i].x += glm::length(v) / 2;
			else
				rotation_vector[i].x -= glm::length(v) / 2;
			rotation_vector[i].x = fmod(rotation_vector[i].x, 360);
		}
	}
}