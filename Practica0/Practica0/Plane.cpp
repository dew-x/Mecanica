#include "Plane.h"


Plane::Plane(){
}


Plane::~Plane(){
	
}

void Plane::calcD(){
	d = (-(norm.x)*p.coord.x) + (-(norm.y)*p.coord.y) + (-(norm.z)*p.coord.z);
}

void Plane::setPlane(Point point, glm::vec3 normal){
	p = point;
	norm = normal;
	calcD();
}

bool Plane::isInFront(Point p){
	float general = (p.coord.x*norm.x) + (p.coord.y*norm.y) + (p.coord.z*norm.z) + d;
	if (general >= 0) return true;
	else return false;
}

Point Plane::entryPointSegmentPlane(Line a){
	//create a intersect point
	a.calcAlfa(*this);
	Point intersectPoint;
	intersectPoint.setCoord((a.p.coord.x + (a.alfa*a.direction.x)), (a.p.coord.y + (a.alfa*a.direction.y)), (a.p.coord.z + (a.alfa*a.direction.z)));
	//return this
	return intersectPoint;
}