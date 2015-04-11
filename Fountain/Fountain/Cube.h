#pragma once
#include <glm/glm.hpp>
#include <iostream>
#include <GL\glew.h>
#include <vector>
using namespace std;

class Cube
{
	glm::vec3 center;
	glm::vec3 distances;

public:
	Cube(const glm::vec3 &c ,const glm::vec3 &d);
	~Cube();
	vector<glm::vec3> Cube::getVertices();
	vector<glm::vec3> Cube::getQuads();
};

