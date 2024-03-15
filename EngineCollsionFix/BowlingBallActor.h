#pragma once
#include "Actor.h"
class BowlingBallActor : public Actor
{
public:
	BowlingBallActor();

	class BowlingMoveComponent* getMoveComponent();
	class BoxComponent* getBoxComponent();

private:
	class MeshComponent* meshComponent;
	class BoxComponent* boxComponent;
	class BowlingMoveComponent* moveComponent;
};

