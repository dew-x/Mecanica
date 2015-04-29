#pragma once
#include <vector>
#include <stdlib.h>
#include "Particle.h"
#include <iostream>

enum corda_mode {
	ANCHOR0,
	ANCHOR1,
	ANCHOR2,
};

#define CORDA_SIZE 50
#define CORDA_DIST 0.01f

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
	void updateForces() {
		for (unsigned id = 0; id < CORDA_SIZE; ++id) {
			//std::cout <<id<<" "<< particles[id].getCurrentPosition().x << " " << particles[id].getCurrentPosition().y << " " << particles[id].getCurrentPosition().z << endl;
			if ((mode == ANCHOR1 && id == 0) || (mode == ANCHOR2 && (id == 0 || id == CORDA_SIZE - 1))) {
				particles[id].setForce({ 0.0f, 0.0f, 0.0f });
				particles[id].setVelocity({ 0.0f, 0.0f, 0.0f });
			}
			else {
				particles[id].setForce({ 0.0f, -9.8f, 0.0f });
				if (id - 1 >= 0){
					float dist = glm::distance(particles[id - 1].getCurrentPosition(), particles[id].getCurrentPosition());
					glm::vec3 norm = glm::normalize(particles[id - 1].getCurrentPosition() - particles[id].getCurrentPosition());
					glm::vec3 velR = particles[id - 1].getVelocity() - particles[id].getVelocity();
					glm::vec3 force = ((kElastic*(dist - CORDA_DIST)) + (kDumping * (glm::dot(velR, norm))))*norm;
					particles[id].addForce(force);
					//std::cout << "NORM 1 " << norm.x << " " << norm.y << " " << norm.z << endl;
					//std::cout << "DIST 1 " << glm::distance(particles[id - 1].getCurrentPosition(), particles[id].getCurrentPosition()) << std::endl;
				}
				if (id + 1 < CORDA_SIZE){
					float dist = glm::distance(particles[id + 1].getCurrentPosition(), particles[id].getCurrentPosition());
					glm::vec3 norm = glm::normalize(particles[id + 1].getCurrentPosition() - particles[id].getCurrentPosition());
					glm::vec3 velR = particles[id + 1].getVelocity() - particles[id].getVelocity();
					glm::vec3 force = ((kElastic*(dist - CORDA_DIST)) + (kDumping * (glm::dot(velR, norm))))*norm;
					particles[id].addForce(force);
					//std::cout << "NORM 2 " << norm.x << " " << norm.y << " " << norm.z << endl;
					//std::cout << "DIST 2 " << glm::distance(particles[id + 1].getCurrentPosition(), particles[id].getCurrentPosition()) << std::endl;
				}
				//particles[id].addForce(f1);
				//particles[id].addForce(f2);
			}
			//std::cout << id << " " << particles[id].getForce().x << " " << particles[id].getForce().y << " " << particles[id].getForce().z << endl;
			
		}
		//system("PAUSE");
	}
	Particle* getPart(unsigned id) { 
		/*if ((mode == ANCHOR1 && id == 0) || (mode == ANCHOR2 && (id == 0 || id == CORDA_SIZE - 1))) {
			particles[id].setForce({ 0.0f, 0.0f, 0.0f });
			particles[id].setVelocity({ 0.0f, 0.0f, 0.0f });
		}
		else {
			particles[id].setForce({ 0.0f, -9.8f, 0.0f }); 
			if (id - 1 >= 0){
				float dist = glm::distance(particles[id - 1].getCurrentPosition(), particles[id].getCurrentPosition());
				glm::vec3 norm = (particles[id-1].getCurrentPosition() - particles[id].getCurrentPosition()) / dist;
				glm::vec3 velR = particles[id - 1].getVelocity() - particles[id].getVelocity();
				glm::vec3 force = (kElastic*(dist - CORDA_DIST)) + kDumping * (glm::dot(velR, norm))*norm;
				particles[id].addForce(force);
			}if (id + 1 < CORDA_SIZE){
				float dist = glm::distance(particles[id + 1].getCurrentPosition(), particles[id].getCurrentPosition());
				glm::vec3 norm = (particles[id+1].getCurrentPosition() - particles[id].getCurrentPosition()) / dist;
				glm::vec3 velR = particles[id + 1].getVelocity() - particles[id].getVelocity();
				glm::vec3 force = (kElastic*(dist - CORDA_DIST)) + kDumping * (glm::dot(velR, norm))*norm;
				particles[id].addForce(force);
			}
			//particles[id].addForce(f1);
			//particles[id].addForce(f2);
		}*/
		return &particles[id];
	};
	float kElastic;
	float kDumping;
};

