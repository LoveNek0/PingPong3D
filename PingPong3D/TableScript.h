#pragma once
#include "ObjectScript.h"
#include "Log.h"

class TableScript : public ObjectScript {
public:

	Vector3D defaultRotation;

	void OnUpdate() {
		if (GetGameObject()->GetScene()->GetWindow()->GetInput()->mouse->GetButton(BUTTON_LEFT)) {
			GetGameObject()->transform.rotation.SetZ(GetGameObject()->transform.rotation.GetZ() + (10 * GetGameObject()->GetScene()->GetWindow()->GetInput()->mouse->GetOffset().x * Time::DeltaTime()));
			GetGameObject()->transform.rotation.SetX(GetGameObject()->transform.rotation.GetX() + (10 * GetGameObject()->GetScene()->GetWindow()->GetInput()->mouse->GetOffset().y * Time::DeltaTime()));
		}
		GetGameObject()->transform.rotation.SetY(0);
		//else
			//GetGameObject()->transform.rotation.FromVector(defaultRotation);

		float delta = 2.0f * Time::DeltaTime();
		if (GetGameObject()->GetScene()->GetWindow()->GetInput()->keyboard->GetKey('+'))
			if(GetGameObject()->GetScene()->GetWindow()->zoom + delta <= 2)
				GetGameObject()->GetScene()->GetWindow()->zoom += delta;
			else
				GetGameObject()->GetScene()->GetWindow()->zoom = 2;
		if (GetGameObject()->GetScene()->GetWindow()->GetInput()->keyboard->GetKey('-'))
			if (GetGameObject()->GetScene()->GetWindow()->zoom - delta >= 0.8)
				GetGameObject()->GetScene()->GetWindow()->zoom -= delta;
			else
				GetGameObject()->GetScene()->GetWindow()->zoom = 0.8;
	}
};