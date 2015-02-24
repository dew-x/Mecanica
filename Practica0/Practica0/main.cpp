#include <iostream>
#include <glm\glm.hpp>
#include <vector>
#include "Point.h"
#include "functions.h"
#include "Sphere.h"
using namespace std;


void main() {
	float alpha = deg2rad(30.0);
	float beta = deg2rad(45.0);
	glm::vec3 direction = getVecFrom2Angles(alpha, beta);
	cout << direction.x << " " << direction.y << " " << direction.z << endl;
	vector<Point> points;
	for (float i = 0; i <= 10; i += 0.01) {
		Point p;
		p.setCoord(direction.x*i, direction.y*i, direction.z*i);
		points.push_back(p);
	}
	// sphere
	Point center(1,2,1);
	float radius = 3.0;
	Sphere s(center, radius);
	unsigned pos = 0;
	while (pos < points.size() && !s.isPointInside(points[pos])) ++pos;
	cout << pos << endl;
	while (pos < points.size() && s.isPointInside(points[pos])) ++pos;
	cout << pos << endl;
	// plane

	// triangle
	system("PAUSE");
}