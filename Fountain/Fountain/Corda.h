#pragma once
#include <vector>
#include <stdlib.h>
#include "Particle.h"

enum corda_mode {
	ANCHOR0,
	ANCHOR1,
	ANCHOR2,
};

#define CORDA_SIZE 100
#define CORDA_DIST 0.1f

class Corda
{
private:
	std::vector<Particle> particles;
	corda_mode mode;
public:
	Corda();
	~Corda();
	void reset(corda_mode mode);
	unsigned size() { return CORDA_SIZE; };
	glm::vec3 getPos(unsigned id) { return particles[id].getCurrentPosition(); };
	Particle* getPart(unsigned id) { 
		if ((mode == ANCHOR1 && id == 0) || (mode == ANCHOR2 && (id == 0 || id == CORDA_SIZE - 1))) {
			particles[id].setForce({ 0.0f, 0.0f, 0.0f });
			particles[id].setVelocity({ 0.0f, 0.0f, 0.0f });
		}
		else {
			particles[id].setForce({ 0.0f, -9.8f, 0.0f });
			//particles[id].addForce(f1);
			//particles[id].addForce(f2);
		}
		return &particles[id];
	};
};

