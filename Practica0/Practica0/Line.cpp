#include "Line.h"


Line::Line(Point point, glm::vec3 direc){
	p = point;
	direction = direc;
}


Line::~Line()
{
}

void Line::setPointLine(const float &x, const float &y, const float &z) {
	p.setCoord(x, y, z);
}

void Line::setDirectionLine(const float &x, const float &y, const float &z) {
	direction = glm::vec3(x, y, z);
}

float Line::distPointToLine(const Point &q) {
	return glm::length(glm::cross((q.coord - p.coord), direction)) / glm::length(direction);
}

void Line::calcAlfa(Point q, Plane p){
	alfa = (-p.d - ((p.norm.x*q.coord.x) + (p.norm.y*q.coord.y) + (p.norm.z*q.coord.z))) / ((p.norm.x*direction.x) + (p.norm.y*direction.y) + (p.norm.z*direction.z));
}