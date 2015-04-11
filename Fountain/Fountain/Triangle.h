#pragma once
#include "Point.h"
#include "Plane.h"
#define _USE_MATH_DEFINES
#include <math.h>

class Triangle
{
public:
	Triangle(Point, Point, Point);
	~Triangle();
	Point vA, vB, vC;
	Plane* tPlane;
	//functions
	Point entryPointSegmentPlane(Line l,bool &inside);
	bool isPointInside(Point p);
};

