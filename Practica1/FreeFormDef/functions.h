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
				else if (x >= final.x) {
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

void twist(vector<vector<vector<glm::vec3> > > &points, glm::vec3 origin, glm::vec3 final, double angle) {
	for (int i = 0; i < points.size(); ++i) {
		for (int j = 0; j < points[i].size(); ++j) {
			for (int k = 0; k < points[i][j].size(); ++k) {
				double ry = 0;
				float z = points[i][j][k].z;
				if (z >= final.z) ry = angle;
				else if (z> origin.z) ry = angle*((z-origin.z) / (final.z-origin.z));
				glm::mat3 mul = {
					{ cos(ry), 0, -sin(ry) },
					{ sin(ry), 0, cos(ry) },
					{ 0,1,0 }
				};
				points[i][j][k] = mul*points[i][j][k];
			}
		}
	}
}

void preCalcBinominal(int max, vector<int> &output) {
	output = vector<int> (max+1);
	int n = max;
	for (int i = 0; i <= max; ++i) {
		long long unsigned val = 1;
		int ni = n - i;
		if (ni < i) {
			for (int j = i + 1; j <= n; ++j) {
				val *= j;
			}
			for (int j = 2; j <= ni; ++j) {
				val /= j;
			}
		}
		else {
			for (int j = ni + 1; j <= n; ++j) {
				val *= j;
			}
			for (int j = 2; j <= i; ++j) {
				val /= j;
			}
		}
		output[i] = val;
	}
}

inline double bernstein(int k, int n, double v, const vector<int> &binominal) {
	return binominal[k] * pow(v, (double)k) * pow((1 - v), (double)(n - k));
}

glm::vec3 deform(glm::vec3 point, int SIZE, const vector<vector<vector<glm::vec3> > > &grid, const vector<int> &binominal) {
	//cout << "b0 " << point.x << " " << point.y << " " << point.z << endl;
	glm::vec3 ffd3, ffd2, ffd1;
	double bpS = 0, bpT = 0, bpU = 0;
	ffd1 = { 0, 0, 0 };
	for (int i = 0; i <= SIZE; i++) {
		ffd2 = { 0, 0, 0 };
		for (int j = 0; j <= SIZE; j++) {
			ffd3 = { 0, 0, 0 };
			for (int k = 0; k <= SIZE; k++) {
				bpU = bernstein(k, SIZE, point.z, binominal);
				ffd3 = ffd3 + ((float)bpU*grid[i][j][k]);
				//cout << "a3 " << ffd3.x << " " << ffd3.y << " " << ffd3.z << endl;
			}
			bpT = bernstein(j, SIZE, point.y, binominal);
			ffd2 = ffd2 + ((float)bpT * ffd3);
			//cout << "a2 " << ffd2.x << " " << ffd2.y << " " << ffd2.z << endl;
		}
		bpS = bernstein(i, SIZE, point.x, binominal);
		ffd1 = ffd1 + ((float)bpS * ffd2);
		//cout << "a1 " << ffd1.x << " " << ffd1.y << " " << ffd1.z << endl;
	}
	//cout << "a0 " << ffd1.x << " " << ffd1.y << " " << ffd1.z << endl;
	return ffd1;
}