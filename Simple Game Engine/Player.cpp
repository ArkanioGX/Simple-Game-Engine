#include "Player.h"
#include "SpriteComponent.h"
#include "Assets.h"
#include "InputComponent.h"
#include "Maths.h"

Player::Player() : Actor()
{
	SpriteComponent* sc = new SpriteComponent(this, Assets::getTexture("Ship"),500);
	InputComponent* ic = new InputComponent(this);
	ic->setMaxSpeed(300.f);
	ic->setMaxAngularSpeed(Maths::twoPi);
}
