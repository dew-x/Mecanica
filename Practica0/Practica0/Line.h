#pragma once
#include <glm/glm.hpp>
#include "Point.h"
class Line
{
public:
	Line(Point, glm::vec3);
	Line(Point orig, Point end);
	~Line();
	Point p;
	glm::vec3 direction;
	// setters
	float distPointToLine(const Point &q);
};

