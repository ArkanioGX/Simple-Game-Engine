#include "FollowCameraComponent.h"
#include "Actor.h"

FollowCameraComponent::FollowCameraComponent(Actor* ownerP):
	CameraComponent(ownerP),
	horizontalDistance(FOLLOW_HORIZONTAL_DISTANCE),
	verticalDistance(FOLLOW_VERTICAL_DISTANCE),
	targetDistance(FOLLOW_TARGET_DISTANCE),
	springConstant(FOLLOW_SPRING_CONSTANT)
{
}

void FollowCameraComponent::update(float dt)
{
	CameraComponent::update(dt);

	float dampening = 2.0f * Maths::sqrt(springConstant);
	Vector3 idealPos = computeCameraPosition();
	Vector3 diff = actualPosition - idealPos;
	Vector3 accel = -springConstant * diff - dampening * velocity;
	velocity += accel * dt;
	actualPosition += velocity * dt;

	Vector3 target = owner.getPosition() + owner.getForward();
	Matrix4 view = Matrix4::createLookAt(actualPosition, target, Vector3::unitZ);
	setViewMatrix(view);
}

void FollowCameraComponent::snapToIdeal()
{
	actualPosition = computeCameraPosition();
	velocity = Vector3::zero;
	Vector3 target = owner.getPosition() + owner.getForward() * targetDistance;
	Matrix4 view = Matrix4::createLookAt(actualPosition, target, Vector3::unitZ);
	setViewMatrix(view);
}

void FollowCameraComponent::setHorizontalDistance(float dist)
{
	horizontalDistance = dist;
}

void FollowCameraComponent::setVerticalDistance(float dist)
{
	verticalDistance = dist;
}

void FollowCameraComponent::setTargetDistance(float dist)
{
	targetDistance = dist;
}

void FollowCameraComponent::setSpringConstant(float dist)
{
	springConstant = dist;
}

Vector3 FollowCameraComponent::computeCameraPosition() const
{
	Vector3 camPos = owner.getPosition();
	camPos -= owner.getForward() * horizontalDistance;
	camPos += Vector3::unitZ * verticalDistance;
	return camPos;
}
