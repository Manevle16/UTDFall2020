#include "Wheel_Animation.h"

Wheel_Animation::Wheel_Animation(){}

Wheel_Animation::~Wheel_Animation(){}

void Wheel_Animation::init() {
	position_vector = {
		{-.8f, 0.0f, -1.5f },
		{0.79f, 0.0f, -1.4f },
		{-.8f, 0.0f, 1.20f },
		{0.79f, 0.0f, 1.20f }
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