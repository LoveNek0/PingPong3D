#pragma once
#include "Transform.h"
#include "TextField.h"
#include "GameObject.h"
class Window;

class Scene
{
private:
	Window* window;
	vector<GameObject*> objects;
	vector<TextField*> texts;

public:
	Transform transform;

	Scene() {
		transform = Transform();
		objects = vector<GameObject*>(0);
		texts = vector<TextField*>(0);
	}

	void AddObject(GameObject* object) {
		if (GetObject(object->GetID()) == NULL) {
			objects.push_back(object);
			GameObject::Init(object, this);
		}
	}
	void AddText(TextField* text) {
		if (GetTextField(text->GetID()) == NULL)
			texts.push_back(text);
	}

	GameObject* GetObject(string id) {
		for (GameObject* obj : objects) {
			if (strcmp(obj->GetID().c_str(), id.c_str()) == 0)
				return obj;
		}
		return NULL;
	}
	TextField* GetTextField(string id) {
		for (TextField* obj : texts) {
			if (strcmp(obj->GetID().c_str(), id.c_str()) == 0)
				return obj;
		}
		return NULL;
	}

	vector<GameObject*> GetObjects() {
		return objects;
	}
	vector<TextField*> GetTexts() {
		return texts;
	}

	Window* GetWindow() {
		return window;
	}

	static void Init(Scene* scene, Window* window) {
		scene->window = window;
	}
};