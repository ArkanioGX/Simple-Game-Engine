#include "DoorController.h"
#include "Actor.h"
DoorController::DoorController(Actor* ownerP, char kID) : Component(ownerP), keyID(kID) {

}

DoorController::~DoorController()
{
}

bool DoorController::checkKeyID(char kID)
{
	return keyID == kID;
}

void DoorController::destroyDoor()
{
	owner.setState(Actor::ActorState::Dead);
}
