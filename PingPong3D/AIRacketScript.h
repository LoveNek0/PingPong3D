#pragma once
#include <math.h>
#include "ObjectScript.h"
#include "Log.h"


class AIRacketScript : public ObjectScript {
public:
	static enum Player {
		FIRST,
		SECOND
	};
	Player player = FIRST;
	GameObject* ball = NULL;
	float speed = 1.0f;

	void OnStart() {
		if (player == FIRST)
			GetGameObject()->transform.position.x = -98;
		else
			GetGameObject()->transform.position.x = 98;
	}

	void OnUpdate() {
		float distance_y = ball->transform.position.y - GetGameObject()->transform.position.y;
		float distance_x = ball->transform.position.x - GetGameObject()->transform.position.x;
		if (distance_y != 0) {
			float boost = 1.0f - (fabs(distance_x) / 200.0f);
			float step = 100.0f * Time::DeltaTime() * speed * boost;
			if (step > fabs(distance_y))
				step = distance_y;
			else
				if (distance_y < 0)
					step *= -1;

			if (GetGameObject()->transform.position.y + step >= 40)
				step = 40.0f - GetGameObject()->transform.position.y;
			if (GetGameObject()->transform.position.y + step <= -40)
				step = -40.0f - GetGameObject()->transform.position.y;

			GetGameObject()->transform.position.y += step;
		}
			

	}
};