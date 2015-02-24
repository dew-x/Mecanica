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

Point Sphere::entryPointSegmentPlane(Line l, bool &valid) {
	float a = glm::dot(l.direction, l.direction);
	float b = 2 * glm::dot(l.direction, l.p.coord - center.coord);
	float c = glm::dot(center.coord, center.coord) + glm::dot(l.p.coord, l.p.coord) - 2 * glm::dot(center.coord, l.p.coord) - radius*radius;
	float total = b*b - 4*a*c;
	if (total >= 0) {
		glm::vec3 intersection = l.p.coord + l.direction * ((-b + sqrt(total)) / (2 * a));
		valid = true;
		return Point(intersection.x, intersection.y, intersection.z);
	}
	else {
		valid = false;
		return Point(0, 0, 0);
	}
}
