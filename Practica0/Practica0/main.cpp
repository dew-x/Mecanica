#include <iostream>
#include <iomanip>
#include <glm\glm.hpp>
#include <vector>
#include "Point.h"
#include "functions.h"
#include "Sphere.h"
#include "Plane.h"
#include "Triangle.h"
using namespace std;


void main() {
	cout << setprecision(8);
	float alpha = deg2rad(30.0);
	float beta = deg2rad(45.0);
	glm::vec3 direction = getVecFrom2Angles(alpha, beta);
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
	bool dir = s.isPointInside(points[pos]);
	while (pos < points.size() && dir==s.isPointInside(points[pos])) ++pos;
	Line ls3(points[pos - 1], points[pos]);
	bool valid;
	Point inter1 = s.entryPointSegmentPlane(ls3, valid);
	cout << "Shpere collision" << endl;
	cout << "Collision between " << points[pos - 1] << " and " << points[pos] << endl;
	cout << "Collision point: " << inter1 << endl << endl;
	// plane
	Point Q(1, 2, 1);
	glm::vec3 norm = { -1, 1, 1 };
	Plane p(Q, norm);
	pos = 0;
	dir = p.isInFront(points[0]);
	while (pos < points.size() && dir==p.isInFront(points[pos])) ++pos;
	Line ls1(points[pos - 1], points[pos]);
	Point inter=p.entryPointSegmentPlane(ls1);
	cout << "Plane collision" << endl;
	cout << "Collision between " << points[pos - 1] << " and " << points[pos] <<  endl;
	cout << "Collision point: " << inter << endl << endl;
	// triangle
	Point v1(1, 2, 1), v2(-1, 1, 2), v3(0, -1, 0);
	Triangle t(v1, v2, v3);
	pos = 0;
	dir = t.tPlane->isInFront(points[0]);
	while (pos < points.size() && dir == t.tPlane->isInFront(points[pos])) ++pos;
	Line ls2(points[pos - 1], points[pos]);
	bool valid1;
	Point inter2 = t.entryPointSegmentPlane(ls2,valid1);
	cout << "Triangle collision" << endl;
	cout << "Collision between " << points[pos - 1] << " and " << points[pos] << endl;
	if (valid1) {
		cout << "Collision point: " << inter << endl << endl;
	}
	else {
		cout << "Collision outside triangle." << endl << endl;
	}
	system("PAUSE");
}