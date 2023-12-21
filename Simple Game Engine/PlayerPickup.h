#pragma once
#include "Component.h"
#include "Collider.h"

class PlayerPickup : Component
{
	Collider* c;
public:
	PlayerPickup(Actor* ownerP, Collider* coll);
	PlayerPickup() = delete;
	PlayerPickup(const PlayerPickup&) = delete;
	PlayerPickup& operator =(const PlayerPickup&) = delete;

	void update(float dt) override;
};

