#pragma once
#include "MoveComponent.h"
#include "Vector3.h"

class BowlingMoveComponent : public MoveComponent
{
public:
	BowlingMoveComponent(class Actor* ownerP);

	void update(float dt) override;

	void addAdditiveForce(Vector3 f);

private:
	Vector3 currentForce;
};

