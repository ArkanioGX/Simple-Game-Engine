#pragma once
#include "Actor.h"

class PlayerPlaneActor : public Actor
{
public:
	PlayerPlaneActor();
	void actorInput(const struct InputState& inputState) override;
	void shoot();
	void ding();

private:
	class MoveComponent* moveComponent;
	class AudioComponent* audio;
	class AirplaneCameraComponent* cameraComponent;

};

