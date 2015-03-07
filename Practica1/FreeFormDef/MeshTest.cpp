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

	std::cout << min.x << " " << min.y << " " << min.z << std::endl;
	std::cout << max.x << " " << max.y << " " << max.z << std::endl;
	vector<vector<vector<glm::vec3> > > grid(SIZE + 1, vector<vector<glm::vec3> >(SIZE+1, vector<glm::vec3>(SIZE+1)));
	glm::vec3 width = max - min;
	for (int i = 0; i <= SIZE; ++i) {
		for (int j = 0; j <= SIZE; ++j) {
			for (int k = 0; k <= SIZE; ++k) {
				glm::vec3 coord = { ((float)i / SIZE)*width.x, ((float)j / SIZE)*width.y, ((float)k / SIZE)*width.z };
				grid[i][j][k] = min + coord;
				//cout << i << " " << j << " " << k << " -> " << grid[i][j][k].x << " " << grid[i][j][k].y << " " << grid[i][j][k].z<< endl;
			}
		}
	}
	
	// taper
	//taper(grid, min, max);
	// twist
	twist(grid, min, max, 1.0);
	// recalc points
	glm::vec3 s_vertex;
	glm::vec3 t_vertex;
	glm::vec3 u_vertex;
	//prepare S
	s_vertex.x = width.x;
	s_vertex.y = s_vertex.z = 0;
	//prepare T
	t_vertex.x = t_vertex.z = 0;
	t_vertex.y = width.y;
	//prepare U
	u_vertex.x = u_vertex.y = 0;
	u_vertex.z = width.z;
	//calc cross products
	glm::vec3 cp_s;
	glm::vec3 cp_t;
	glm::vec3 cp_u;
	cp_s = glm::cross(t_vertex, u_vertex);
	cp_t = glm::cross(s_vertex, u_vertex);
	cp_u = glm::cross(s_vertex, t_vertex);
	//create points
	vector<glm::vec3> points(vertexData.size());
	for (int i = 0; i<vertexData.size(); ++i) {
		//points[i] = (vertexData[i] - min);
		glm::vec3 vs;
		vs = vertexData[i] - min;
		points[i].x = (glm::dot(cp_s, vs)) / (glm::dot(cp_s, s_vertex));
		points[i].y = (glm::dot(cp_t, vs)) / (glm::dot(cp_t, t_vertex));
		points[i].z = (glm::dot(cp_u, vs)) / (glm::dot(cp_u, u_vertex));
		points[i] = deform(points[i], SIZE, grid, binominal);
	}
	// write the new mesh vertex
	for (int i = 0; i < vertexData.size(); i++) {
		mesh.setVertex(i, points[i].x, points[i].y, points[i].z);
	}
	// create a new file with the modified mesh
	mesh.printObjModel(mesh, fileOut);
	cout << double(clock() - t) / CLOCKS_PER_SEC << endl;
	system("PAUSE");
}