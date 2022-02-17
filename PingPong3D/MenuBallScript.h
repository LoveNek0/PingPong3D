#pragma once
#include <string>
#include "ObjectScript.h"
#include "Log.h"
#include "BallScript.h"


class MenuBallScript : public BallScript {
public:
	void OnTableInit() {
		startSpeed = 2;
		speed = startSpeed;// RandomFloat(startSpeed - 0.5f, startSpeed + 0.5f);
	}

	void OnGameEnd(Player winner) {
		//Log::Debug("win: " + to_string((int)winner));
		//Log::Debug(GetGameObject()->transform.position.ToString());
		//active = false;

		InitTable();
	}

	void OnKickBall(Player player) {
		dirrection = Vector2D::Rotate(dirrection, RandomFloat(-0.5f, 0.5f));
		//speed = RandomFloat(startSpeed - 0.5f, startSpeed + 0.5f);
	}
};