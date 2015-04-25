#include "Corda.h"

float random(float min, float max) {
	float r = rand() / float(RAND_MAX);
	return min + (max - min)*r;
}

bool inside(float val, float min, float max) {
	return val >= min && val <= max;
}

Corda::Corda()
{
	reset(ANCHOR1);
	kElastic = 0.5;
	kDumping = 0.2;
}


Corda::~Corda()
{
}

void Corda::reset(corda_mode mode) {
	this->mode = mode;
	particles = std::vector<Particle>(CORDA_SIZE);
	float randx = 0.0f;//random(-3.0f, 3.0f);
	float randz = 0.0f;//random(-3.0f, 3.0f);
	for (unsigned i = 0; i < CORDA_SIZE; ++i) {
		float newz, newx;
		do {
			float ra = random(0, 2 * M_PI);
			newx = randx+cos(ra)*CORDA_DIST;
			newz = randz + sin(ra)*CORDA_DIST;
		} while (!inside(newx, -4.0f, 4.0f) || !inside(newz, -4.0, 4.0f));
		particles[i].setPosition({ newx, 5.0f, newz });
		particles[i].setForce({ 0.0f, -9.8f, 0.0f });
		particles[i].setBouncing(0.6f);
		randx = newx;
		randz = newz;
	}
}

