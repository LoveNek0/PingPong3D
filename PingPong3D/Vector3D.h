#pragma once
#include <iomanip>
#include <iostream>
using namespace std;

class Vector3D
{
private:

public:
	Vector3D() {
		this->x = 0;
		this->y = 0;
		this->z = 0;
	}
	Vector3D(float x, float y) {
		this->x = x;
		this->y = y;
		this->z = 0;
	}
	Vector3D(float x, float y, float z) {
		this->x = x;
		this->y = y;
		this->z = z;
	}

	float x;
	float y;
	float z;
	

	string ToString() {
		return "vector(" + to_string(x) + ", " + to_string(y) + ", " + to_string(z) + ")";
	}

	Vector3D operator+(Vector3D value) {
		Vector3D result = Vector3D(
			this->x + value.x,
			this->y + value.y,
			this->z + value.z
		);
		return result;
	}
	Vector3D operator-(Vector3D& value) {
		Vector3D result = Vector3D(
			this->x - value.x,
			this->y - value.y,
			this->z - value.z
		);
		return result;
	}
	float operator*(const Vector3D& right) {
		float result =
			this->x * right.x
			+
			this->y * right.y
			+
			this->z * right.z;
		return result;
	}
	Vector3D operator*(const float value) {
		Vector3D result = Vector3D(
			this->x * value,
			this->y * value,
			this->z * value
		);
		return result;
	}
	Vector3D operator/(const float value) {
		Vector3D result = Vector3D(
			this->x / value,
			this->y / value,
			this->z / value
		);
		return result;
	}

	friend ostream& operator<< (ostream& output, Vector3D& obj) {
		output << obj.ToString();
		return output;
	}
};