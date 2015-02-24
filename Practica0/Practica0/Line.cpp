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

void Line::calcAlfa(Plane plane){
	alfa = (-plane.d - ((plane.norm.x*p.coord.x) + (plane.norm.y*p.coord.y) + (plane.norm.z*p.coord.z))) / ((plane.norm.x*direction.x) + (plane.norm.y*direction.y) + (plane.norm.z*direction.z));
}