#include "Geometry.h"

Geometry::Geometry()
{
	maxObjects = 0;
}

Geometry::~Geometry()
{
	for (int i = 0; i < NUM_PRIMITIVES; i++) delete[] _data[i];
}

std::vector<glm::vec3> createSphere(float Radius, int Resolution){

	// vertice positions
	std::vector<glm::vec3> v;

	// iniatiate the variable we are going to use
	float X1, Y1, X2, Y2, Z1, Z2;
	float inc1, inc2, inc3, inc4, inc5, Radius1, Radius2;

	for (int w = 0; w < Resolution; w++) {
		for (int h = (-Resolution / 2); h < (Resolution / 2); h++){

			inc1 = (w / (float)Resolution) * 2 * PI;
			inc2 = ((w + 1) / (float)Resolution) * 2 * PI;

			inc3 = (h / (float)Resolution)*PI;
			inc4 = ((h + 1) / (float)Resolution)*PI;

			X1 = sin(inc1);
			Y1 = cos(inc1);
			X2 = sin(inc2);
			Y2 = cos(inc2);

			// store the upper and lower radius, remember everything is going to be drawn as triangles
			Radius1 = Radius*cos(inc3);
			Radius2 = Radius*cos(inc4);

			Z1 = Radius*sin(inc3);
			Z2 = Radius*sin(inc4);

			// insert the triangle coordinates
			v.push_back(glm::vec3(Radius1*X1, Z1, Radius1*Y1));
			v.push_back(glm::vec3(Radius1*X2, Z1, Radius1*Y2));
			v.push_back(glm::vec3(Radius2*X2, Z2, Radius2*Y2));

			v.push_back(glm::vec3(Radius1*X1, Z1, Radius1*Y1));
			v.push_back(glm::vec3(Radius2*X2, Z2, Radius2*Y2));
			v.push_back(glm::vec3(Radius2*X1, Z2, Radius2*Y1));
		}
	}
	return v;
}

