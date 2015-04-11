#include "Cube.h"


Cube::Cube(const glm::vec3 &d,const glm::vec3 &c ){
	distances = d;
	center = c;
}

Cube::~Cube(){
}

vector<glm::vec3> Cube::getVertices(){
	vector<glm::vec3> cubeVertices = {
		//bot 
			{center.x,center.y,center.z},
			{center.x,center.y,center.z + distances.z}, 
			{center.x + distances.x,center.y,center.z + distances.z}, 
			{center.x + distances.x,center.y,center.z}, 
		//top
			{center.x,center.y + distances.y,center.z}, 
			{center.x , center.y + distances.y,center.z + distances.z },
			{ center.x + distances.x, center.y + distances.y, center.z + distances.z },
			{ center.x + distances.x , center.y + distances.y,center.z }
	};
	return cubeVertices;
}

vector<glm::vec3> Cube::getQuads(){
	vector<glm::vec3> cubeQuads = {
		//top
			{ center.x, center.y + distances.y, center.z },
			{ center.x, center.y + distances.y, center.z + distances.z },
			{ center.x + distances.x, center.y + distances.y, center.z + distances.z },
			{ center.x + distances.x, center.y + distances.y, center.z },
		//bot
			{ center.x, center.y, center.z },
			{ center.x, center.y, center.z + distances.z },
			{ center.x + distances.x, center.y, center.z + distances.z },
			{ center.x + distances.x, center.y, center.z },
		//front
			{ center.x, center.y, center.z },
			{ center.x, center.y + distances.y, center.z },
			{ center.x + distances.x, center.y + distances.y, center.z },
			{ center.x + distances.x, center.y, center.z },
		//left
			{ center.x, center.y, center.z },
			{ center.x, center.y, center.z + distances.z },
			{ center.x, center.y + distances.y, center.z + distances.z },
			{ center.x, center.y + distances.y, center.z },
			//back
			{ center.x, center.y, center.z + distances.z },
			{ center.x, center.y + distances.y, center.z + distances.z },
			{ center.x + distances.x, center.y + distances.y, center.z + distances.z },
			{ center.x + distances.x, center.y, center.z + distances.z },
			//right
			{ center.x + distances.x, center.y, center.z + distances.z },
			{ center.x + distances.x, center.y + distances.y, center.z + distances.z },
			{ center.x + distances.x, center.y + distances.y, center.z }, 
			{ center.x + distances.x, center.y, center.z },
	};
	return cubeQuads;
}



