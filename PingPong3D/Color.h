#pragma once
#include <iostream>
#include <string>
using namespace std;

class Color
{
private:
	int r;
	int g;
	int b;

public:
	Color() {
		r = 0;
		g = 0;
		b = 0;
	}
	Color(int red, int green, int blue) {
		SetRed(red);
		SetGreen(green);
		SetBlue(blue);
	}

	void SetRed(int value) {
		if (value < 0)
			value = 0;
		if (value > 255)
			value = 255;
		r = value;
	}
	void SetGreen(int value) {
		if (value < 0)
			value = 0;
		if (value > 255)
			value = 255;
		g = value;
	}
	void SetBlue(int value) {
		if (value < 0)
			value = 0;
		if (value > 255)
			value = 255;
		b = value;
	}

	int GetRed() {
		return r;
	}
	int GetGreen() {
		return g;
	}
	int GetBlue() {
		return b;
	}

	float GetRedFloat() {
		return (float)r/255.0f;
	}
	float GetGreenFloat() {
		return (float)g/255.0f;
	}
	float GetBlueFloat() {
		return (float)b/255.0f;
	}

	string ToString() {
		return "rgb(" + to_string(r) + ", " + to_string(g) + ", " + to_string(b) + ")";
	}

	friend ostream& operator<< (ostream& output, Color& obj) {
		output << obj.ToString();
		return output;
	}
};

