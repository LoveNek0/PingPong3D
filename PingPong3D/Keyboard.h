#pragma once
#include <vector>
#include <string>
using namespace std;

enum SpecialKeys {
	ARROW_LEFT = 100,
	ARROW_RIGHT = 102,
	ARROW_UP = 101,
	ARROW_DOWN = 103,
	F5 = GLUT_KEY_F5
};

enum KeyboardKeys {
	ESC = 27,
	ENTER = 13,
	SPACE = 32,
	BACKSPACE = 8
};

class Keyboard {
private:
	vector<unsigned char>* pressedKeys = new vector<unsigned char>(0);
	vector<int>* pressedSpecial = new vector<int>(0);
	unsigned char *lastPressed;

public:
	Keyboard(vector<unsigned char>*& p, vector<int>*& s, unsigned char*lastChar) {
		p = pressedKeys;
		s = pressedSpecial;
		lastPressed = lastChar;
	}

	bool GetKey(unsigned char key) {
		key = tolower(key);
		for (unsigned char ch : *pressedKeys)
			if (ch == key)
				return true;
		return false;
	}

	bool GetSpecialKey(int key) {
		for (int i : *pressedSpecial)
			if (i == key)
				return true;
		return false;
	}

	bool GetSpecialKey(SpecialKeys key) {
		return GetSpecialKey((int)key);
	}

	bool GetKey(KeyboardKeys key) {
		return GetKey((unsigned char)key);
	}

	unsigned char GetPressed() {
		unsigned char l = *lastPressed;
		*lastPressed = '\0';
		return l;
	}
};