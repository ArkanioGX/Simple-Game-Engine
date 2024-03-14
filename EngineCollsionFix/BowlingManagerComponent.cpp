#include "BowlingManagerComponent.h"
#include "BowlingBallActor.h"
#include "ArrowIndicatorActor.h"
#include "BowlingManager.h"
#include "Log.h"

BowlingManagerComponent::BowlingManagerComponent(Actor* ownerP):
	Component(ownerP)
{
	placePins();
	arrow = new ArrowIndicatorActor();
	currentPhase = gamePhase::BallOrientation;
}



void BowlingManagerComponent::placePins()
{
	currentBall = new BowlingBallActor();

	Vector3 basePos = Vector3(-100, 100, -100);
	float nRange = 4;
	float size = 200;
	for (int n = nRange; n> 0; n --) {
		for (int i = 0; i < n; i++) {
			PinActor* pin = new PinActor();
			Vector3 pos = Vector3::zero;

			pos.x = (size/(n+1))*(i+1);
			pos.y = (size / nRange) * -n;

			pos += basePos;

			pin->setPosition(pos);

			pinsPlaced.emplace_back(pin);
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
		arrow->setRotation(Quaternion(Vector3::unitZ, Maths::pi + sin * (Maths::pi / 3)));
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
		Log::info("HELLO 1 ");
		nextPhase();
		break;
	case gamePhase::BallPower:
		currentPower = MIN_POWER + (MAX_POWER - MIN_POWER) * Maths::sin(time);
		BowlingManager* m = static_cast<BowlingManager*>(&owner);
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


