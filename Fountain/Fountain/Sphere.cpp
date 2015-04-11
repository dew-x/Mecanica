#include "Sphere.h"
#define _USE_MATH_DEFINES

Sphere::Sphere(Point p, float radius)
{
	center = p;
	this->radius = radius;
}


Sphere::~Sphere()
{
}

bool Sphere::isPointInside(const Point &p) {
	return center.distanceToPoint(p) <= radius;
}

Point Sphere::entryPointSegmentPlane(Line l, bool &valid) {
	float a = glm::dot(l.direction, l.direction);
	float b = 2 * glm::dot(l.direction, l.p.coord - center.coord);
	float c = glm::dot(center.coord, center.coord) + glm::dot(l.p.coord, l.p.coord) - 2 * glm::dot(center.coord, l.p.coord) - radius*radius;
	float total = b*b - 4*a*c;
	if (total >= 0) {
		glm::vec3 intersection = l.p.coord + l.direction * ((-b + sqrt(total)) / (2 * a));
		valid = true;
		return Point(intersection.x, intersection.y, intersection.z);
	}
	else {
		valid = false;
		return Point(0, 0, 0);
	}
}

vector<glm::vec3> Sphere::getVertexSphere(int r){

	// vertice positions
	std::vector<glm::vec3> vertex;

	// iniatiate the variable we are going to use
	float xA, yA, xB, yB, zA, zB, alfa, beta, gama, omega, Radius1, Radius2;

	for (int w = 0; w < r; w++) {
		for (int h = (-r / 2); h < (r / 2); h++){

			alfa = (w / (float)r) * 2 * M_PI;
			beta = ((w + 1) / (float)r) * 2 * M_PI;

			gama= (h / (float)r)*M_PI;
			omega = ((h + 1) / (float)r)*M_PI;

			xA = sin(alfa);
			yA = cos(alfa);
			xB = sin(beta);
			yB= cos(beta);

			// store the upper and lower radius, remember everything is going to be drawn as triangles
			Radius1 = radius*cos(gama);
			Radius2 = radius*cos(omega);

			zB = radius*sin(gama);
			zB = radius*sin(omega);

			// insert the triangle coordinates
			vertex.push_back(glm::vec3(Radius1*xA, zA, Radius1*yA));
			vertex.push_back(glm::vec3(Radius1*xB, zA, Radius1*yB));
			vertex.push_back(glm::vec3(Radius2*xB, zB, Radius2*yB));

			vertex.push_back(glm::vec3(Radius1*xA, zA, Radius1*yA));
			vertex.push_back(glm::vec3(Radius2*xB, zB, Radius2*yB));
			vertex.push_back(glm::vec3(Radius2*xA, zB, Radius2*yA));
		}
	}
	return vertex;
}
