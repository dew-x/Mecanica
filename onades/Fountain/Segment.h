#pragma once
#include <glm\glm.hpp>
#include "Point.h"
class Segment
{
public:
	Point origin;
	Point final;
	Segment(const Point &p, const Point &q);
	~Segment();
};

