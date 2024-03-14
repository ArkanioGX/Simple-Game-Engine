#pragma once
#include "CameraComponent.h"
class BowlingCameraComponent : public CameraComponent
{
public:
	BowlingCameraComponent(class Actor* ownerP, int updateOrder = 10);

	void update(float dt) override;

	float getPitchSpeed() const { return pitchSpeed; }
	float getYawSpeed() const { return yawSpeed; }

	void setPitchSpeed(float pitchSpeedP);
	void setYawSpeed(float yawSpeedP);

	enum camPhase {Orbit, LookAt};

	void setCamPhase(camPhase phase);

	Matrix4 orbitCamUpdate(float dt);
	Matrix4 lookCamUpdate(float dt);


private:
	class Actor* targetBall;

	Vector3 lanePosition;

	// Offset from target
	Vector3 offset;
	// Up vector of camera
	Vector3 up;

	camPhase currentCamPhase;

	float pitchSpeed;
	float yawSpeed;
};

