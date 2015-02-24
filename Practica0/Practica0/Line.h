#pragma once
#include <glm/glm.hpp>
#include "Point.h"
#include "Plane.h"
class Line
{
public:
	Line(Point, glm::vec3);
	~Line();
	Point p;
	glm::vec3 direction;
	float alfa;
	// setters
	void setPointLine(const float &x, const float &y, const float &z);
	void setDirectionLine(const float &x, const float &y, const float &z);
	float distPointToLine(const Point &q);
	void calcAlfa(Point, Plane);
};

