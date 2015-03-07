#pragma once
#include "mesh.h"
#include <iostream>
#include <iomanip>
#include <time.h>
using namespace std;

#define SIZE 20

void taper(vector<vector<vector<glm::vec3> > > &points, glm::vec3 origin, glm::vec3 final) {
	for (int i = 0; i < points.size(); ++i) {
		for (int j = 0; j < points[i].size(); ++j) {
			for (int k = 0; k < points[i][j].size(); ++k) {
				float x = points[i][j][k].x;
				float y,z;
				if (x <= origin.x) {
					y = z = 1;
				}
				else if (x<= final.x) {
					y = z = 0.5;
				}
				else {
					y = z = 1 - 0.5 * ((x - origin.x) / (final.x - origin.x));
				}
				glm::vec3 fac = { 1, y, z };
				points[i][j][k] *= fac;
			}
		}
	}
}

void twist(vector<vector<vector<glm::vec3> > > &points, glm::vec3 origin) {

}

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
		if (vertexData[i].x < min.x) min.x=vertexData[i].x;
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
				glm::vec3 coord = { (i / SIZE)*width.x, (j / SIZE)*width.y, (k / SIZE)*width.z };
				grid[i][j][k] = min + coord;
			}
		}
	}
	
	// taper
	taper(grid, min, max);
	// twist
	//twist(grid, min);
	// recalc points
	vector<glm::vec3> points(vertexData.size());
	for (int i = 0; i<vertexData.size(); ++i) {
		points[i] = (vertexData[i] - min);
	}
	//As exemple we modify one mesh vertex
	vertexData[5].x = 2.0f;
	vertexData[5].y = 2.0f;
	vertexData[5].z = 2.0f;
	// or the same way:	
	//mesh.setVertex(5, 2.0f, 2.0f, 2.0f);

	// write the new mesh vertex
	for (int i = 0; i < vertexData.size(); i++) {
		mesh.setVertex(i, vertexData[i].x*2, vertexData[i].y, vertexData[i].z);
	}
	// create a new file with the modified mesh
	mesh.printObjModel(mesh, fileOut);
	cout << double(clock() - t) / CLOCKS_PER_SEC << endl;
	system("PAUSE");
}