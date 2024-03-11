#pragma once
#include "Actor.h"
class TorpedoActor : public Actor
{
public:
	TorpedoActor();
	
	void destroyTorpedo();

private:
	class MeshComponent* meshComponent;
	class TorpMoveComponent* moveComponent;
};

