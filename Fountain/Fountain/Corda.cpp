#include "Corda.h"


Corda::Corda()
{
	reset(ANCHOR1);
}


Corda::~Corda()
{
}

void Corda::reset(corda_mode mode) {
	particles = std::vector<Particle>(0);
	for (unsigned i = 0; i < CORDA_SIZE; ++i) {
		Particle p();
	}
}
