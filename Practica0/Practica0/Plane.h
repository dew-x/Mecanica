#pragma once
#include "Point.h"
#include "Line.h"
class Plane
{
public:
	Plane(Point p, glm::vec3 norm);
	~Plane();
	Point p;
	glm::vec3 norm;
	float d;
	//functions
	void calcD();
	Point entryPointSegmentPlane(Point p, Point q);
	bool isInFront(Point p);
};

