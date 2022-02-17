#pragma once
#include <string>
#include <stdlib.h>
#include <functional>
#include "ObjectScript.h"
#include "Log.h"
#include "TextField.h"
#include "ScoreManager.h"
using namespace std;

class MenuScript : public ObjectScript {
public:
	TextField* menu;
	TextField* scoreText;
	TextField* aboutText;
	GameObject* table;
	int selected = 0;
	unsigned long long last;
	bool showScore = false;
	bool showAbout = false;
	bool selectDifficulty = false;
	bool gameMode = false;
	bool inputName = false;
	bool inS = false;

	int diff = 0;

	unsigned long long pressed = 0;

	string name_1;
	string name_2;

	std::function<void(float, string)> single;
	std::function<void(float, string, string)> multi;
	std::function<void(void)> score;
	std::function<void(void)> about;
	std::function<void(void)> exit;

	void OnStart() {
		last = Time::GetMS();
	}

	void OnUpdate() {
		if (!showScore && !showAbout && !selectDifficulty && !inputName) {
			scoreText->text = "";
			aboutText->text = "";
			string items[5] = {
				"Singleplayer",
				"Multiplayer",
				"Score",
				"About",
				"Exit"
			};

			float t_x = menu->position.x;
			float t_y = menu->position.y;
			int m_x = GetGameObject()->GetScene()->GetWindow()->GetInput()->mouse->GetAxis().x;
			int m_y = GetGameObject()->GetScene()->GetWindow()->GetInput()->mouse->GetAxis().y;
			for (int i = 0; i < 5; i++) {
				if (
					m_x >= t_x
					&&
					m_x <= t_x + (items[i].length() + 18)
					) {
					if (
						m_y <= (t_y + (18 * (i + 1)))
						&&
						m_y >= (t_y + (18 * (i + 2)))
						) {
						selected = i;
						break;
					}
				}
			}

			if (
				!GetGameObject()->GetScene()->GetWindow()->GetInput()->keyboard->GetKey('w')
				&&
				!GetGameObject()->GetScene()->GetWindow()->GetInput()->keyboard->GetKey('s')
				&&
				!GetGameObject()->GetScene()->GetWindow()->GetInput()->keyboard->GetSpecialKey(ARROW_UP)
				&&
				!GetGameObject()->GetScene()->GetWindow()->GetInput()->keyboard->GetSpecialKey(ARROW_DOWN)
				)
				last = 0;
			if ((Time::GetMS() - last) >= 150) {
				if (
					GetGameObject()->GetScene()->GetWindow()->GetInput()->keyboard->GetKey('w')
					||
					GetGameObject()->GetScene()->GetWindow()->GetInput()->keyboard->GetSpecialKey(ARROW_UP)
					) {
					selected--;
					last = Time::GetMS();
				}
				if (
					GetGameObject()->GetScene()->GetWindow()->GetInput()->keyboard->GetKey('s')
					||
					GetGameObject()->GetScene()->GetWindow()->GetInput()->keyboard->GetSpecialKey(ARROW_DOWN)
					) {
					selected++;
					last = Time::GetMS();
				}
			}
			if (selected > 4)
				selected = 0;
			if (selected < 0)
				selected = 4;
			string str = "Menu\n";
			for (int i = 0; i < 5; i++)
				if (i == selected)
					str += "  >" + items[i] + "\n";
				else
					str += "    " + items[i] + "\n";
			menu->text = str;

			if ((Time::GetMS() - last) >= 150)
			if (GetGameObject()->GetScene()->GetWindow()->GetInput()->keyboard->GetKey(ENTER)) {
				switch (selected) {
				case 0:
					pressed = Time::GetMS();
					selectDifficulty = true;
					gameMode = false;
					break;
				case 1:
					pressed = Time::GetMS();
					selectDifficulty = true;
					gameMode = true;
					break;
				case 2:
					score();
					break;
				case 3:
					about();
					break;
				case 4:
					exit();
					break;
				}
				last = Time::GetMS();
			}
		}

		if (showScore) {
			if (GetGameObject()->GetScene()->GetWindow()->GetInput()->keyboard->GetKey(SPACE))
				showScore = false;
			if (GetGameObject()->GetScene()->GetWindow()->GetInput()->keyboard->GetSpecialKey(F5))
				ScoreManager::Clear();
			menu->text = "";
			string list = "Best Scores\n";
			list += "  Singleplayer\n";
			list += "    Easy\n";
			{
				list += "      Time      Winner      Score\n";
				Score* s = ScoreManager::GetScore(0, 1);
				list += "      ";
				if (s == NULL)
					list += "                 Score list is empty\n";
				else {
					if ((int)(s->timePlayed / 1000 / 60) < 10)
						list += "0";
					list += to_string((int)(s->timePlayed / 1000 / 60));
					list += ":";
					if ((int)(s->timePlayed / 1000) % 60 < 10)
						list += "0";
					list += to_string((int)(s->timePlayed / 1000) % 60);
					list += "     ";
					list += s->winner;
					for (int i = 0; i < 10 - s->winner.length(); i++)
						list += " ";
					list += "     ";
					if (s->score < 10000)
						list += "0";
					if (s->score < 1000)
						list += "0";
					if (s->score < 100)
						list += "0";
					if (s->score < 10)
						list += "0";
					list += to_string(s->score) + "\n";
				}
			}
			list += "    Normal\n";
			{
				list += "      Time      Winner      Score\n";
				Score* s = ScoreManager::GetScore(0, 2);
				list += "      ";
				if (s == NULL)
					list += "                 Score list is empty\n";
				else {
					if ((int)(s->timePlayed / 1000 / 60) < 10)
						list += "0";
					list += to_string((int)(s->timePlayed / 1000 / 60));
					list += ":";
					if ((int)(s->timePlayed / 1000) % 60 < 10)
						list += "0";
					list += to_string((int)(s->timePlayed / 1000) % 60);
					list += "     ";
					list += s->winner;
					for (int i = 0; i < 10 - s->winner.length(); i++)
						list += " ";
					list += "     ";
					if (s->score < 10000)
						list += "0";
					if (s->score < 1000)
						list += "0";
					if (s->score < 100)
						list += "0";
					if (s->score < 10)
						list += "0";
					list += to_string(s->score) + "\n";
				}
			}
			list += "    Hard\n";
			{
				list += "      Time      Winner      Score\n";
				Score* s = ScoreManager::GetScore(0, 3);
				list += "      ";
				if (s == NULL)
					list += "                 Score list is empty\n";
				else {
					if ((int)(s->timePlayed / 1000 / 60) < 10)
						list += "0";
					list += to_string((int)(s->timePlayed / 1000 / 60));
					list += ":";
					if ((int)(s->timePlayed / 1000) % 60 < 10)
						list += "0";
					list += to_string((int)(s->timePlayed / 1000) % 60);
					list += "     ";
					list += s->winner;
					for (int i = 0; i < 10 - s->winner.length(); i++)
						list += " ";
					list += "     ";
					if (s->score < 10000)
						list += "0";
					if (s->score < 1000)
						list += "0";
					if (s->score < 100)
						list += "0";
					if (s->score < 10)
						list += "0";
					list += to_string(s->score) + "\n";
				}
			}
			list += "\n  Multiplayer\n";
			list += "    Easy\n";
			{
				list += "      Time      Winner      Score\n";
				Score* s = ScoreManager::GetScore(1, 1);
				list += "      ";
				if (s == NULL)
					list += "                 Score list is empty\n";
				else {
					if ((int)(s->timePlayed / 1000 / 60) < 10)
						list += "0";
					list += to_string((int)(s->timePlayed / 1000 / 60));
					list += ":";
					if ((int)(s->timePlayed / 1000) % 60 < 10)
						list += "0";
					list += to_string((int)(s->timePlayed / 1000) % 60);
					list += "     ";
					list += s->winner;
					for (int i = 0; i < 10 - s->winner.length(); i++)
						list += " ";
					list += "     ";
					if (s->score < 10000)
						list += "0";
					if (s->score < 1000)
						list += "0";
					if (s->score < 100)
						list += "0";
					if (s->score < 10)
						list += "0";
					list += to_string(s->score) + "\n";
				}
			}
			list += "    Normal\n";
			{
				list += "      Time      Winner      Score\n";
				Score* s = ScoreManager::GetScore(1, 2);
				list += "      ";
				if (s == NULL)
					list += "                 Score list is empty\n";
				else {
					if ((int)(s->timePlayed / 1000 / 60) < 10)
						list += "0";
					list += to_string((int)(s->timePlayed / 1000 / 60));
					list += ":";
					if ((int)(s->timePlayed / 1000) % 60 < 10)
						list += "0";
					list += to_string((int)(s->timePlayed / 1000) % 60);
					list += "     ";
					list += s->winner;
					for (int i = 0; i < 10 - s->winner.length(); i++)
						list += " ";
					list += "     ";
					if (s->score < 10000)
						list += "0";
					if (s->score < 1000)
						list += "0";
					if (s->score < 100)
						list += "0";
					if (s->score < 10)
						list += "0";
					list += to_string(s->score) + "\n";
				}
			}
			list += "    Hard\n";
			{
				list += "      Time      Winner      Score\n";
				Score* s = ScoreManager::GetScore(1, 3);
				list += "      ";
				if (s == NULL)
					list += "                 Score list is empty\n";
				else {
					if ((int)(s->timePlayed / 1000 / 60) < 10)
						list += "0";
					list += to_string((int)(s->timePlayed / 1000 / 60));
					list += ":";
					if ((int)(s->timePlayed / 1000) % 60 < 10)
						list += "0";
					list += to_string((int)(s->timePlayed / 1000) % 60);
					list += "     ";
					list += s->winner;
					for (int i = 0; i < 10 - s->winner.length(); i++)
						list += " ";
					list += "     ";
					if (s->score < 10000)
						list += "0";
					if (s->score < 1000)
						list += "0";
					if (s->score < 100)
						list += "0";
					if (s->score < 10)
						list += "0";
					list += to_string(s->score) + "\n";
				}
			}
			list += "\n\nF5 - Clear statistic\n";
			list += "Press SPACE to go back";
			scoreText->text = list;
		}
		if (showAbout) {
			if (GetGameObject()->GetScene()->GetWindow()->GetInput()->keyboard->GetKey(SPACE))
				showAbout = false;
			menu->text = "";
			string text = "";
			text += "About\n";
			text += "  Program:   PingPong3D\n";
			text += "  Author:      LoveNek0\n";
			text += "\nControls\n";
			text += "  Singleplayer\n";
			text += "    A - Left\n    D - Right\n\n";
			text += "  Multiplayer\n";
			text += "    First player\n";
			text += "      A - Left\n      D - Right\n\n";
			text += "    Second player\n";
			text += "      Left Arrow - Left\n      Right Arrow - Right\n";
			text += "\n\nPress SPACE to go back";
			aboutText->text = text;
		}
		if (selectDifficulty) {
			scoreText->text = "";
			aboutText->text = "";
			string items[4] = {
				"Easy",
				"Normal",
				"Hard"
			};

			float t_x = menu->position.x;
			float t_y = menu->position.y;
			int m_x = GetGameObject()->GetScene()->GetWindow()->GetInput()->mouse->GetAxis().x;
			int m_y = GetGameObject()->GetScene()->GetWindow()->GetInput()->mouse->GetAxis().y;
			for (int i = 0; i < 3; i++) {
				if (
					m_x >= t_x
					&&
					m_x <= t_x + (items[i].length() + 18)
					) {
					if (
						m_y <= (t_y + (18 * (i + 1)))
						&&
						m_y >= (t_y + (18 * (i + 2)))
						) {
						selected = i;
						break;
					}
				}
			}

			if (
				!GetGameObject()->GetScene()->GetWindow()->GetInput()->keyboard->GetKey('w')
				&&
				!GetGameObject()->GetScene()->GetWindow()->GetInput()->keyboard->GetKey('s')
				&&
				!GetGameObject()->GetScene()->GetWindow()->GetInput()->keyboard->GetSpecialKey(ARROW_UP)
				&&
				!GetGameObject()->GetScene()->GetWindow()->GetInput()->keyboard->GetSpecialKey(ARROW_DOWN)
				)
				last = 0;
			if ((Time::GetMS() - last) >= 150) {
				if (
					GetGameObject()->GetScene()->GetWindow()->GetInput()->keyboard->GetKey('w')
					||
					GetGameObject()->GetScene()->GetWindow()->GetInput()->keyboard->GetSpecialKey(ARROW_UP)
					) {
					selected--;
					last = Time::GetMS();
				}
				if (
					GetGameObject()->GetScene()->GetWindow()->GetInput()->keyboard->GetKey('s')
					||
					GetGameObject()->GetScene()->GetWindow()->GetInput()->keyboard->GetSpecialKey(ARROW_DOWN)
					) {
					selected++;
					last = Time::GetMS();
				}
			}

			if (selected > 2)
				selected = 0;
			if (selected < 0)
				selected = 2;

			string str = "Select difficulty\n";
			for (int i = 0; i < 3; i++)
				if (i == selected)
					str += "  >" + items[i] + "\n";
				else
					str += "    " + items[i] + "\n";
			menu->text = str;

			if (Time::GetMS() - pressed > 150)
				if (GetGameObject()->GetScene()->GetWindow()->GetInput()->keyboard->GetKey(ENTER)) {
					switch (selected) {
					case 0:
						inS = false;
						inputName = true;
						selectDifficulty = false;
						diff = 0;
						break;
					case 1:
						inS = false;
						inputName = true;
						selectDifficulty = false;
						diff = 1;
						break;
					case 2:
						inS = false;
						inputName = true;
						selectDifficulty = false;
						diff = 2;
						break;
					}
					last = Time::GetMS();
				}
		}
		if (inputName) {
			scoreText->text = "";
			aboutText->text = "";

			string str = "Input name\n";
			
			if (!inS)
				str += "  Player 1 (WASD): " + name_1;
			else
				str += "  Player 2 (Arrows): " + name_2;

			if (Time::GetMS() - pressed > 30) {
				if (GetGameObject()->GetScene()->GetWindow()->GetInput()->keyboard->GetKey(ENTER)) {
					if (!gameMode) {
						if (name_1 != "")
							single(1 + diff, name_1);
					}
					else {
						if (!inS) {
							if (name_1 != "")
								inS = true;
						}
						else
							if (name_1 != "" && name_2 != "" && name_1 != name_2)
								multi(1 + diff, name_1, name_2);
					}
					pressed = Time::GetMS();
				}
				else {
					unsigned char in = GetGameObject()->GetScene()->GetWindow()->GetInput()->keyboard->GetPressed();
					if (in != '\0') {
						if (!gameMode)
							if (in == BACKSPACE) {
								if (name_1.length() > 0)
									name_1 = name_1.substr(0, name_1.length() - 1);
							}
							else
								name_1 += in;
						else
							if(!inS)
								if (in == BACKSPACE) {
									if (name_1.length() > 0)
										name_1 = name_1.substr(0, name_1.length() - 1);
								}
								else
									name_1 += in;
							else
								if (in == BACKSPACE) {
									if (name_2.length() > 0)
										name_2 = name_2.substr(0, name_2.length() - 1);
								}
								else
									name_2 += in;
					}
				}
			}
			menu->text = str;
		}


		table->transform.rotation.SetZ(table->transform.rotation.GetZ() + 10 * Time::DeltaTime());
	}
};