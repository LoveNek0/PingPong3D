#pragma once
#include <chrono>
using namespace std::chrono;

class Time {
private:
	static float deltaTime;
	static milliseconds lastTime;
	static unsigned long long tick;

public:
	static float DeltaTime() {
		return deltaTime;
	}
	static unsigned long long Tick() {
		return tick;
	}
	static unsigned long long GetMS() {
		return duration_cast<milliseconds>(system_clock::now().time_since_epoch()).count();
	}
	static milliseconds GetTime() {
		return duration_cast<milliseconds>(system_clock::now().time_since_epoch());
	}
	static void Update() {
		milliseconds ms = duration_cast<milliseconds>(system_clock::now().time_since_epoch());
		deltaTime = (float)(ms - lastTime).count() / 1000.0f;
		lastTime = ms;
		tick++;
	}
};

float Time::deltaTime = 1.0f;
milliseconds Time::lastTime = duration_cast<milliseconds>(system_clock::now().time_since_epoch());
unsigned long long Time::tick = 0;