#include "MoveComponent.h"
#include "Maths.h"
#include "Actor.h"
#include "Window.h"

MoveComponent::MoveComponent(Actor* ownerP, int updateOrderP) : 
	Component(ownerP,updateOrderP),
	velocity(Vector2::zero),
	angularSpeed(0.0f)
{
}

void MoveComponent::setVelocity(Vector2 velocityP)
{
	velocity = velocityP;
}

void MoveComponent::setAngularSpeed(float angularSpeedP)
{
	angularSpeed = angularSpeedP;
}

void MoveComponent::update(float dt)
{
	if (!Maths::nearZero(angularSpeed)) {
		float newRotation = owner.getRotation() + angularSpeed * dt;
		owner.setRotation(newRotation);
	}
	if (!Maths::nearZero(velocity.x) || !Maths::nearZero(velocity.y)) {
		Vector2 newPos = owner.getPosition() + velocity * dt;
		owner.setPosition(newPos);
	}
}

