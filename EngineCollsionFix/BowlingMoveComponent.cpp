#include "BowlingMoveComponent.h"
#include "BowlingManagerComponent.h"
#include "Actor.h"
#include "LineSegment.h"
#include "PhysicsSystem.h"
#include "Game.h"
#include "BowlingBallActor.h"
#include "PinMoveComponent.h"
#include "BoxComponent.h"
#include "AABB.h"
#include "Log.h"

#include "CubeActor.h"
#include "PinActor.h"

BowlingMoveComponent::BowlingMoveComponent(Actor* ownerP) :
	MoveComponent(ownerP),
	friction(0.995),
	hasStopped(true)
{
}

void BowlingMoveComponent::update(float dt)
{
	currentForce *= friction;

	if (currentForce.length() < 2 && !hasStopped && owner.getPosition().y > yPin) {
		hasStopped = true;
		Vector3 newForce = Vector3(0, 0, 0);
		if (owner.getPosition().x > 0) {
			newForce = Vector3(1, 0, 0);
		}
		else {
			newForce = Vector3(-1, 0, 0);
		}
		setForce(newForce * 80);
	}
	

	if (IsOnSide()) {
		setForce(Vector3(0, -1, 0) * 100);
	}
	
	setForwardSpeed(currentForce.length());

	// Construct segment in direction of travel
	const float segmentLength = 30.0f;
	Vector3 start = owner.getPosition();
	Vector3 dir = owner.getForward();
	Vector3 end = start + dir * segmentLength;

	// Create line segment
	LineSegment l(start, end);

	// Test segment vs world
	PhysicsSystem::CollisionInfo info;

	BowlingBallActor* bm = static_cast<BowlingBallActor*>(&owner);

	// (Don't collide vs player)
	if (owner.getGame().getPhysicsSystem().boxCast(bm->getBoxComponent(), info) && info.actor != &owner)
	{
		/*
		CubeActor* Wall = dynamic_cast<CubeActor*>(info.actor);
		if (Wall)
		{
			PhysicsSystem::CollisionInfo infoL;
			// If we collided, reflect the ball about the normal
			dir = Vector3::reflect(dir, Vector3(1,0,0));
			owner.rotateToNewForward(dir);
			
		}*/

		PinActor* Pin = dynamic_cast<PinActor*>(info.actor);
		if (Pin)
		{
			
			Vector3 forceFWD = Pin->getPosition() - owner.getPosition();
			forceFWD.normalize();
			forceFWD = Vector3(forceFWD.x, forceFWD.y, 0);
			Pin->getMoveComponent()->addForce(currentForce.length() * forceFWD);
			currentForce *= 0.9;
		}
	}

	MoveComponent::update(dt);
}

void BowlingMoveComponent::addAdditiveForce(Vector3 f)
{
	setForce(currentForce + f);
}

void BowlingMoveComponent::setForce(Vector3 f)
{
	currentForce = f;
	setForwardSpeed(f.length());
	f.normalize();
	owner.rotateToNewForward(f);
	
}

void BowlingMoveComponent::LaunchBall(Vector3 f) {
	setForce(f);
	hasStopped = false;
}

bool BowlingMoveComponent::HasReachedEnd()
{
	return (owner.getPosition().y <= yPin && currentForce.length() < 2) || (owner.getPosition().y <= -150);
}

bool BowlingMoveComponent::IsOnSide()
{
	return (Maths::abs(owner.getPosition().x) > 85) ;
}

