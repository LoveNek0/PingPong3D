#pragma once
#include <string>
#include "BallScript.h"
#include "TextField.h"
#include "Time.h"
#include "ScoreManager.h"

class GameBallScript : public BallScript {
public:
	TextField* timerText;
	TextField* scoreText;
	TextField* gameEndMessageText;

	ObjectScript* racketScript_1;
	ObjectScript* racketScript_2;

	std::function<void(void)> onEndAndSpace = []() {};

	int score_1 = 0;
	int score_2 = 0;

	string name_1 = "";
	string name_2 = "";

	milliseconds startTime;

	bool gameOver = false;

	bool placeBall = true;

	Score::GameType gameType = Score::SINGLE;

	unsigned long long lastTime;

	void OnTableInit() {
		startTime = Time::GetTime();
		lastTime = Time::GetMS();
		placeBall = true;
		dirrection = Vector2D::Rotate(dirrection, RandomFloat(-0.5f, 0.5f));
		speed = startSpeed;
	}

	void OnKickBall(Player player) {
			if (player == FIRST)
				score_1++;
			else
				score_2++;
	}

	void OnGameEnd(Player winner) {
			int w = 0;// 7 * 18 + 9;
			string result = "";
			result += "             Game Over\n\n";
			result += "Winner: "; // 7 * 18 + 9
			if (winner == FIRST) {
				result += name_1 + "\n"; // 11*18 + 9
				w += name_1.length() * 18 + 2 * 9;
			}
			else {
				if (name_2 == "") {
					result += "Bot\n";
					w += 3 * 18 + 9;
				}
				else {
					result += name_2 + "\n"; // 12*18 + 9
					w += name_2.length() * 18 + 9;
				}
			}
			result += "Score: " + ((winner == FIRST) ? to_string(score_1) : to_string(score_2)) + "\n";
			result += "Time: ";
			milliseconds endTime = Time::GetTime();
			int time_m = ((endTime - startTime).count() / 1000) / 60;
			int time_s = ((endTime - startTime).count() / 1000) % 60;

			if (time_m < 10)
				result += "0";
			result += to_string(time_m) + ":";

			if (time_s < 10)
				result += "0";
			result += to_string(time_s);
			result += "\n\n";
			result += "Press SPACE to continue";

			gameEndMessageText->text = result;

			if (winner == FIRST)
				ScoreManager::AddScore((name_2 == "" ? 0 : 1), startSpeed, Score(name_1, score_1, (endTime - startTime).count()));
			if (winner == SECOND)
				if (name_2 != "")
					ScoreManager::AddScore((name_2 == "" ? 0 : 1), startSpeed, Score(name_2, score_2, (endTime - startTime).count()));

			gameEndMessageText->position.x = (GetGameObject()->GetScene()->GetWindow()->GetSize().x - (float)w) / 2.0;
			gameEndMessageText->position.y = (GetGameObject()->GetScene()->GetWindow()->GetSize().y - 5.0 * 18.0) / 2.0;
			racketScript_1->active = false;
			racketScript_2->active = false;
			gameOver = true;
	}

	void OnUpdate() {
		if (!placeBall) {
			if (!gameOver) {
				BallScript::OnUpdate();

				scoreText->text = "Score (Player 1): " + to_string(score_1);
				scoreText->text += "\nScore (Player 2): " + to_string(score_2);
				timerText->text = "Time: ";

				milliseconds c = Time::GetTime();

				int time_m = ((c - startTime).count() / 1000) / 60;
				int time_s = ((c - startTime).count() / 1000) % 60;

				if (time_m < 10)
					timerText->text += "0";
				timerText->text += to_string(time_m) + ":";

				if (time_s < 10)
					timerText->text += "0";
				timerText->text += to_string(time_s);
			}
			else {
				if (GetGameObject()->GetScene()->GetWindow()->GetInput()->keyboard->GetKey(SPACE)) {
					onEndAndSpace();
				}
			}
		}
		else {
			racketScript_1->active = false;
			racketScript_2->active = false;

			if (Time::GetMS() - lastTime > 150) {
				if (GetGameObject()->GetScene()->GetWindow()->GetInput()->keyboard->GetKey(ENTER)) {
					placeBall = false;
					racketScript_1->active = true;
					racketScript_2->active = true;
					startTime = Time::GetTime();
					lastTime = Time::GetMS();
				}
			}
			
			if (GetGameObject()->GetScene()->GetWindow()->GetInput()->keyboard->GetKey('W'))
				if (GetGameObject()->transform.position.x + 100 * Time::DeltaTime() > 80)
					GetGameObject()->transform.position.x = 80;
				else
					GetGameObject()->transform.position.x += 100 * Time::DeltaTime();
			else if (GetGameObject()->GetScene()->GetWindow()->GetInput()->keyboard->GetKey('A'))
				if (GetGameObject()->transform.position.y + 100 * Time::DeltaTime() > 45)
					GetGameObject()->transform.position.y = 45;
				else
					GetGameObject()->transform.position.y += 100 * Time::DeltaTime();
			else if (GetGameObject()->GetScene()->GetWindow()->GetInput()->keyboard->GetKey('S'))
				if (GetGameObject()->transform.position.x - 100 * Time::DeltaTime() < -80)
					GetGameObject()->transform.position.x = -80;
				else
					GetGameObject()->transform.position.x -= 100 * Time::DeltaTime();
			else if (GetGameObject()->GetScene()->GetWindow()->GetInput()->keyboard->GetKey('D'))
				if (GetGameObject()->transform.position.y - 100 * Time::DeltaTime() < -45)
					GetGameObject()->transform.position.y = -45;
				else
					GetGameObject()->transform.position.y -= 100 * Time::DeltaTime();
		}
	}
};