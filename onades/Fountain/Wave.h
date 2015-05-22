#pragma once
#include <vector>
#include <iostream>


#define CSIZE 40
#define CWAVE 1.96f
#define CDIST 0.2f
const float CDIST2 = CDIST*sqrt(2);

struct info{
	float height;
	float velocity;
	info *a, *b, *c, *d;
};

const std::vector<std::vector<int> > streach = {
		{ 1, 0 },
		{ -1, 0 },
		{ 0, 1 },
		{ 0, -1 }
};

class Wave
{
	std::vector<info> wave;
public:
	Wave();
	~Wave();

	void reset(float height);
	void movePoint();
	void moveWave();
	void updateVelocity(float deltaT);
};

