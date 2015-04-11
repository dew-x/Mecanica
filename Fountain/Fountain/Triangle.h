#pragma once
#include <glm/glm.hpp>
#include <iostream>
#include <math.h>

class Triangle
{
	glm::vec3 vertex1;
	glm::vec3 vertex2;
	glm::vec3 vertex3;
	glm::vec3 normal;
	float d;
public:
	Triangle(){};
	~Triangle(){};
	//setters
	void setVertices(const glm::vec3& v1, const glm::vec3& v2, const glm::vec3& v3) {
		vertex1 = v1;
		vertex2 = v2;
		vertex3 = v3;
	};
	void computeNormal() { normal = glm::normalize(glm::cross(vertex2 - vertex1, vertex3 - vertex1)); };
	void computeD() { d = glm::dot(-normal, vertex1); };
	//getters
	glm::vec3 getNormal() { return normal; };
	float getD() { return d; };
	float getTriangleArea(glm::vec3 v1, glm::vec3 v2, glm::vec3 v3){ return (glm::length(glm::cross(v2 - v1, v3 - v1)) / 2); };
	//functions
	bool isPointColliding(glm::vec3 p, glm::vec3 q) {
		if ((glm::dot(normal, q) + d)*(glm::dot(normal, p) + d) <= 0) {
			glm::vec3 v = q - p;
			float alpha = (-d - glm::dot(normal, q)) / glm::dot(normal, v);
			glm::vec3 intersection; intersection = q + alpha*v;
			return	((getTriangleArea(intersection, vertex2, vertex3) + getTriangleArea(vertex1, intersection, vertex3) +
					getTriangleArea(vertex1, vertex2, intersection)) - getTriangleArea(vertex1, vertex2, vertex3) <= 0);
		}
		else return false;
	};
};

