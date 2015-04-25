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
public:
	Corda();
	~Corda();
	void reset(corda_mode mode);
};

