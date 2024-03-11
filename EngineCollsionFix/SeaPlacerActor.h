#pragma once
#include "Actor.h"
class SeaPlacerActor : public Actor
{
public:
	SeaPlacerActor();

private:
	class SeaPlacerComponent* SPComponent;
};

