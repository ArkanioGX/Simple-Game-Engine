#include "PlayerPickup.h"

PlayerPickup::PlayerPickup(Actor* ownerP, Collider* coll) : Component(ownerP), c(coll)
{

}

void PlayerPickup::update(float dt)
{
	c->checkTrigger();
}
