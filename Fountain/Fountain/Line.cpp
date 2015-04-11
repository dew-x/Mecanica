#include "Line.h"


Line::Line(Point point, glm::vec3 direc){
	p = point;
	direction = direc;
}

Line::Line(Point orig, Point end) {
	p = orig;
	direction = end.coord - orig.coord;
}


Line::~Line()
{
}

float Line::distPointToLine(const Point &q) {
	return glm::length(glm::cross((q.coord - p.coord), direction)) / glm::length(direction);
}