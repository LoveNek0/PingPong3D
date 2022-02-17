#include <iostream>
#include "Window.h"
#include "Scene.h"
#include "Input.h"
#include "GameObject.h"
#include "RacketScript.h"
#include "TableScript.h"
#include "MenuScript.h"
#include "SceneManager.h"
using namespace std;

int main() {
	Window window = Window("PingPong3D");
	window.SetScene(SceneManager::MainMenu());
	window.Run();
	return 0;
}