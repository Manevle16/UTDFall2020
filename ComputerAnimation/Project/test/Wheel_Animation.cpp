#include "Wheel_Animation.h"

Wheel_Animation::Wheel_Animation(){}

Wheel_Animation::~Wheel_Animation(){}

void Wheel_Animation::init() {
	position_vector = {
		{-.8f, 0.0f, -1.4f },
		{0.79f, 0.0f, -1.4f },
		{-.8f, 0.0f, 1.21f },
		{0.79f, 0.0f, 1.21f }
	};

	scale = { 1.0f, 1.0f, 1.0f };

	rotation_vector = {
		{0.0f, 0.0f, 0.0f },
		{0.0f, 180.0f, 0.0f },
		{0.0f, 0.0f, 0.0f },
		{0.0f, 180.0f, 0.0f }
	};
}

void Wheel_Animation::update(float delta_time) {};

void Wheel_Animation::rotateWheelsByVelocity(glm::vec3 v, int dir) {
	if (dir == 1) {
		for (int i = 0; i < 4; i++) {
			if (i % 2 != 0)
				rotation_vector[i].x += glm::length(v) / 2;
			else
				rotation_vector[i].x -= glm::length(v) / 2;
		}
	}
	else {
		for (int i = 0; i < 4; i++) {
			if (i % 2 == 0)
				rotation_vector[i].x += glm::length(v) / 2;
			else
				rotation_vector[i].x -= glm::length(v) / 2;
		}
	}
}