#pragma once
#include "Actor.h"
class PinActor : public Actor
{
public:
	PinActor();

private:
	class BoxComponent* box;
};

