#include "Sphere.h"


Sphere::Sphere(Point p, float radius)
{
	center = p;
	this->radius = radius;
}


Sphere::~Sphere()
{
}

bool Sphere::isPointInside(const Point &p) {
	return center.distanceToPoint(p) <= radius;
}
