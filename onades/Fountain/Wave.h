#pragma once
#include <vector>
#include <iostream>
#include <GL\glew.h>
#include <SDL\SDL.h>
#include <SDL\SDL_opengl.h>


#define CSIZE 320
const float CDIST = 10.0f / CSIZE;
const float CDIST2 = CDIST*CDIST;
const float CWAVE = 1.96f / CDIST2;

struct info{
	float height;
	float velocity;
	info *a, *b, *c, *d;
};

const std::vector<std::vector<int> > streach = {
		{ 1, 0 },
		{ -1, 0 },
		{ 0, 1 },
		{ 0, -1 }
};

class Wave
{
	std::vector<info> wave;
public:
	Wave();
	~Wave();

	void reset(float height);
	void movePoint();
	void moveWave();
	void updateVelocity(float deltaT);
	int size() { return CSIZE; }
	void loadVBO(std::vector<GLfloat> &vbo);
};

