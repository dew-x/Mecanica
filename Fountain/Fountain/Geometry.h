#pragma once 
#include "Vertex.h"
#include "ErrorManagement.h"
#include <string>
#include <fstream>
#include <vector>
#include <iostream>
#include <stdlib.h>
#include <time.h>

#define NUM_PRIMITIVES 7
#define PI 3.14159

struct GameObject {
	int _objectType;
	glm::vec3 _translation;
	float _angle;
	glm::vec3 _rotation;
	glm::vec3 _scale;
	int _mode;
};

class Geometry
{
	Vertex * _data[NUM_PRIMITIVES];
	vector <GameObject> _objects;
	int maxObjects;
	int maxVertices[NUM_PRIMITIVES];

public:
	Geometry();
	~Geometry();
	// getters
	inline vector <GameObject> &getObject() { return _objects; }
	inline int getNumObjects() { return maxObjects; }
	inline Vertex* getData(const int &i) { return _data[i]; }
	inline int getNumVertices(const int &i) { return maxVertices[i]; }
	// functions
	void initPrimitives();
	void LoadScene(string fileName);
};

