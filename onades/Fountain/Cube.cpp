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
	bool tx = (particle.x>center.x&&particle.x<center.x + distances.x);
	bool ty = (particle.y>center.y&&particle.y<center.y + distances.y);
	bool tz = (particle.z>center.z&&particle.z<center.z + distances.z);
	if (tx&&ty&&tz) return true;
	else return false;
}

glm::vec3 Cube::normalCol(glm::vec3 targ, glm::vec3 orig) {
	bool tx = (targ.x>center.x&&targ.x<center.x+distances.x);
	bool ox = (orig.x>center.x&&orig.x<center.x + distances.x);
	bool ty = (targ.y>center.y&&targ.y<center.y + distances.y);
	bool oy = (orig.y>center.y&&orig.y<center.y + distances.y);
	bool tz = (targ.z>center.z&&targ.z<center.z + distances.z);
	bool oz = (orig.z>center.z&&orig.z<center.z + distances.z);
	glm::vec3 v = { 0.0f, 0.0f, 0.0f };
	if (tx != ox) {
		v.x = orig.x - targ.x;
		return glm::normalize(v);
	}
	else if (ty != oy) {
		v.y = orig.y - targ.y;
		return glm::normalize(v);
	}
	else if (tz != oz) {
		v.z = orig.z - targ.z;
		return glm::normalize(v);
	}
	else {
		return v;
		cout << "BIG ERROR" << endl;
	}
}



