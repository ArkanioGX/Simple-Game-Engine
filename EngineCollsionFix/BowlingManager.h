#pragma once
#include "Actor.h"
#include "BowlingCameraComponent.h"
class BowlingManager : public Actor
{
public:
	BowlingManager();

	void actorInput(const InputState& inputState) override;

	class BowlingCameraComponent* getCamera();
	class BowlingManagerComponent* getManager();

private:
	class BowlingCameraComponent* camera;
	class BowlingManagerComponent* manager;
};

