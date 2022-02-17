#pragma once
#include <vector>

using namespace std;

class Polygon3D
{
private:
	vector<Vector3D> drawpoints;

public:
	Color color;

	Polygon3D() {
		color = Color();
		drawpoints = vector<Vector3D>(0);
	}

	void AddPoint(Vector3D point) {
		drawpoints.push_back(point);
	}
	void AddPoint(float x, float y, float z) {
		AddPoint(Vector3D(x, y, z));
	}

	vector<Vector3D> GetPoints() {
		return drawpoints;
	}
};
