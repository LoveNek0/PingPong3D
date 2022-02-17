#pragma once
#include "Scene.h"
#include "MenuScript.h"
#include "AIRacketScript.h"
#include "MenuBallScript.h"
#include "RacketScript.h"
#include "GameBallScript.h"

class SceneManager {
public:
	static Scene* MainMenu() {
		Scene* scene = new Scene();

		TextField* menu = new TextField("menu");
		TextField* score = new TextField("score", "", 20, 20, Color(230, 230, 230));
		TextField* aboutText = new TextField("about", "", 20, 20, Color(230, 230, 230));

		menu->color = Color(255, 255, 255);
		menu->position.x = 15;
		menu->position.y = 15;
		GameObject* eventHandler = new GameObject("event_handler");
		MenuScript* menuScript = new MenuScript();
		menuScript->menu = menu;
		menuScript->single = [scene](float speed, string n_1) { scene->GetWindow()->SetScene(Singleplayer(speed, n_1)); };
		menuScript->multi = [scene](float speed, string n_1, string n_2) { scene->GetWindow()->SetScene(Multiplayer(speed, n_1, n_2)); };
		menuScript->score = [menuScript]() {
			menuScript->showScore = true;
		};
		menuScript->about = [menuScript]() {
			menuScript->showAbout = true;
		};
		menuScript->exit = []() { exit(0); };
		menuScript->scoreText = score;
		menuScript->aboutText = aboutText;

		eventHandler->AddScript(menuScript);
		scene->AddObject(eventHandler);
		scene->AddText(menu);
		scene->AddText(score);
		scene->AddText(aboutText);

		GameObject* table = GameObject::Open("Objects/Table.3d", "table");
		GameObject* racket1 = GameObject::Open("Objects/Racket.3d", "r1");
		GameObject* racket2 = GameObject::Open("Objects/Racket.3d", "r2");
		GameObject* ball = GameObject::Open("Objects/Ball.3d", "ball");
		ball->transform.position.z = 2;

		AIRacketScript* r1 = new AIRacketScript();
		AIRacketScript* r2 = new AIRacketScript();
		MenuBallScript* b = new MenuBallScript();
		b->playerObject_1 = racket1;
		b->playerObject_2 = racket2;

		r1->ball = ball;
		r2->ball = ball;

		r1->player = AIRacketScript::FIRST;
		r2->player = AIRacketScript::SECOND;

		racket1->AddScript(r1);
		racket2->AddScript(r2);

		ball->AddScript(b);

		menuScript->table = table;

		scene->AddObject(table);
		scene->AddObject(racket1);
		scene->AddObject(racket2);
		scene->AddObject(ball);


		return scene;
	}

	static Scene* Singleplayer(float speed, string n_1) {
		Scene* scene = new Scene();

		/* Text Objects */
		TextField* timer = new TextField("timer", "Time: 00:00:00", 20, 20, Color(255, 255, 255));
		TextField* score = new TextField("score", "Score: 0", 20, 40, Color(255, 255, 255));
		TextField* gameEnd = new TextField("end", "", 0, 0, Color(255, 255, 255));
		/* End Text Objects*/

		/* Game Objects */
		GameObject* table = GameObject::Open("Objects/Table.3d", "table");
		GameObject* ball = GameObject::Open("Objects/Ball.3d", "ball");
		GameObject* racket_1 = GameObject::Open("Objects/Racket.3d", "racket_1");
		GameObject* racket_2 = GameObject::Open("Objects/Racket.3d", "racket_2");

		TableScript* tableScript = new TableScript();
		tableScript->defaultRotation = Vector3D(5, 355, 224.8f);

		table->AddScript(tableScript);
		table->transform.rotation.SetX(5);
		table->transform.rotation.SetY(355);
		table->transform.rotation.SetZ(224.8);

		GameBallScript* ballScript = new GameBallScript();
		ballScript->gameType = Score::SINGLE;
		ballScript->gameEndMessageText = gameEnd;
		ballScript->playerObject_1 = racket_1;
		ballScript->playerObject_2 = racket_2;
		ballScript->timerText = timer;
		ballScript->scoreText = score;
		ballScript->startSpeed = speed;
		ballScript->name_1 = n_1;

		ballScript->onEndAndSpace = [scene]() {
			scene->GetWindow()->SetScene(MainMenu());
		};
		ball->AddScript(ballScript);

		RacketScript* racketScript_1 = new RacketScript();
		racketScript_1->player = RacketScript::FIRST;
		racket_1->AddScript(racketScript_1);

		AIRacketScript* racketScript_2 = new AIRacketScript();
		racketScript_2->ball = ball;
		racketScript_2->player = AIRacketScript::SECOND;
		racket_2->AddScript(racketScript_2);


		ballScript->racketScript_1 = racketScript_1;
		ballScript->racketScript_2 = racketScript_2;
		/* End Game Objects*/

		scene->AddObject(table);
		scene->AddObject(ball);
		scene->AddObject(racket_1);
		scene->AddObject(racket_2);

		scene->AddText(timer);
		scene->AddText(score);
		scene->AddText(gameEnd);

		return scene;
	}

	static Scene* Multiplayer(int speed, string n_1, string n_2) {
		Scene* scene = new Scene();

		/* Text Objects */
		TextField* timer = new TextField("timer", "Time: 00:00:00", 20, 20, Color(255, 255, 255));
		TextField* score = new TextField("score", "Score: 0", 20, 40, Color(255, 255, 255));
		TextField* gameEnd = new TextField("end", "", 0, 0, Color(255, 255, 255));
		/* End Text Objects*/

		/* Game Objects */
		GameObject* table = GameObject::Open("Objects/Table.3d", "table");
		GameObject* ball = GameObject::Open("Objects/Ball.3d", "ball");
		GameObject* racket_1 = GameObject::Open("Objects/Racket.3d", "racket_1");
		GameObject* racket_2 = GameObject::Open("Objects/Racket.3d", "racket_2");

		TableScript* tableScript = new TableScript();
		tableScript->defaultRotation = Vector3D(5, 355, 224.8f);

		table->AddScript(tableScript);
		table->transform.rotation.SetX(5);
		table->transform.rotation.SetY(355);
		table->transform.rotation.SetZ(224.8);

		GameBallScript* ballScript = new GameBallScript();
		ballScript->gameType = Score::MULTI;
		ballScript->gameEndMessageText = gameEnd;
		ballScript->playerObject_1 = racket_1;
		ballScript->playerObject_2 = racket_2;
		ballScript->timerText = timer;
		ballScript->scoreText = score;
		ballScript->name_1 = n_1;
		ballScript->name_2 = n_2;
		ballScript->startSpeed = speed;
		ballScript->onEndAndSpace = [scene]() {
			scene->GetWindow()->SetScene(MainMenu());
		};
		ball->AddScript(ballScript);

		RacketScript* racketScript_1 = new RacketScript();
		racketScript_1->player = RacketScript::FIRST;
		racket_1->AddScript(racketScript_1);

		RacketScript* racketScript_2 = new RacketScript();
		racketScript_2->player = RacketScript::SECOND;
		racket_2->AddScript(racketScript_2);


		ballScript->racketScript_1 = racketScript_1;
		ballScript->racketScript_2 = racketScript_2;
		/* End Game Objects*/

		scene->AddObject(table);
		scene->AddObject(ball);
		scene->AddObject(racket_1);
		scene->AddObject(racket_2);

		scene->AddText(timer);
		scene->AddText(score);
		scene->AddText(gameEnd);

		return scene;
	}
};