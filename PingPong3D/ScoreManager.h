#pragma once
#include <string>
#include <iostream>
#include <fstream>
#include <vector>
#include "Time.h"
using namespace std;

struct Score {
	static enum Player {
		FIRST,
		SECOND
	};

	static enum GameType {
		SINGLE,
		MULTI
	};

	string winner;
	int score;
	unsigned long long timePlayed;
	Score() {

	}
	Score(string winner, int score, unsigned long long timePlayed) {
		this->winner = winner;
		this->score = score;
		this->timePlayed = timePlayed;
	}
};

class ScoreManager {
public:
	static void AddScore(int mode, int difficulty, Score score) {
		Score* s = GetScore(mode, difficulty);
		if (s == NULL) {
			ofstream fout(to_string(mode) + "_" + to_string(difficulty) + ".txt");
			fout << score.winner << " " << to_string(score.score) << " " << to_string(score.timePlayed);
			fout.close();
		}
		else
			if (s->score < score.score) {
				ofstream fout(to_string(mode) + "_" + to_string(difficulty) + ".txt");
				fout << score.winner << " " << to_string(score.score) << " " << to_string(score.timePlayed);
				fout.close();
			}
	}

	static Score* GetScore(int mode, int diff) {
		ifstream fin;
		fin.open(to_string(mode) + "_" + to_string(diff) + ".txt");
		if (!fin.is_open())
			return NULL;
		Score* max = NULL;
		while (!fin.eof()) {
			Score* t = new Score();
			fin >> t->winner;
			fin >> t->score;
			fin >> t->timePlayed;
			if (max == NULL)
				max = t;
			else
				if (t->score > max->score)
					max = t;
		}
		fin.close();
		return max;
	}

	static void Clear() {
		remove("0_1.txt");
		remove("0_2.txt");
		remove("0_3.txt");
		remove("1_1.txt");
		remove("1_2.txt");
		remove("1_3.txt");
	}
};