void Geometry::initPrimitives() {
	// CUBE
	maxVertices[0] = 36;
	_data[0] = new Vertex[36];
	_data[0][0].setPosition(-0.5f, 0.5f, -0.5f);
	_data[0][1].setPosition(-0.5f, -0.5f, -0.5f);
	_data[0][2].setPosition(0.5f, -0.5f, -0.5f);
	_data[0][3].setPosition(0.5f, -0.5f, -0.5f);
	_data[0][4].setPosition(0.5f, 0.5f, -0.5f);
	_data[0][5].setPosition(-0.5f, 0.5f, -0.5f);

	_data[0][6].setPosition(0.5f, -0.5f, -0.5f);
	_data[0][7].setPosition(0.5f, -0.5f, 0.5f);
	_data[0][8].setPosition(0.5f, 0.5f, 0.5f);
	_data[0][9].setPosition(0.5f, 0.5f, 0.5f);
	_data[0][10].setPosition(0.5f, 0.5f, -0.5f);
	_data[0][11].setPosition(0.5f, -0.5f, -0.5f);

	_data[0][12].setPosition(0.5f, 0.5f, 0.5f);
	_data[0][13].setPosition(0.5f, -0.5f, 0.5f);
	_data[0][14].setPosition(-0.5f, -0.5f, 0.5f);
	_data[0][15].setPosition(-0.5f, -0.5f, 0.5f);
	_data[0][16].setPosition(-0.5f, 0.5f, 0.5f);
	_data[0][17].setPosition(0.5f, 0.5f, 0.5f);

	_data[0][18].setPosition(-0.5f, -0.5f, -0.5f);
	_data[0][19].setPosition(-0.5f, -0.5f, 0.5f);
	_data[0][20].setPosition(-0.5f, 0.5f, 0.5f);
	_data[0][21].setPosition(-0.5f, 0.5f, 0.5f);
	_data[0][22].setPosition(-0.5f, 0.5f, -0.5f);
	_data[0][23].setPosition(-0.5f, -0.5f, -0.5f);

	_data[0][24].setPosition(0.5f, 0.5f, 0.5f);
	_data[0][25].setPosition(-0.5f, 0.5f, 0.5f);
	_data[0][26].setPosition(-0.5f, 0.5f, -0.5f);
	_data[0][27].setPosition(-0.5f, 0.5f, -0.5f);
	_data[0][28].setPosition(0.5f, 0.5f, -0.5f);
	_data[0][29].setPosition(0.5f, 0.5f, 0.5f);

	_data[0][30].setPosition(0.5f, -0.5f, 0.5f);
	_data[0][31].setPosition(-0.5f, -0.5f, 0.5f);
	_data[0][32].setPosition(-0.5f, -0.5f, -0.5f);
	_data[0][33].setPosition(-0.5f, -0.5f, -0.5f);
	_data[0][34].setPosition(0.5f, -0.5f, -0.5f);
	_data[0][35].setPosition(0.5f, -0.5f, 0.5f);

	for (int i = 0; i < maxVertices[0]; i++) _data[0][i].setColor(20, 200, 80, 255);

	// TRIANGLE
	maxVertices[1] = 3;
	_data[1] = new Vertex[3];
	_data[1][0].setPosition(0.0f, 1.0f, 0.0f);//front
	_data[1][1].setPosition(1.0f, -1.0f, 0.0f);
	_data[1][2].setPosition(-1.0f, -1.0f, 0.0f);

	for (int i = 0; i < maxVertices[1]; i++) _data[1][i].setColor(200, 30, 200, 255);

	// SPHERE
	std::vector<glm::vec3> v = createSphere(3.8, 30);
	for (int j = 2; j < 4; j++) {
		maxVertices[j] = v.size();
		_data[j] = new Vertex[maxVertices[j]];
		for (int i = 0; i < maxVertices[j]; i++)_data[j][i].setPosition(v[i].x, v[i].y, v[i].z);
	}
	for (int i = 0; i < maxVertices[2]; i++) _data[2][i].setColor(200, 0, 0, 255);
	for (int i = 0; i < maxVertices[3]; i++) _data[3][i].setColor(0, 0, 200, 255);

	// PLANES
	maxVertices[4] = 4;
	_data[4] = new Vertex[maxVertices[4]];
	_data[4][0].setPosition(-1.0f, 1.0f, 0.0f);
	_data[4][1].setPosition(1.0f, 1.0f, 0.0f);
	_data[4][2].setPosition(1.0f, -1.0f, 0.0f);
	_data[4][3].setPosition(-1.0f, -1.0f, 0.0f);
	for (int i = 0; i < maxVertices[4]; i++) _data[4][i].setColor(255, 200, 0, 255);

	maxVertices[5] = 4;
	_data[5] = new Vertex[maxVertices[5]];
	_data[5][0].setPosition(0.0f, 1.0f, -1.0f);
	_data[5][1].setPosition(0.0f, 1.0f, 1.0f);
	_data[5][2].setPosition(0.0f, -1.0f, 1.0f);
	_data[5][3].setPosition(0.0f, -1.0f, -1.0f);
	for (int i = 0; i < maxVertices[5]; i++) _data[5][i].setColor(255, 200, 0, 255);

	maxVertices[6] = 4;
	_data[6] = new Vertex[maxVertices[6]];
	_data[6][0].setPosition(-1.0f, 0.0f, 1.0f);
	_data[6][1].setPosition(1.0f, 0.0f, 1.0f);
	_data[6][2].setPosition(1.0f, 0.0f, -1.0f);
	_data[6][3].setPosition(-1.0f, 0.0f, -1.0f);
	for (int i = 0; i < maxVertices[6]; i++) _data[6][i].setColor(255, 200, 0, 255);
}

void Geometry::LoadScene(string fileName) {
	ifstream file;
	file.open(fileName);
	if (file.is_open()) {
		file >> maxObjects;
		_objects.reserve(maxObjects);
		if (_objects.size() == 0) {
			for (int i = 0; i < maxObjects; i++) {
				GameObject newObject;
				file >> newObject._objectType;
				file >> newObject._translation.x;
				file >> newObject._translation.y;
				file >> newObject._translation.z;
				file >> newObject._angle;
				file >> newObject._rotation.x;
				file >> newObject._rotation.y;
				file >> newObject._rotation.z;
				file >> newObject._scale.x;
				file >> newObject._scale.y;
				file >> newObject._scale.z;
				file >> newObject._mode;
				_objects.push_back(newObject);
			}
		}
		file.close();
	}
	else {
		string errorMessage = "System was not able to open: " + fileName;
		ErrorManagement::errorRunTime(errorMessage);
	}
}