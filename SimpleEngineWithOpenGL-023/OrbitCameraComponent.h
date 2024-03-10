#pragma once
#include "CameraComponent.h"
class OrbitCameraComponent : public CameraComponent
{
public:
	OrbitCameraComponent(class Actor* owner);

	void update(float dt) override;

	float getPitchSpeed() const { return pitchSpeed; }
	float getYawSpeed() const { return yawSpeed; }

	void setPitchSpeed(float pitchSpeedP);
	void setYawSpeed(float yawSpeedP);

private:
	Vector3 offset;

	Vector3 up;

	float pitchSpeed;
	float yawSpeed;
};

