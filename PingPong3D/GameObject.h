#pragma once
#include <iostream>
#include <vector>
#include <fstream>
#include "Polygon3D.h"
#include "ObjectScript.h"
#include "GameException.h"
using namespace std;

class Scene;

class GameObject
{
private:
	string id;
	vector<Polygon3D> polygones;
	vector<ObjectScript*> scripts;
	Scene* scene;

public:
	Transform transform;

	GameObject(string id) {
		transform = Transform();
		polygones = vector<Polygon3D>(0);
		this->id = id;
	}

	string GetID() {
		return id;
	}

	void AddPolygone(Polygon3D polygone) {
		polygones.push_back(polygone);
	}
	void AddScript(ObjectScript* script) {
		scripts.push_back(script);
		ObjectScript::Init(script, this);
	}

	vector<Polygon3D> GetPolygones() {
		return polygones;
	}
	vector<ObjectScript*> GetScripts() {
		return scripts;
	}

	Scene* GetScene() {
		return scene;
	}

	static void Init(GameObject* object, Scene* scene) {
		object->scene = scene;
		for (ObjectScript* script : object->GetScripts())
			script->OnStart();
	}

	static GameObject* Open(string file, string id) {
		ifstream read(file);
		if (read.fail())
			throw GameException("File '" + file + "' is not exist!");
		GameObject* object = new GameObject(id);

		string tmp = "";
		Polygon3D polygon = Polygon3D();
		while (!read.eof()) {
			unsigned char in = read.get();
			if (in == '\n' || in == ' ' || read.eof()) {
				if (tmp == "polygon") {
					polygon = Polygon3D();
				}
				if (tmp == "color") {
					int r, g, b;
					read >> r;
					read >> g;
					read >> b;
					polygon.color = Color(r, g, b);
				}
				if (tmp == "point") {
					float x, y, z;
					read >> x;
					read >> y;
					read >> z;
					polygon.AddPoint(x, y, z);
				}
				if (tmp == "end")
					object->AddPolygone(polygon);
				tmp = "";
			}
			else
				tmp += in;

		}
		return object;
	}
};