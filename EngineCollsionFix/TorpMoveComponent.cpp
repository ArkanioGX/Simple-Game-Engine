#include "TorpMoveComponent.h"
#include "TorpedoActor.h"
#include "LineSegment.h"
#include "Collisions.h"
#include "PhysicsSystem.h"
#include "TorpedoActor.h"
#include "Vector3.h"
#include "Game.h"
#include "PlaneActor.h"
#include "BoatActor.h"
#include "AudioComponent.h"
#include "Actor.h"
#include "PlayerPlaneActor.h"

TorpMoveComponent::TorpMoveComponent(Actor* ownerP):
	MoveComponent(ownerP)
{
	owner.setRotation(Quaternion(Vector3::unitY, Maths::piOver2));
	setForwardSpeed(400);
	player = owner.getGame().getPlayer();
}



void TorpMoveComponent::update(float dt)
{
	// Construct segment in direction of travel
	const float segmentLength = 30.0f;
	Vector3 start = owner.getPosition();
	Vector3 dir = owner.getForward();
	Vector3 end = start + dir * segmentLength;

	// Create line segment
	LineSegment l(start, end);

	// Test segment vs world
	PhysicsSystem::CollisionInfo info;
	// (Don't collide vs player)
	if (owner.getGame().getPhysicsSystem().segmentCast(l, info))
	{

		PlaneActor* sea = dynamic_cast<PlaneActor*>(info.actor);
		if (sea) {
			// If we collided, reflect the ball about the normal
			dir = Vector3(0.0f, -1.0f, 0.0f);
			owner.rotateToNewForward(dir);
			setForwardSpeed(1000);
		}
		BoatActor* boat = dynamic_cast<BoatActor*>(info.actor);
		if (boat) {
			boat->setState(Actor::ActorState::Dead);
			hit();
		}

		
	}

	// Base class update moves based on forward speed
	MoveComponent::update(dt);
}

void TorpMoveComponent::hit()
{
	player->ding();
	owner.setState(Actor::ActorState::Dead);
}
