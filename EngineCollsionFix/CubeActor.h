#pragma once
#include "Actor.h"
class CubeActor : public Actor
{
public:
	CubeActor();

private:
	class BoxComponent* box;
};

