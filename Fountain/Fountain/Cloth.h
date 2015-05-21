#pragma once
#include <vector>
#include <iostream>
#include "Particle.h"

#define CSIZE 20
#define CDIST 0.1f
const float CDIST2= CDIST*sqrt(2);

const std::vector<std::vector<int> > streach = {
		{1,0},
		{-1,0},
		{0,1},
		{0,-1}
};

const std::vector<std::vector<int> > shear = {
		{ 1, 1 },
		{ -1, 1 },
		{ 1, -1 },
		{ -1, -1 }
};

const std::vector<std::vector<int> > bend = {
		{ 2, 0 },
		{ -2, 0 },
		{ 0, 2 },
		{ 0, -2 }
};

class Cloth {
private:
	std::vector<Particle> particles;
public:
	Cloth();
	~Cloth();
	void reset(float height);
	Particle* getPart(unsigned id) {
		return &particles[id];
	}
	unsigned getSize() {
		return CSIZE;
	}
	void updateForces();
	glm::vec3 getPos(unsigned i, unsigned j) { return particles[i*CSIZE+j].getCurrentPosition(); };
	float kElastic;
	float kDumping;
};

