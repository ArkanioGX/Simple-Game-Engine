#include "KeyController.h"
#include "Log.h"
#include "Component.h"
#include "SceneLoader.h"
#include "Actor.h"



KeyController::KeyController(Actor* ownerP, char id, SceneLoader* sl) :Component(ownerP), keyID(id), scene(sl)
{
}


void KeyController::OnTrigger(Collision* coll)
{
	Log::info("test");
	scene->checkDoors(keyID);
	owner.setState(Actor::ActorState::Dead);
}
