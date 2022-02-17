#pragma once
#include "Vector2D.h"

enum MouseButton {
	BUTTON_LEFT,
	BUTTON_RIGHT,
	BUTTON_MIDDLE
};

class Mouse {
private:
	Vector2D* position = new Vector2D();
	Vector2D* offset = new Vector2D();
	bool buttons[3] = { false, false, false };
public:
	Mouse(Vector2D*& p, Vector2D*& o, bool*& b) {
		p = position;
		o = offset;
		b = buttons;
	}

	bool GetButton(MouseButton button) {
		switch (button)
		{
		case MouseButton::BUTTON_LEFT:
			return buttons[0];
			break;
		case MouseButton::BUTTON_RIGHT:
			return buttons[1];
			break;
		case MouseButton::BUTTON_MIDDLE:
			return buttons[2];
			break;
		}
		return false;
	}
	Vector2D GetAxis() {
		return Vector2D(position->x, position->y);
	}
	Vector2D GetOffset() {
		return Vector2D(offset->x, offset->y);
	}
};