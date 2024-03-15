#include "BowlingMoveComponent.h"
#include "BowlingManagerComponent.h"
#include "Actor.h"
#include "LineSegment.h"
#include "PhysicsSystem.h"
#include "Game.h"
#include "BowlingBallActor.h"
#include "BoxComponent.h"
#include "AABB.h"
#include "Log.h"

#include "CubeActor.h"
#include "PinActor.h"

BowlingMoveComponent::BowlingMoveComponent(Actor* ownerP) :
	MoveComponent(ownerP)
{
}

void BowlingMoveComponent::update(float dt)
{
	setForwardSpeed(currentForce.length());

	if (Maths::abs(owner.getPosition().x) > 75) {
		owner.rotateToNewForward(Vector3(0, -1, 0));
	}


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
		// Did we hit a target?
		CubeActor* Wall = dynamic_cast<CubeActor*>(info.actor);
		if (Wall)
		{
			PhysicsSystem::CollisionInfo infoL;
			// If we collided, reflect the ball about the normal
			dir = Vector3::reflect(dir, Vector3(1,0,0));
			owner.rotateToNewForward(dir);
			
		}

		PinActor* Pin = dynamic_cast<PinActor*>(info.actor);
		if (Pin)
		{
			Log::info("Pin !!");

		}
	}

	MoveComponent::update(dt);
}

void BowlingMoveComponent::addAdditiveForce(Vector3 f)
{
	currentForce += f;
	setForwardSpeed(f.length());
	f.normalize();
	owner.rotateToNewForward(f);
}

