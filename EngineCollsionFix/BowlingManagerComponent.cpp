#include "BowlingManagerComponent.h"
#include "BowlingBallActor.h"
#include "ArrowIndicatorActor.h"
#include "BowlingManager.h"
#include "BowlingMoveComponent.h"
#include "PinMoveComponent.h"
#include "Log.h"
#include "CubeActor.h"
#include "ScoreShowActor.h"
#include "ScoreShowComponent.h"

BowlingManagerComponent::BowlingManagerComponent(Actor* ownerP):
	Component(ownerP)
{

	arrow = new ArrowIndicatorActor();
	currentPhase = gamePhase::BallOrientation;

	currentBall = new BowlingBallActor();

	scoreAct = new ScoreShowActor();
	scoreAct->setPosition(Vector3(150, 700, 0));
	scoreAct->setRotation(Quaternion(Vector3::unitX, Maths::piOver2 + 0.2));
	scoreAct->rotate(Vector3::unitX, Maths::pi);

	
}



void BowlingManagerComponent::placePins()
{

	//Pins Placement
	Vector3 basePos = Vector3(-90, 0, -98);
	float nRange = 4;
	float size = 180;
	for (int n = nRange; n > 0; n--) {
		for (int i = 0; i < n; i++) {
			PinActor* pin = new PinActor();
			Vector3 pos = Vector3::zero;

			pos.x = (size / (n + 1)) * (i + 1);
			pos.y = ((size/2) / nRange) * -n;

			pos += basePos;

			pin->setPosition(pos);

			pin->setRotation(Quaternion(Vector3::unitX, Maths::piOver2));

			pin->getMoveComponent()->setBasePos();

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

	placePins();
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
		nextPhase();
		break;
	case gamePhase::BallOrientation:
		arrow->setRotation(Quaternion(Vector3::unitZ, sin * (Maths::pi / 4) - Maths::piOver2 ));
		break;
	case gamePhase::BallPower:
		arrow->setScale(15 + Maths::abs(sin * 20));
		break;
	case gamePhase::BallWatch:
		if (currentBall->getMoveComponent()->HasReachedEnd() && !hasReachedEnd) {
			endT = entTimerTime;
			if (currentBall->getMoveComponent()->IsOnSide()) {
				endT = 0;
			}
			hasReachedEnd = true;
		}
		if (hasReachedEnd) {
			endT = Maths::clamp(endT - dt, 0.0f, entTimerTime);
			if (endT == 0) {
				nextPhase();
			}
		}

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

		
		currentBall->getMoveComponent()->LaunchBall(currentFWD * currentPower);

		BowlingManager* m = static_cast<BowlingManager*>(&owner);
		m->getCamera()->setTarget(currentBall);
		m->getCamera()->setCamPhase(BowlingCameraComponent::camPhase::LookAt);
		m->getCamera()->setLanePosition(m->getCamera()->getCurrentPos());

		launchN++;

		nextPhase();
		break;
	}
}

void BowlingManagerComponent::calculateScore()
{
	std::vector<PinActor*> pinToRemove = std::vector<PinActor*>();
	for (PinActor* p : pinsPlaced) {
		if (p->getMoveComponent()->hasMoved()) {
			score++;
			p->setState(Actor::ActorState::Dead);
			pinToRemove.push_back(p);
		}
	}

	for (PinActor* p : pinToRemove) {
		int id = -1;
		for (int i = 0; i < pinsPlaced.size(); i++) {
			if (pinsPlaced[i] == p) {
				id = i;
				break;
			}
		}
		if (id != -1) {
			pinsPlaced.erase(pinsPlaced.begin() + id);
		}
	}

	scoreAct->getScoreShow()->setScore(score);
}

void BowlingManagerComponent::nextPhase()
{
	time = 0;
	BowlingManager* m = static_cast<BowlingManager*>(&owner);

	switch (currentPhase) {
	case gamePhase::Reset:
		if (launchN % 2 == 0) {
			calculateScore();
			resetPins();
			score = 0;
		}
		else {
			calculateScore();
			if (score == 10) {
				resetPins();
				score = 0;
				launchN++;
			}
		}
		

		currentBall->setState(Actor::ActorState::Dead);
		arrow->setState(Actor::ActorState::Dead);

		arrow = new ArrowIndicatorActor();

		currentBall = new BowlingBallActor();

		hasReachedEnd = false;
		
		m->getCamera()->setTarget(currentBall);
		m->getCamera()->setCamPhase(BowlingCameraComponent::camPhase::Orbit);

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


