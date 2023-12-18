#pragma once
#include "Actor.h"
#include "Collider.h"
#include <SDL_stdinc.h>

class Player : public Actor
{
	Collider* c;
public:

	Player();

	Collider* getCollider() {return c;}
};

