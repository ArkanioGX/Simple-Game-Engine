#include "BowlingManager.h"
#include "PinActor.h"
#include "BowlingBallActor.h"
#include "BowlingCameraComponent.h"
#include "BowlingManagerComponent.h"

BowlingManager::BowlingManager()
{
	//camera = new BowlingCameraComponent(this);
	manager = new BowlingManagerComponent(this);
}
