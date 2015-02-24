#pragma once
#define _USE_MATH_DEFINES
#include <math.h>
#include <glm\glm.hpp>

float deg2rad(float deg) {
	return deg * M_PI / 180.0;
}

glm::vec3 getVecFrom2Angles(float alpha, float beta) {
	glm::vec3 ret(cos(alpha)*cos(beta), sin(beta), sin(alpha)*cos(beta));
	return ret;
}