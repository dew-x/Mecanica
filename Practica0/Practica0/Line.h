#pragma once
#include <glm/glm.hpp>
#include "Point.h"
class Line
{
public:
	Line();
	~Line();
	Point p;
	glm::vec3 direction;
	float alfa;
	// setters
	void setPointLine(const float &x, const float &y, const float &z);
	void setDirectionLine(const float &x, const float &y, const float &z);
	float distPointToLine(const Point &q);
};

