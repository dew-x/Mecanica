#include "Cube.h"


Cube::Cube(const glm::vec3 &c, const glm::vec3 &d){
	center = c;
	distances = d;
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
		//top triangles
			{ center.x, center.y + distances.y, center.z },
			{ center.x, center.y + distances.y, center.z + distances.z },
			{ center.x + distances.x, center.y + distances.y, center.z },

			{ center.x + distances.x, center.y + distances.y, center.z },
			{ center.x, center.y + distances.y, center.z + distances.z },
			{ center.x + distances.x, center.y + distances.y, center.z + distances.z },
		//bot triangles
			{ center.x, center.y, center.z },
			{ center.x, center.y, center.z + distances.z },
			{ center.x + distances.x, center.y, center.z },
		
			{ center.x + distances.x, center.y, center.z },
			{ center.x, center.y, center.z + distances.z },
			{ center.x + distances.x, center.y, center.z + distances.z },
		//front triangles
			{ center.x, center.y, center.z },
			{ center.x, center.y + distances.y, center.z },
			{ center.x + distances.x, center.y, center.z },

			{ center.x + distances.x, center.y, center.z },
			{ center.x, center.y + distances.y, center.z },
			{ center.x + distances.x, center.y + distances.y, center.z },
		//left triangles
			{ center.x, center.y, center.z },
			{ center.x, center.y, center.z + distances.z },
			{ center.x, center.y + distances.y, center.z },

			{ center.x, center.y + distances.y, center.z },
			{ center.x, center.y + distances.y, center.z + distances.z },
			{ center.x, center.y, center.z + distances.z },
		//back triangles
			{ center.x, center.y, center.z + distances.z },
			{ center.x, center.y + distances.y, center.z + distances.z },
			{ center.x + distances.x, center.y, center.z + distances.z },

			{ center.x + distances.x, center.y, center.z + distances.z },
			{ center.x + distances.x, center.y + distances.y, center.z + distances.z },
			{ center.x, center.y + distances.y, center.z + distances.z },
		//right triangles
			{ center.x + distances.x, center.y, center.z + distances.z },
			{ center.x + distances.x, center.y + distances.y, center.z + distances.z },
			{ center.x + distances.x, center.y, center.z },

			{ center.x + distances.x, center.y + distances.y, center.z }, 
			{ center.x + distances.x, center.y, center.z },
			{ center.x + distances.x, center.y + distances.y, center.z + distances.z },
		//all are 
	};
	return cubeQuads;
}

bool Cube::isInside(glm::vec3 particle){
	if (particle.x < (center.x + distances.x) && particle.y < (center.y + distances.y) && particle.z < (center.z + distances.z)) return true;
	else return false;
}



