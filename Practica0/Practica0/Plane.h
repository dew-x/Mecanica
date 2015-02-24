#pragma once
#include "Point.h"
#include "Line.h"
class Plane
{
public:
	Plane(Point point, glm::vec3 normal);
	~Plane();
	Point p;
	glm::vec3 norm;
	float d;
	//functions
	Point entryPointSegmentPlane(Line a);
	bool isInFront(Point p);
};

