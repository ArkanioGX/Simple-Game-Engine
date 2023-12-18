#include "Player.h"
#include "SpriteComponent.h"
#include "Assets.h"
#include "Collider.h"
#include "InputComponent.h"
#include "Maths.h"

Player::Player() : Actor()
{
	SpriteComponent* sc = new SpriteComponent(this, Assets::getTexture("Ship"),500);
	InputComponent* ic = new InputComponent(this);
	c = new Collider(this, {0,0,Assets::getTexture("Ship").getWidth() * getScale(),Assets::getTexture("Ship").getHeight() * getScale()}, false);
	ic->setMaxSpeed(300.f);
	ic->setMaxAngularSpeed(Maths::twoPi);
}
