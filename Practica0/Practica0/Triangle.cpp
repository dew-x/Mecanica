#include "Triangle.h"


Triangle::Triangle(){
}


Triangle::~Triangle()
{
}

void Triangle::setTriangle(Point v1, Point v2, Point v3){
	glm::vec3 direc1 = glm::vec3(v2.coord.x - v1.coord.x, v2.coord.y - v1.coord.y, v2.coord.z - v1.coord.z);
	glm::vec3 direc2 = glm::vec3(v3.coord.x - v1.coord.x, v3.coord.y - v1.coord.y, v3.coord.z - v1.coord.z);
	tPlane.setPlane(v1, glm::cross(direc1,direc2));
	vA = v1;
	vB = v2;
	vC = v3;
}
