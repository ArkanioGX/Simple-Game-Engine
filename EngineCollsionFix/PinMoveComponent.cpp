#include "PinMoveComponent.h"
#include "Actor.h"
#include "LineSegment.h"
#include "PhysicsSystem.h"
#include "Game.h"
#include "BoxComponent.h"
#include "AABB.h"
#include "PinActor.h"
#include "Log.h"


PinMoveComponent::PinMoveComponent(Actor* ownerP) :
	Component(ownerP),
	friction(0.95),
	currentForce(Vector3::zero)
{
	
}

void PinMoveComponent::update(float dt)
{
	currentForce *= friction;
	
	

	// Test segment vs world
	PhysicsSystem::CollisionInfo info;

	PinActor* bm = static_cast<PinActor*>(&owner);

	if (owner.getGame().getPhysicsSystem().boxCast(bm->getBoxComponent(), info) && info.actor != &owner )
	{

		PinActor* Pin = dynamic_cast<PinActor*>(info.actor);
		if (Pin)
		{
			Vector3 forceFWD = Pin->getPosition() - owner.getPosition();
			//Pin->setPosition(Pin->getPosition() + forceFWD);
			forceFWD.normalize();
			forceFWD = Vector3(forceFWD.x, forceFWD.y, 0);

			Vector3 midForce = (Pin->getMoveComponent()->getForce() + currentForce) * 0.5f;

			currentForce = midForce;
			
			Pin->getMoveComponent()->setForce(midForce);
			
		}
	}

	Vector3 newPosition = owner.getPosition();
	newPosition += currentForce * dt;
	owner.setPosition(newPosition);

}

void PinMoveComponent::addForce(Vector3 f)
{
	currentForce += f;
}

void PinMoveComponent::setForce(Vector3 f)
{
	currentForce = f;
}

Vector3 PinMoveComponent::getForce()
{
	return currentForce;
}

void PinMoveComponent::setBasePos()
{
	basePos = owner.getPosition();
}

bool PinMoveComponent::hasMoved()
{
	return (basePos - owner.getPosition()).length() > 0.5;
}
