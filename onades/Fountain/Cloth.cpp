#include "Cloth.h"


float mapf(float v, float a, float b, float c, float d) {
	return ((v - a) / (b - a))*(d - c) + c;
}

bool cinside(int x,int y){
	return x >= 0 && x < CSIZE && y >= 0 && y < CSIZE;
}

Cloth::Cloth(){
	kElastic = 200;
	kDumping = 7;
	reset(5.0);
}


Cloth::~Cloth(){
}

void Cloth::reset(float height) {
	particles = std::vector<Particle>(CSIZE*CSIZE);
	for (unsigned i = 0; i < CSIZE; ++i) {
		for (unsigned j = 0; j < CSIZE; ++j) {
			particles[i*CSIZE+j].setPosition({ mapf(i, 0, CSIZE - 1, -(CSIZE*CDIST) / 2, (CSIZE*CDIST) / 2), height/2, mapf(j, 0, CSIZE - 1, -(CSIZE*CDIST) / 2, (CSIZE*CDIST) / 2) });//retocar
			particles[i*CSIZE + j].setForce({ 0.0f, 0.0f, 0.0f });
			particles[i*CSIZE + j].setBouncing(0.6f);
		}
	}
}

void Cloth::updateVelocity(){
	for (int i = 0;i < CSIZE;i++){
		for (int j = 0;j < CSIZE;j++){
			//particles[(i*CSIZE) + j].setForce({ 0, 0, 0 });
			//creem un vector de vectors per guardar-nos els 4 veins de la particula en questio
			glm::vec3 velocity = {0,0,0};
			for (int x = 0; x < streach.size(); x++){
				if (cinside((i + streach[x][0]), (j + streach[x][1]))){
					velocity += particles[((i + streach[x][0])*CSIZE) + (j + streach[x][1])].getVelocity() - particles[(i*CSIZE) + j].getVelocity();
				}
				else{
					velocity += particles[((i + streach[x][0]*-1)*CSIZE) + (j + streach[x][1]*-1)].getVelocity() - particles[(i*CSIZE) + j].getVelocity();
				}
			}
			/*
				//streach
			for (int x = 0; x < streach.size(); x++){
				if (cinside((i+streach[x][0]),(j+streach[x][1]))){
					float dist = glm::distance(particles[((i+streach[x][0])*CSIZE)+(j+streach[x][1])].getCurrentPosition(), particles[(i*CSIZE)+j].getCurrentPosition());
					glm::vec3 norm = glm::normalize(particles[((i+streach[x][0])*CSIZE) + (j + streach[x][1])].getCurrentPosition() - particles[(i*CSIZE) + j].getCurrentPosition());
					glm::vec3 velR = particles[((i+streach[x][0])*CSIZE) + (j + streach[x][1])].getVelocity() - particles[(i*CSIZE) + j].getVelocity();
					glm::vec3 force = ((kElastic*(dist - CDIST)) + (kDumping * (glm::dot(velR, norm))))*norm;
					particles[(i*CSIZE) + j].addForce(force);
				}
			}
			//shear
			for (int x = 0; x < shear.size();x++){
				if (cinside((i+shear[x][0]),(j+shear[x][1]))){
					float dist = glm::distance(particles[((i+shear[x][0])*CSIZE) + (j + shear[x][1])].getCurrentPosition(), particles[(i*CSIZE) + j].getCurrentPosition());
					glm::vec3 norm = glm::normalize(particles[((i+shear[x][0])*CSIZE) + (j + shear[x][1])].getCurrentPosition() - particles[(i*CSIZE) + j].getCurrentPosition());
					glm::vec3 velR = particles[((i+shear[x][0])*CSIZE) + (j + shear[x][1])].getVelocity() - particles[(i*CSIZE) + j].getVelocity();
					glm::vec3 force = ((kElastic*(dist - CDIST2)) + (kDumping * (glm::dot(velR, norm))))*norm;
					particles[(i*CSIZE) + j].addForce(force);
				}
			}
			//bend
			for (int x = 0; x < bend.size(); x++){
				if (cinside((i + bend[x][0]), (j + bend[x][1]))){
					float dist = glm::distance(particles[((i+bend[x][0])*CSIZE) + (j + bend[x][1])].getCurrentPosition(), particles[(i*CSIZE) + j].getCurrentPosition());
					glm::vec3 norm = glm::normalize(particles[((i+bend[x][0])*CSIZE) + (j + bend[x][1])].getCurrentPosition() - particles[(i*CSIZE) + j].getCurrentPosition());
					glm::vec3 velR = particles[((i+bend[x][0])*CSIZE) + (j + bend[x][1])].getVelocity() - particles[(i*CSIZE) + j].getVelocity();
					glm::vec3 force = ((kElastic*(dist - (CDIST*2))) + (kDumping * (glm::dot(velR, norm))))*norm;
					particles[(i*CSIZE) + j].addForce(force);
				}
			}
			*/
		}
	}
}