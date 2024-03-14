#pragma once
#include "Actor.h"
class BowlingManager : public Actor
{
public:
	BowlingManager();


private:
	class BowlingCameraComponent* camera;
	class BowlingManagerComponent* manager;
};

