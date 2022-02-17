#pragma once
#include "ObjectScript.h"
#include "Log.h"

class RacketScript : public ObjectScript {
public:
	static enum Player {
		FIRST,
		SECOND
	};
	char left = 'a';
	char right = 'd';
	Player player = FIRST;
	float speed = 1.0f;

	void OnStart() {
		if (player == FIRST)
			GetGameObject()->transform.position.x = -98;
		else
			GetGameObject()->transform.position.x = 98;
	}

	void OnUpdate() {
		float step = 100 * speed * Time::DeltaTime();
		float s = 0;
		if (player == FIRST) {
			if (
				GetGameObject()->GetScene()->GetWindow()->GetInput()->keyboard->GetKey('a')
				||
				GetGameObject()->GetScene()->GetWindow()->GetInput()->keyboard->GetKey('ô')
				)
				s = step;
			if (
				GetGameObject()->GetScene()->GetWindow()->GetInput()->keyboard->GetKey('d')
				||
				GetGameObject()->GetScene()->GetWindow()->GetInput()->keyboard->GetKey('â')
				)
				s = -step;

		}
		if (player == SECOND) {
			if (GetGameObject()->GetScene()->GetWindow()->GetInput()->keyboard->GetSpecialKey(ARROW_LEFT))
				s = step;
			if (GetGameObject()->GetScene()->GetWindow()->GetInput()->keyboard->GetSpecialKey(ARROW_RIGHT))
				s = -step;
		}

		if (GetGameObject()->transform.position.y + s >= 40)
			s = 40.0f - GetGameObject()->transform.position.y;
		if (GetGameObject()->transform.position.y + s <= -40)
			s = -(40.0f + GetGameObject()->transform.position.y);

		GetGameObject()->transform.position.y += s;
	}
};