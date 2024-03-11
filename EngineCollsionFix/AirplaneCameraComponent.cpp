#include "AirplaneCameraComponent.h"
#include "Actor.h"

AirplaneCameraComponent::AirplaneCameraComponent(Actor* ownerP) :
	CameraComponent(ownerP),
	offset(Vector3(0,0.1,800))
{
}

void AirplaneCameraComponent::update(float dt)
{
	CameraComponent::update(dt);

	Vector3 ActorPos = owner.getPosition();
	Vector3 idealPos = ActorPos + offset;

	Vector3 target = owner.getPosition();
	Matrix4 view = Matrix4::createLookAt(idealPos, target, Vector3::unitZ);
	setViewMatrix(view);
}
