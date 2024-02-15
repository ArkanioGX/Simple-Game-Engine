#pragma once
#include "Actor.h"
#include "CameraComponent.h"

class FPSCameraComponent : public CameraComponent
{
public:
	FPSCameraComponent(class Actor* ownerP);

	void update(float dt) override;
	void processInput(struct InputState const&) {};

	float getPitch() const { return pitch; }
	float getPitchSpeed() const { return pitchSpeed; }
	float getMaxPitch() const { return maxPitch; }

	void setPitchSpeed(float speed);
	void setMaxPitch(float pitchP);

private:
	float pitchSpeed;
	float maxPitch;
	float pitch;
};

