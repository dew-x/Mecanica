#include "Triangle.h"


Triangle::Triangle(Point v1, Point v2, Point v3){
	glm::vec3 direc1 = glm::vec3(v2.coord.x - v1.coord.x, v2.coord.y - v1.coord.y, v2.coord.z - v1.coord.z);
	glm::vec3 direc2 = glm::vec3(v3.coord.x - v1.coord.x, v3.coord.y - v1.coord.y, v3.coord.z - v1.coord.z);
	tPlane= new Plane(v1, glm::cross(direc1, direc2));
	vA = v1;
	vB = v2;
	vC = v3;
}


Triangle::~Triangle()
{
}

Point Triangle::entryPointSegmentPlane(Line l, bool &inside) {
	Point p = tPlane->entryPointSegmentPlane(l);
	if (isPointInside(p)) inside=true;
	else inside=false;
	return p;
}

bool Triangle::isPointInside(Point p) {
	glm::vec3 l1, l2, l3;
	l1 = glm::normalize(vA.coord - p.coord);
	l2 = glm::normalize(vB.coord - p.coord);
	l3 = glm::normalize(vC.coord - p.coord);
	float angle = acos(glm::dot(l1, l2)) + acos(glm::dot(l2, l3)) + acos(glm::dot(l3, l1));
	return fabs(M_PI * 2 - angle) < 0.0001;
}

vector<glm::vec3> Triangle::getVertex(){
	vector<glm::vec3> vertex[3];
	vertex[3] = {

	};
	return vertex[3];
}

glm::vec3 Triangle::TransformPointToVertex(Point a){

}