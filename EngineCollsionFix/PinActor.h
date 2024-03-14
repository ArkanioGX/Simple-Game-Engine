#pragma once
#include "Actor.h"
class PinActor : public Actor
{
public:
	PinActor();

private:
	class MeshComponent* meshComponent;
	class BoxComponent* boxComponent;
};

