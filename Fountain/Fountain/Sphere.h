#pragma once
#include "Point.h"
#include "Line.h"

class Sphere
{
public:
	Point center;
	float radius;
	Sphere(Point p, float radius);
	~Sphere();
	bool isPointInside(const Point &p);
	Point entryPointSegmentPlane(Line l, bool &valid);
};

