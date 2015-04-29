#pragma once
#include <vector>
#include "Particle.h"

#define CSIZE 50
#define CDIST 0.1f
std::vector<std::vector<int> > streach = {
		{1,0},
		{-1,0},
		{0,1},
		{0,-1}
};

std::vector<std::vector<int> > shear = {
		{ 1, 1 },
		{ -1, 1 },
		{ 1, -1 },
		{ -1, -1 }
};

std::vector<std::vector<int> > bend = {
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
	void updateForces() {

	}
	glm::vec3 getPos(unsigned id) { return particles[id].getCurrentPosition(); };
	float kElastic;
	float kDumping;
};

