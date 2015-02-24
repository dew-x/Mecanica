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
