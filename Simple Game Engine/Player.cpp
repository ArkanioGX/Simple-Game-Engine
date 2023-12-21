#include "Player.h"
#include "SpriteComponent.h"
#include "Assets.h"
#include "Collider.h"
#include "PlayerPickup.h"
#include "InputComponent.h"
#include "Maths.h"

Player::Player() : Actor()
{
	SpriteComponent* sc = new SpriteComponent(this, Assets::getTexture("Player"),500);
	c = new Collider(this, {0,0,44,56}, false);
	InputComponent* ic = new InputComponent(this,c);
	PlayerPickup* pp = new PlayerPickup(this, c);
	ic->setMaxSpeed(300.f);
	ic->setMaxAngularSpeed(Maths::twoPi);
}
