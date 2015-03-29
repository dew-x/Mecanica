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
					{ cos(ry), -sin(ry),0 },
					{ sin(ry), cos(ry), 0},
					{ 0,0,1 }
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

glm::vec3 deform(glm::vec3 point, int size, const vector<vector<vector<glm::vec3> > > &grid, const vector<int> &binominal) {
	//cout << "b0 " << point.x << " " << point.y << " " << point.z << endl;
	glm::vec3 x,y,z;
	x = { 0, 0, 0 };
	vector<float> bs(size + 1), bt(size + 1), bu(size + 1);
	for (int i = 0; i <= size; i++) {
		bs[i] = bernstein(i, size, point.x, binominal);
		bt[i] = bernstein(i, size, point.y, binominal);
		bu[i] = bernstein(i, size, point.z, binominal);
	}
	for (int i = 0; i <= size; i++) {
		y = { 0, 0, 0 };
		for (int j = 0; j <= size; j++) {
			z = { 0, 0, 0 };
			for (int k = 0; k <= size; k++) {
				z += (bu[k]*grid[i][j][k]);
			}
			y += (bt[j] * z);
		}
		x += (bs[i] * y);
	}
	return x;
}
#define ZERO 1.1920929e-07F
inline bool fok(float a, float b) {
	int n, m;
	frexp(a, &n);
	frexp(b, &m);
	return abs(n - m) < 23;
}
glm::vec3 deform2(glm::vec3 point, int size, const vector<vector<vector<glm::vec3> > > &grid, const vector<int> &binominal) {
	//cout << "b0 " << point.x << " " << point.y << " " << point.z << endl;
	glm::vec3 x, y, z;
	x = { 0, 0, 0 };
	vector<float> bs(size + 1), bt(size + 1), bu(size + 1);
	for (int i = 0; i <= size; i++) {
		bs[i] = bernstein(i, size, point.x, binominal);
		bt[i] = bernstein(i, size, point.y, binominal);
		bu[i] = bernstein(i, size, point.z, binominal);
		cout <<i <<" "<< bs[i] << " " << bt[i] << " " << bu[i] << endl;
	}
	int minx, miny, minz, maxx,maxy,maxz;
	minx = miny = minz = 0;
	maxx = maxy = maxz = size;
	// calc limit i
	for (int i = 0; bs[i] < ZERO && i<=size; i++) minx = i + 1;
	for (int i = size; bs[i] < ZERO && i >=0; --i) maxx = i - 1;
	for (int i = 0; bt[i] < ZERO && i <= size; i++) miny = i + 1;
	for (int i = size; bt[i] < ZERO && i >= 0; --i) maxy = i - 1;
	for (int i = 0; bu[i] < ZERO && i <= size; i++) minz = i + 1;
	for (int i = size; bu[i] < ZERO && i >= 0; --i) maxz = i - 1;
	for (int i = minx; i <= maxx; i++) {
		y = { 0, 0, 0 };
		for (int j = miny; j <= maxy; j++) {
			z = { 0, 0, 0 };
			for (int k = minz; k <= maxz; k++) {
				z += (bu[k] * grid[i][j][k]);
			}
			y += (bt[j] * z);
		}
		x += (bs[i] * y);
	}
	return x;
}