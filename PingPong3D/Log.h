#pragma once
#include <string>
#include <iostream>
#include <iomanip>
using namespace std;


class Log {
public:
	static void Out(string prefix, string s) {
		time_t currentTime;
		struct tm* localTime;

		time(&currentTime);                   // Get the current time
		localTime = localtime(&currentTime);  // Convert the current time to the local time

		int Hour = localTime->tm_hour;
		int Min = localTime->tm_min;
		int Sec = localTime->tm_sec;

		cout << "[" << ((Hour < 10) ? "0" : "") << Hour << ":" << ((Min < 10) ? "0" : "") << Min << ":" << ((Sec < 10) ? "0" : "") << Sec << "]" << "[" << prefix << "] " << s << endl;
	}

	static void Info(string s) {
		Out("INFO", s);
	}

	static void Debug(string s) {
		Out("DEBUG", s);
	}

	static void Warning(string s) {
		Out("WARNING", s);
	}

	static void Error(string s) {
		Out("ERROR", s);
	}
};