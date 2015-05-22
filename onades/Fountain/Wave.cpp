#include "Wave.h"

int coord(int x, int y){
	return x*CSIZE + y;
}

bool cinside(int x, int y){
	return x >= 0 && x < CSIZE && y >= 0 && y < CSIZE;
}

Wave::Wave(){
	wave = std::vector<info>(CSIZE*CSIZE);

	for (int i = 0; i < CSIZE; i++){
		for (int j = 0; j < CSIZE; j++){
			wave[coord(i, j)].velocity = 0.0;
			wave[coord(i, j)].height = 0.0;
			if (cinside(i + 1, j))wave[coord(i, j)].a = &wave[coord(i + 1, j)];
			else wave[coord(i, j)].a = &wave[coord(i - 1, j)];
			if (cinside(i - 1, j))wave[coord(i, j)].b = &wave[coord(i - 1, j)];
			else wave[coord(i, j)].b = &wave[coord(i + 1, j)];
			if (cinside(i, j + 1))wave[coord(i, j)].c = &wave[coord(i, j + 1)];
			else wave[coord(i, j)].c = &wave[coord(i, j - 1)];
			if (cinside(i, j - 1))wave[coord(i, j)].d = &wave[coord(i, j - 1)];
			else wave[coord(i, j)].d = &wave[coord(i, j + 1)];
		}
	}
}


Wave::~Wave()
{
}


void Wave::reset(float height){
	for (int i = 0; i < CSIZE*CSIZE; i++){
		wave[i].velocity = 0.0;
		wave[i].height = 0.0;
	}
}

void Wave::movePoint(){
	int x = rand() % (CSIZE*CSIZE);
	wave[x].height = 5;
}

void Wave::moveWave(){
	for (int i = 0; i < CSIZE; i++){
		wave[coord(i, 0)].height = 5;
	}
}

void Wave::updateVelocity(float deltaT){
	for (int i = 0; i < CSIZE*CSIZE; i++){
		wave[i].velocity += deltaT * CWAVE * (wave[i].a->height + wave[i].b->height + wave[i].c->height + wave[i].d->height - 4 * wave[i].height);
	}
	for (int i = 0; i < CSIZE*CSIZE; i++){
		wave[i].height += deltaT * wave[i].velocity;
	}
}