#include "Plane.h"


Plane::Plane(Point point, glm::vec3 normal){
	p = point;
	norm = normal;
	d = glm::dot(-norm, p.coord);
}


Plane::~Plane(){
	
}

bool Plane::isInFront(Point p){
	float general = glm::dot(p.coord,norm) + d;
	if (general >= 0) return true;
	else return false;
}

// http://stackoverflow.com/questions/5666222/3d-line-plane-intersection
Point Plane::entryPointSegmentPlane(Line l){
	float fac = -glm::dot(norm, l.p.coord-p.coord) / glm::dot(norm, l.direction);
	glm::vec3 intersection = l.p.coord + (l.direction * fac);
	Point intersectPoint(intersection.x, intersection.y, intersection.z);
	return intersectPoint;
}