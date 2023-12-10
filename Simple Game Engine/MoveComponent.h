#pragma once
#include "Component.h"
#include "Vector2.h"
class MoveComponent : public Component
{
public:
	MoveComponent(Actor* ownerP, int updateOrder = 10);
	MoveComponent() = delete;
	MoveComponent(const MoveComponent&) = delete;
	MoveComponent& operator =(const MoveComponent&) = delete;

	Vector2 getVelocity() const { return velocity; }
	float getAngularSpeed() const { return angularSpeed; }

	void setVelocity(Vector2 velocityP);
	void setAngularSpeed(float angularSpeedP);

	void update(float dt) override;

private:
	Vector2 velocity;
	float angularSpeed;
};

