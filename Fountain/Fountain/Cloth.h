#pragma once
#include <vector>
#include "Particle.h"

#define CSIZE 50
#define CDIST 0.1f

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
};

