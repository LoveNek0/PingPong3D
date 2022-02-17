#pragma once
#include <iomanip>
#include <string>
#include <iostream>
using namespace std;

class Vector2D
{
private:

public:
	static Vector2D Rotate(Vector2D vec, float angle) {
		Vector2D result;
		result.x = vec.x * cos(angle) - vec.y * sin(angle);
		result.y = vec.x * sin(angle) + vec.y * cos(angle);
		return result;
	}

	Vector2D() {
		this->x = 0;
		this->y = 0;
	}
	Vector2D(float x, float y) {
		this->x = x;
		this->y = y;
	}

	float x;
	float y;
	
	string ToString() {
		return "vector(" + to_string(x) + ", " + to_string(y) + ")";
	}

	Vector2D operator+(Vector2D value) {
		Vector2D result = Vector2D(
			this->x + value.x,
			this->y + value.y
		);
		return result;
	}
	Vector2D operator-(Vector2D& value) {
		Vector2D result = Vector2D(
			this->x - value.x,
			this->y - value.y
		);
		return result;
	}
	float operator*(const Vector2D& right) {
		float result =
			this->x * right.x
			+
			this->y * right.y;
		return result;
	}
	Vector2D operator*(const float value) {
		Vector2D result = Vector2D(
			this->x * value,
			this->y * value
		);
		return result;
	}
	Vector2D operator/(const float value) {
		Vector2D result = Vector2D(
			this->x / value,
			this->y / value
		);
		return result;
	}

	friend ostream& operator<< (ostream& output, Vector2D& obj) {
		output << obj.ToString();
		return output;
	}
};