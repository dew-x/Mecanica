#pragma once
#include "Point.h"
#include "Line.h"
class Plane
{
public:
	Plane();
	~Plane();
	Point p;
	glm::vec3 norm;
	float d;
	void setPlane(Point p, glm::vec3 norm);
	//functions
	void calcD();
	Point entryPointSegmentPlane(Line a);
	bool isInFront(Point p);
};

