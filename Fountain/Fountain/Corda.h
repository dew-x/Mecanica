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
			if (id - 1 >= 0){
				float dist = glm::distance(particles[id - 1].getCurrentPosition(), particles[id].getCurrentPosition());
				glm::vec3 norm = (particles[id].getCurrentPosition() - particles[id - 1].getCurrentPosition()) / dist;
				glm::vec3 velR = particles[id].getVelocity() - particles[id - 1].getVelocity();
				glm::vec3 force = (kElastic*(dist - CORDA_DIST)) + kDumping * (glm::dot(velR, norm))*norm;
				particles[id].addForce(force);
			}if (id + 1 < CORDA_SIZE){
				float dist = glm::distance(particles[id + 1].getCurrentPosition(), particles[id].getCurrentPosition());
				glm::vec3 norm = (particles[id].getCurrentPosition() - particles[id + 1].getCurrentPosition()) / dist;
				glm::vec3 velR = particles[id].getVelocity() - particles[id + 1].getVelocity();
				glm::vec3 force = (kElastic*(dist - CORDA_DIST)) + kDumping * (glm::dot(velR, norm))*norm;
				particles[id].addForce(force);
			}
			//particles[id].addForce(f1);
			//particles[id].addForce(f2);
		}
		return &particles[id];
	};
	float kElastic;
	float kDumping;
};

