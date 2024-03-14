#pragma once
#include "Component.h"
#include "PinActor.h"

class BowlingManagerComponent : public Component
{
public:
	BowlingManagerComponent(class Actor* ownerP);

	void placePins();
	void resetPins();

	class BowlingBallActor* getBall();

	void update(float dt) override;

	void Interact();

	void nextPhase();
	
private:
	std::vector<PinActor*> pinsPlaced ;

	class BowlingBallActor* currentBall;
	class ArrowIndicatorActor* arrow;

	enum gamePhase {Reset, BallOrientation, BallPower, BallWatch};

	gamePhase currentPhase;

	float time = 0;

	Vector3 currentFWD = Vector3::negUnitY;
	float currentPower = 10;
};

constexpr float MIN_POWER = 100;
constexpr float MAX_POWER = 400;


