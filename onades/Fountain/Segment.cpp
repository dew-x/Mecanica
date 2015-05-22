#include "Segment.h"


Segment::Segment(const Point &p, const Point &q)
{
	origin = p;
	final = q;
}


Segment::~Segment()
{
}
