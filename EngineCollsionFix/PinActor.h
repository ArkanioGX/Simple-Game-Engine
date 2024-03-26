#pragma once
#include "Actor.h"
class PinActor : public Actor
{
public:
	PinActor();

	class PinMoveComponent* getMoveComponent();
	class BoxComponent* getBoxComponent();
private:
	class BoxComponent* box;
	class PinMoveComponent* moveComponent;
};

