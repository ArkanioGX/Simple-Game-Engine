#pragma once
#include "Vector3.h"
#include "Component.h"

class PinMoveComponent : public Component
{
public:
	PinMoveComponent(class Actor* ownerP);

	void update(float dt) override;

	void addForce(Vector3 f);
	void setForce(Vector3 f);

	Vector3 getForce();

	void setBasePos();
	bool hasMoved();
private:
	Vector3 currentForce;
	float friction;
	Vector3 basePos;
};

