#pragma once
#include "CameraComponent.h"
class BowlingCameraComponent : public CameraComponent
{
public:
	BowlingCameraComponent(class Actor* ownerP, int updateOrder = 10);

	void update(float dt) override;

	float getPitchSpeed() const { return pitchSpeed; }
	float getYawSpeed() const { return yawSpeed; }

	void setTarget(Actor* t);

	void setPitchSpeed(float pitchSpeedP) { pitchSpeed = pitchSpeedP; }
	void setYawSpeed(float yawSpeedP) { yawSpeed = yawSpeedP; }

	enum camPhase {Orbit, LookAt};

	void setCamPhase(camPhase phase) { currentCamPhase = phase; }

	Matrix4 orbitCamUpdate(float dt);
	Matrix4 lookCamUpdate(float dt);

	void setLanePosition(Vector3 pos) { lanePosition = pos; }

	Vector3 getCurrentPos() { return cameraPosition; }


private:
	class Actor* targetBall;

	Vector3 lanePosition;

	// Offset from target
	Vector3 offset;
	// Up vector of camera
	Vector3 up;

	Vector3 cameraPosition;

	camPhase currentCamPhase;

	float pitchSpeed;
	float yawSpeed;
};

