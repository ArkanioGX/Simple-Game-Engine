#pragma once
#include "MoveComponent.h"

class TorpMoveComponent : public MoveComponent
{
public:
	TorpMoveComponent(class Actor* ownerP);

	void update(float dt) override;

	void hit();
private:
	class PlayerPlaneActor* player;
};

