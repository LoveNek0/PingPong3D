#pragma once

class GameObject;
class Scene;
class Window;
class Input;

class ObjectScript {
private:
	GameObject* gameObject = NULL;

public:
	bool active = true;

	virtual void OnStart() {
		return;
	}
	virtual void OnUpdate() {
		return;
	}

	GameObject* GetGameObject() {
		return gameObject;
	}

	static void Init(ObjectScript* script, GameObject* gameObject) {
		script->gameObject = gameObject;
	}
};