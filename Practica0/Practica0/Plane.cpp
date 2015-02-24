#include "Plane.h"


Plane::Plane(Point point, glm::vec3 normal){
	p = point;
	norm = normal;
	calcD();
}


Plane::~Plane(){
	
}

void Plane::calcD(){
	d = (-(norm.x)*p.coord.x) + (-(norm.y)*p.coord.y) + (-(norm.z)*p.coord.z);
}

bool Plane::isInFront(Point p){
	float general = (p.coord.x*norm.x) + (p.coord.y*norm.y) + (p.coord.z*norm.z) + d;
	if (general >= 0) return true;
	else return false;
}

Point Plane::entryPointSegmentPlane(Point p, Point q){
	//create direct vector for a line of two enter points
	glm::vec3 v = glm::vec3((q.coord.x - p.coord.x), (q.coord.y - p.coord.y), (q.coord.z - p.coord.z));
	//calc alfa
	float alfa = (-d - ((norm.x*q.coord.x) + (norm.y*q.coord.y) + (norm.z*q.coord.z))) / ((norm.x*v.x) + (norm.y*v.y) + (norm.z*v.z));
	//create a intersect point
	Point intersectPoint;
	intersectPoint.setCoord((q.coord.x + (alfa*v.x)), (q.coord.y + (alfa*v.y)), (q.coord.z + (alfa*v.z)));
	//return this
	return intersectPoint;
}