#pragma once
#include "Point.h"
#include "Plane.h"

class Triangle
{
public:
	Triangle();
	~Triangle();
	Point vA, vB, vC;
	Plane tPlane;
	//functions
	void setTriangle(Point, Point, Point);
};

