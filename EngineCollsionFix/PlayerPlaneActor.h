#pragma once
#include "Actor.h"

class PlayerPlaneActor : public Actor
{
public:
	PlayerPlaneActor();

private:
	class AudioComponent* audio;

};

