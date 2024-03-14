#include "BowlingManagerComponent.h"
#include "PinActor.h"
#include "BowlingBallActor.h"

BowlingManagerComponent::BowlingManagerComponent(Actor* ownerP):
	Component(ownerP)
{
	placePins();
}

void BowlingManagerComponent::placePins()
{
	BowlingBallActor* ball = new BowlingBallActor();

	Vector3 basePos = Vector3(-75, 50, -100);
	float nRange = 4;
	float size = 130;
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
