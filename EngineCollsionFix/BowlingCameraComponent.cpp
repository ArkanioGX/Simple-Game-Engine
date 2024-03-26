#include "BowlingCameraComponent.h"
#include "Actor.h"

BowlingCameraComponent::BowlingCameraComponent(Actor* ownerP, int updateOrder):
	CameraComponent(ownerP,updateOrder),
	currentCamPhase(camPhase::Orbit),
	pitchSpeed(0),
	yawSpeed(0),
	targetBall(nullptr),
	lanePosition(Vector3(160,397,0)), 
	offset(0.0f, 150.0f, 120.0f),
	up(Vector3::unitZ)
{
	setCamPhase(camPhase::Orbit);
}

void BowlingCameraComponent::update(float dt)
{
	CameraComponent::update(dt);

	Matrix4 view = Matrix4::identity;

	switch (currentCamPhase) {
	case camPhase::Orbit:
		view = orbitCamUpdate(dt);
		break;
	case camPhase::LookAt:
		view = lookCamUpdate(dt);
		break;
	default: break;
	}
	setViewMatrix(view);
}

void BowlingCameraComponent::setTarget(Actor* t)
{
	targetBall = t;
}

Matrix4 BowlingCameraComponent::orbitCamUpdate(float dt)
{
	Quaternion yaw{ Vector3::unitZ, yawSpeed * dt };
	offset = Vector3::transform(offset, yaw);
	up = Vector3::transform(up, yaw);

	// Compute camera forward/right from these vectors
	// Forward owner.position - (owner.position + offset) = -offset
	Vector3 forward = -1.0f * offset;
	forward.normalize();
	Vector3 right = Vector3::cross(up, forward);
	right.normalize();

	Quaternion pitch{ right, pitchSpeed * dt };
	offset = Vector3::transform(offset, pitch);
	up = Vector3::transform(up, pitch);

	Vector3 target = targetBall->getPosition();
	cameraPosition = target + offset;
	return Matrix4::createLookAt(cameraPosition, target, up);
	
}

Matrix4 BowlingCameraComponent::lookCamUpdate(float dt)
{
	return Matrix4::createLookAt(lanePosition, targetBall->getPosition(), up);
}


