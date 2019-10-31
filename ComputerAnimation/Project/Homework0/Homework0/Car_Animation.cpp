#include "Car_Animation.h"

Car_Animation::Car_Animation(){}

Car_Animation::~Car_Animation(){}

void Car_Animation::init() {
	position = { 2.0f, 1.0f, 2.0f };
	scale = { 2.0f, 2.0f, 2.0f };
	rotation = { 0.0f, 0.0f, 0.0f };
}

void Car_Animation::reset(){}

void Car_Animation::update(float delta_time) {};