#pragma once
#include "Component.h"
#include "PinActor.h"
class BowlingManagerComponent : public Component
{
public:
	BowlingManagerComponent(class Actor* ownerP);

	void placePins();
	void resetPins();
	
private:
	std::vector<PinActor*> pinsPlaced ;

	enum gamePhase {BallOrientation, BallPower, BallWatch};
};

