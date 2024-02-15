#pragma once
#include "Actor.h"
#include "Vector3.h"

class FPSActor : public Actor
{
public:
	FPSActor();

	void updateActor(float dt) override;
	void actorInput(const struct InputState& inputState) override;

	void setFootstepSurface(float value);
	void setVisible(bool isVisible);

private:
	class MoveComponent* moveComponent = nullptr;
	class MeshComponent* meshComponent = nullptr;
	class FPSCameraComponent* cameraComponent = nullptr;
	class Actor* FPSModel = nullptr;
	float lastFootstep = 0.0f;
};

const Vector3 MODEL_OFFSET = Vector3(10.0f, 10.0f, -10.0f);

