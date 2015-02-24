#include "Line.h"


Line::Line() : direction(0.0f, 0.0f, 0.0f)
{		
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
