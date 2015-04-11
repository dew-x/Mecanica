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



