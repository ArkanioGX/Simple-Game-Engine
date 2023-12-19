#include "Player.h"
#include "SpriteComponent.h"
#include "Assets.h"
#include "Collider.h"
#include "InputComponent.h"
#include "Maths.h"

Player::Player() : Actor()
{
	SpriteComponent* sc = new SpriteComponent(this, Assets::getTexture("Tileset"),500);
	c = new Collider(this, {0,0,Assets::getTexture("Tileset").getWidth() * getScale(),Assets::getTexture("Tileset").getHeight() * getScale()}, false);
	InputComponent* ic = new InputComponent(this,c);
	ic->setMaxSpeed(300.f);
	ic->setMaxAngularSpeed(Maths::twoPi);
}
