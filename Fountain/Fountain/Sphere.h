#pragma once
#include "Point.h"
#include "Line.h"
#include <vector>
#include <iostream>
#define _USE_MATH_DEFINES
#include <cmath>
#include <math.h>
using namespace std;

class Sphere
{
public:
	Point center;
	float radius;
	Sphere(Point p, float radius);
	~Sphere();
	bool isPointInside(const Point &p);
	Point entryPointSegmentPlane(Line l, bool &valid);
	vector<glm::vec3> Sphere::getVertexSphere(int Resolution);
};

