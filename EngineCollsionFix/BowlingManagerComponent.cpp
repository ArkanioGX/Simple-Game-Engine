#include "BowlingManagerComponent.h"
#include "BowlingBallActor.h"
#include "ArrowIndicatorActor.h"
#include "BowlingManager.h"
#include "BowlingMoveComponent.h"
#include "Log.h"
#include "CubeActor.h"

BowlingManagerComponent::BowlingManagerComponent(Actor* ownerP):
	Component(ownerP)
{

	arrow = new ArrowIndicatorActor();
	currentPhase = gamePhase::BallOrientation;

	currentBall = new BowlingBallActor();
}



void BowlingManagerComponent::placePins()
{

	//Pins Placement
	Vector3 basePos = Vector3(-100, 100, -100);
	float nRange = 4;
	float size = 200;
	for (int n = nRange; n > 0; n--) {
		for (int i = 0; i < n; i++) {
			PinActor* pin = new PinActor();
			Vector3 pos = Vector3::zero;

			pos.x = (size / (n + 1)) * (i + 1);
			pos.y = (size / nRange) * -n;

			pos += basePos;

			pin->setPosition(pos);

			pin->setScale(13.0f);
			pin->setRotation(Quaternion(Vector3::unitX, Maths::piOver2));

			//pinsPlaced.emplace_back(pin);
		}
	}
}

void BowlingManagerComponent::resetPins()
{
	for (PinActor* p : pinsPlaced) {
		p->setState(Actor::ActorState::Dead);
	}
	pinsPlaced.clear();
}

BowlingBallActor* BowlingManagerComponent::getBall()
{
	return currentBall;
}

void BowlingManagerComponent::update(float dt)
{
	time += dt;
	float sin = Maths::sin(time);

	Vector3 currentPos = currentBall->getPosition();

	BowlingManager* m = static_cast<BowlingManager*>(&owner);

	if (currentPos.y < 200) {
		
		m->getCamera()->setLanePosition(Vector3(-60, 90, 0));
	}
	else if ( currentPos.y < 600 )
	{
		m->getCamera()->setLanePosition(Vector3(160, 397, 0));
		
	}
	

	switch (currentPhase) {
	case gamePhase::Reset:

		break;
	case gamePhase::BallOrientation:
		arrow->setRotation(Quaternion(Vector3::unitZ, sin * (Maths::pi / 3) - Maths::piOver2 ));
		break;
	case gamePhase::BallPower:
		arrow->setScale(15 + Maths::abs(sin * 20));
		break;
	case gamePhase::BallWatch:


		break;
	default:
		break;
	}
}

void BowlingManagerComponent::Interact()
{
	switch (currentPhase) {
	case gamePhase::BallOrientation:
		currentFWD = arrow->getForward();
		currentFWD = Vector3(currentFWD.x, currentFWD.y, 0);
		Log::info("HELLO 1 ");
		nextPhase();
		break;
	case gamePhase::BallPower:
		currentPower = MIN_POWER + (MAX_POWER - MIN_POWER) * Maths::sin(time);

		
		currentBall->getMoveComponent()->addAdditiveForce(currentFWD * currentPower);

		BowlingManager* m = static_cast<BowlingManager*>(&owner);
		m->getCamera()->setTarget(currentBall);
		m->getCamera()->setCamPhase(BowlingCameraComponent::camPhase::LookAt);
		m->getCamera()->setLanePosition(m->getCamera()->getCurrentPos());

		

		nextPhase();
		break;
	}
}

void BowlingManagerComponent::nextPhase()
{
	time = 0;
	switch (currentPhase) {
	case gamePhase::Reset:
		currentPhase = gamePhase::BallOrientation;
		break;
	case gamePhase::BallOrientation:
		currentPhase = gamePhase::BallPower;
		break;
	case gamePhase::BallPower:
		currentPhase = gamePhase::BallWatch;
		break;
	case gamePhase::BallWatch:
		currentPhase = gamePhase::Reset;
		break;
	default:
		break;
	}
}


