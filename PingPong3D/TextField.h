#pragma once
#include <iostream>
#include <GL/openglut.h>
#include "Color.h"
using namespace std;

class TextField {
private:
	string id;

public:
	string text = "";
	Color color = Color();
	Vector2D position;

	TextField(string id) {
		this->id = id;
		this->text = "";
		position = Vector2D();
	}
	TextField(string id, string text) {
		this->id = id;
		this->text = text;
		position = Vector2D();
	}
	TextField(string id, string text, float x, float y) {
		this->id = id;
		this->text = text;
		position = Vector2D(x, y);
	}
	TextField(string id, string text, float x, float y, Color color) {
		this->id = id;
		this->text = text;
		position = Vector2D(x, y);
		this->color = color;
	}

	string GetID() {
		return id;
	}
};