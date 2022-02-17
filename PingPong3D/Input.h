#pragma once
#include "Mouse.h"
#include "Keyboard.h"

class Input {
public:
	Mouse* mouse;
	Keyboard* keyboard;

	Input(Mouse*& m, Keyboard*& k) {
		mouse = m;
		keyboard = k;
	}
};