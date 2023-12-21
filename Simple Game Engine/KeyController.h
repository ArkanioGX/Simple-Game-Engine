#pragma once
#include "Component.h"
#include "SceneLoader.h"
class KeyController : public Component
{
	char keyID;
	SceneLoader* scene;
public:
	KeyController(Actor* ownerP, char id, SceneLoader* sl);
	KeyController() = delete;
	KeyController(const KeyController&) = delete;
	KeyController& operator=(const KeyController&) = delete;

	void OnTrigger(Collision* coll) override;
};

