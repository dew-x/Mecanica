#include "Cloth.h"


float mapf(float v, float a, float b, float c, float d) {
	return ((v - a) / (b - a))*(d - c) + c;
}

Cloth::Cloth()
{
}


Cloth::~Cloth()
{
}

void Cloth::reset(float height) {
	particles = std::vector<Particle>(CSIZE*CSIZE);
	for (unsigned i = 0; i < CSIZE; ++i) {
		for (unsigned j = 0; j < CSIZE; ++j) {
			particles[i].setPosition({ mapf(i, 0, CSIZE - 1, -(CSIZE*CDIST) / 2), height, mapf(j, 0, CSIZE - 1, -(CSIZE*CDIST) / 2) });
			particles[i].setForce({ 0.0f, -9.8f, 0.0f });
			particles[i].setBouncing(0.6f);
		}
	}
}
