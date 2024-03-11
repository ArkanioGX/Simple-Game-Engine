#include "BoatSpawnerComponent.h"
#include "BoatActor.h"
#include "Actor.h"
#include <time.h>
#include <stdlib.h> 
#include"Game.h"
#include "Log.h"
#include "PlayerPlaneActor.h"

BoatSpawnerComponent::BoatSpawnerComponent(Actor* ownerP):
	Component(ownerP),
	yOffset(-1800),
	xRange(700),
	timeCount(0),
	delay(0.8f)
{
	spawnBoat();
}

void BoatSpawnerComponent::update(float dt)
{
	timeCount += dt;

	if (timeCount >= delay) {
		timeCount -= delay;
		spawnBoat();
	}
}

void BoatSpawnerComponent::spawnBoat()
{

	BoatActor* BA = new BoatActor();

	Vector3 playerPos = owner.getGame().getPlayer()->getPosition();

	float x = playerPos.x + (rand() % int(xRange * 2) - xRange);
	float y = playerPos.y + yOffset;
	BA->setPosition(Vector3(x, y, 0.0f));
	boatList.push_back(BA);
}


