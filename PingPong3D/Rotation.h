#pragma once
#include <cmath>

class Rotation {
private:
	Vector3D rotation;

public:
	Rotation() {
		rotation = Vector3D();
	}
	Rotation(float x, float y, float z) {
		rotation = Vector3D();
		FromVector(Vector3D(x, y, z));
	}
	Rotation(Vector3D dirrection) {
		rotation = Vector3D();
		FromVector(dirrection);
	}

	void FromVector(Vector3D value) {
		SetX(value.x);
		SetY(value.y);
		SetZ(value.z);
	}
	Vector3D ToVector() {
		return rotation;
	}

	void SetX(float value) {
		value = fmod(value, 360);
		if (value < 0)
			value += 360;
		rotation.x = value;
	}
	void SetY(float value) {
		value = fmod(value, 360);
		if (value < 0)
			value += 360;
		rotation.y = value;
	}
	void SetZ(float value) {
		value = fmod(value, 360);
		if (value < 0)
			value += 360;
		rotation.z = value;
	}

	float GetX() {
		return rotation.x;
	}
	float GetY() {
		return rotation.y;
	}
	float GetZ() {
		return rotation.z;
	}

	void Rotate(float x, float y, float z) {
		SetX(GetX() + x);
		SetY(GetY() + y);
		SetZ(GetZ() + z);
	}
	void RotateTo(float x, float y, float z) {
		FromVector(Vector3D(x, y, z));
	}
};