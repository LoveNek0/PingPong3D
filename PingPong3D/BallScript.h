#pragma once
#include <string>
#include "ObjectScript.h"
#include "Log.h"
#include "Vector2D.h"
#include "Time.h"
#include "Vector3D.h"


class BallScript : public ObjectScript {
protected:
	float RandomFloat(float a, float b) {
		float result = .0f;
		while (result == .0f) {
			float random = ((float)rand()) / (float)RAND_MAX;
			float diff = b - a;
			float r = random * diff;
			result = a + r;
		}
		return result;
	}
	float clip(float value, float min, float max) {
		if (value > max)
			return max;
		if (value < min)
			return min;
		return value;
	}

public:
	static enum Player {
		FIRST,
		SECOND
	};

	GameObject* playerObject_1;
	GameObject* playerObject_2;

	float tableSize_x = 100;
	float tableSize_y = 50;

	float speed = 1.0f;
	float startSpeed;

	Vector2D dirrection;

	Vector2D offset;

	void InitTable() {
		dirrection = GetRandomDirrection(10, 1);
		GetGameObject()->transform.position = Vector3D(0, 0, 2);
		OnTableInit();
	}

	Vector2D GetRandomDirrection(float x, float y) {
		Vector2D v = Vector2D(RandomFloat(-x, x), RandomFloat(-y, y));
		return ToDirrection(v);
	}

	Vector2D ToDirrection(Vector2D v) {
		return v / sqrt((v.x) * (v.x) + (v.y) * (v.y));
	}

	virtual void OnGameStart() {

	}

	virtual void OnTableInit() {

	}

	virtual void OnGameEnd(Player winner) {

	}

	virtual void OnKickBall(Player player) {

	}

	void OnStart() {
		srand(static_cast <unsigned> (time(0)));
		OnGameStart();
		InitTable();
	}

	void OnUpdate() {
		dirrection = ToDirrection(dirrection);
		offset = dirrection * Time::DeltaTime() * 70 * speed;
		Vector2D currentPosition = Vector2D(GetGameObject()->transform.position.x, GetGameObject()->transform.position.y);
		if (currentPosition.x + 2 >= tableSize_x)
			OnGameEnd(FIRST);
		if (currentPosition.x - 2 <= -tableSize_x)
			OnGameEnd(SECOND);

		float distance_y_1 = playerObject_1->transform.position.y - currentPosition.y;
		float distance_y_2 = playerObject_2->transform.position.y - currentPosition.y;

		// Racket collision
		if (currentPosition.x + offset.x >= playerObject_2->transform.position.x - 4) {
			if (
				currentPosition.y + offset.y >= playerObject_2->transform.position.y - 10
				&&
				currentPosition.y + offset.y <= playerObject_2->transform.position.y + 10
				) {
				offset.x = (playerObject_2->transform.position.x - 4) - currentPosition.x;
				dirrection.x *= -1;

				OnKickBall(SECOND);
			}
		}
		else if (currentPosition.x + offset.x <= playerObject_1->transform.position.x + 4) {
			if (
				currentPosition.y + offset.y >= playerObject_1->transform.position.y - 10
				&&
				currentPosition.y + offset.y <= playerObject_1->transform.position.y + 10
				) {
				offset.x = -(-(playerObject_1->transform.position.x + 4) + currentPosition.x);
				dirrection.x *= -1;
				
				OnKickBall(FIRST);
			}
		}
		// End racket collision

		if (currentPosition.x + offset.x + 2 >= tableSize_x) {
			offset.x = tableSize_x - 2 - currentPosition.x;
			dirrection.x *= -1;
		}
		if (currentPosition.x + offset.x - 2 <= -tableSize_x) {
			offset.x = -((tableSize_x - 2) + currentPosition.x);
			dirrection.x *= -1;
		}
		if (currentPosition.y + offset.y + 2 >= tableSize_y) {
			offset.y = tableSize_y - 2 - currentPosition.y;
			dirrection.y *= -1;
		}
		if (currentPosition.y + offset.y - 2 <= -tableSize_y) {
			offset.y = -((tableSize_y - 2) + currentPosition.y);
			dirrection.y *= -1;
		}

		GetGameObject()->transform.position.x += offset.x;
		GetGameObject()->transform.position.y += offset.y;
	}
};