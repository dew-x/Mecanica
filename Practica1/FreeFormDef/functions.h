#pragma once
#include <vector>
#include <glm/glm.hpp>
using namespace std;

void taper(vector<vector<vector<glm::vec3> > > &points, glm::vec3 origin, glm::vec3 final) {
	for (int i = 0; i < points.size(); ++i) {
		for (int j = 0; j < points[i].size(); ++j) {
			for (int k = 0; k < points[i][j].size(); ++k) {
				float x = points[i][j][k].x;
				float y, z;
				if (x <= origin.x) {
					y = z = 1;
				}
				else if (x <= final.x) {
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