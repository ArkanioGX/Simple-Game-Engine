#pragma once
#include "Actor.h"
class TorpedoActor : public Actor
{
public:
	TorpedoActor();

private:
	class MeshComponent* meshComponent;
	class TorpMoveComponent* moveComponent;
};

