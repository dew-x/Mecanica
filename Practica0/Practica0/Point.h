#pragma once
#include <glm/glm.hpp>
#include <iostream>
class Point
{
public:
	Point();
	Point(float x, float y, float z);
	Point(glm::vec3 vec);
	~Point();
	glm::vec3 coord;
	// setters
	void setCoord(const float &x, const float &y, const float &z);
	// functions
	virtual float distanceToPoint(const Point& q);
	Point pointInSegment(const Point& q, const float& alfa);
	friend std::ostream &operator<<(std::ostream &os, Point const &p);
};

