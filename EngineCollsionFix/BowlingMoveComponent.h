#pragma once
#include "MoveComponent.h"
#include "Vector3.h"

class BowlingMoveComponent : public MoveComponent
{
public:
	BowlingMoveComponent(class Actor* ownerP);

	void update(float dt) override;

	void addAdditiveForce(Vector3 f);
	void setForce(Vector3 f);
	void LaunchBall(Vector3 f);

	bool HasReachedEnd();
	bool IsOnSide();
private:
	Vector3 currentForce;
	float friction;
	bool hasStopped;
	float yPin = 0;
};

