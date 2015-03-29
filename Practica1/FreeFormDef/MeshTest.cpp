#pragma once
#include "mesh.h"
#include "functions.h"
#include <iostream>
#include <iomanip>
#include <time.h>
#include <vector>
#include <glm/glm.hpp>
using namespace std;

#define SIZE 20

/**
 MeshTest:
 1. Load an OBJ file, 
 2. Modify some of the vertex coordinates 
 3. Write the modified mesh in a new OBJ file
*/

void main() {
	clock_t t = clock();
	
	std::string name = "teapot";
	std::string fileIn = name + ".obj";
	std::string fileOut = name + "Mod.obj";
	Mesh mesh; 
	std::vector<int> binominal;
	preCalcBinominal(SIZE, binominal);
	std::vector<glm::vec3> vertexData;
	std::vector<glm::i32vec3> faceData;
	//-----------------------------------------------------
	//  Load a 3D mesh from an OBJ file, 
	//  modify the position of the vertex
	//  and write a new OBJ file.
	//-----------------------------------------------------

	mesh.loadObjModel(fileIn);//load a 3D model in OBJ format
	vertexData = mesh.returnMeshVertices();
	faceData = mesh.returnMeshFaces();
	std::cout << "Number of vertices = " << vertexData.size() << std::endl;
	std::cout << "Number of faces = " << faceData.size() << std::endl;
	glm::vec3 min = { vertexData[0].x, vertexData[0].y, vertexData[0].z };
	glm::vec3 max = { vertexData[0].x, vertexData[0].y, vertexData[0].z };
	for (int i = 1; i < vertexData.size(); i++) {
		if (vertexData[i].x < min.x) min.x = vertexData[i].x;
		if (vertexData[i].y < min.y) min.y = vertexData[i].y;
		if (vertexData[i].z < min.z) min.z = vertexData[i].z;
		if (vertexData[i].x > max.x) max.x = vertexData[i].x;
		if (vertexData[i].y > max.y) max.y = vertexData[i].y;
		if (vertexData[i].z > max.z) max.z = vertexData[i].z;
	}
	glm::vec3 width = max - min;
	std::cout <<"MIN "<< min.x << " " << min.y << " " << min.z << std::endl;
	std::cout <<"MAX "<< max.x << " " << max.y << " " << max.z << std::endl;
	std::cout << "WIDTH " << width.x << " " << width.y << " " << width.z << std::endl;
	vector<vector<vector<glm::vec3> > > grid(SIZE + 1, vector<vector<glm::vec3> >(SIZE+1, vector<glm::vec3>(SIZE+1)));
	for (int i = 0; i <= SIZE; ++i) {
		for (int j = 0; j <= SIZE; ++j) {
			for (int k = 0; k <= SIZE; ++k) {
				glm::vec3 coord = { ((float)i / SIZE), ((float)j / SIZE), ((float)k / SIZE) };
				grid[i][j][k] = min + (coord*width);
				//cout << i << " " << j << " " << k << " -> " << grid[i][j][k].x << " " << grid[i][j][k].y << " " << grid[i][j][k].z<< endl;
			}
		}
	}
	
	// taper
	//taper(grid, min, max);
	// twist
	twist(grid, min, max, 1.0);
	// recalc points
	glm::vec3 s_vertex = { width.x, 0, 0 };
	glm::vec3 t_vertex = { 0, width.y, 0 };
	glm::vec3 u_vertex = { 0, 0, width.z };
	//calc cross products
	glm::vec3 cp_s = glm::cross(t_vertex, u_vertex);
	glm::vec3 cp_t = glm::cross(s_vertex, u_vertex);
	glm::vec3 cp_u = glm::cross(s_vertex, t_vertex);
	float dt_s = glm::dot(cp_s, s_vertex);
	float dt_t = glm::dot(cp_t, t_vertex);
	float dt_u = glm::dot(cp_u, u_vertex);
	//create points
	vector<glm::vec3> points(vertexData.size());
	//double error = 0;
	for (int i = 0; i<vertexData.size(); ++i) {
		glm::vec3 vs = vertexData[i] - min;
		vs.x = (glm::dot(cp_s, vs)) / dt_s;
		vs.y = (glm::dot(cp_t, vs)) / dt_t;
		vs.z = (glm::dot(cp_u, vs)) / dt_u;
		//glm::vec3 vs1 = deform2(vs, SIZE, grid, binominal);
		vs = deform(vs, SIZE, grid, binominal);
		//error += glm::distance(vs,vs1);
		mesh.setVertex(i, vs.x, vs.y, vs.z);
	}
	//cout << "error " << error << endl;
	// create a new file with the modified mesh
	mesh.printObjModel(mesh, fileOut);
	cout <<"DONE IN " << double(clock() - t) / CLOCKS_PER_SEC << endl;
	system("PAUSE");
}