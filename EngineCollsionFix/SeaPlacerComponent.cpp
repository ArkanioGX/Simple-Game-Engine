#include "SeaPlacerComponent.h"
#include "Vector3.h"
#include "PlaneActor.h"
#include "Maths.h"
#include "Actor.h"
#include "Game.h"
#include "PlayerPlaneActor.h"
#include "Log.h"

SeaPlacerComponent::SeaPlacerComponent(Actor* ownerP) :
	Component(ownerP),
	seaSize(4.0f)
{
	
	
	const float start = -(planeSize/2) * seaSize;
	for (int i = 0; i < seaSize; i++)
	{
		for (int j = 0; j < seaSize; j++)
		{
			PlaneActor* p = new PlaneActor();
			p->setPosition(Vector3(start + i * planeSize, start + j * planeSize, 0.0));
			seaPlane.push_back(p);
		}
	}
}

void SeaPlacerComponent::update(float dt)
{
	for (int i = 0; i < seaPlane.size(); i++) {
		PlaneActor* currentPlane = seaPlane[i];

		float playerX = owner.getGame().getPlayer()->getPosition().x;
		float playerY = owner.getGame().getPlayer()->getPosition().y;
		float planeX = currentPlane->getPosition().x;
		float planeY = currentPlane->getPosition().y;

		float max = (planeSize / 2) * seaSize;

		//X Check
		if ((planeX - playerX) < -max) {
			Vector3 currentPlanePos = currentPlane->getPosition();
			Vector3 idealPos = Vector3(currentPlanePos.x + max*2, currentPlanePos.y, currentPlanePos.z);
			currentPlane->setPosition(idealPos);
		}
		else if ((planeX - playerX) > max) {
			Vector3 currentPlanePos = currentPlane->getPosition();
			Vector3 idealPos = Vector3(currentPlanePos.x - max * 2, currentPlanePos.y, currentPlanePos.z);
			currentPlane->setPosition(idealPos);
		}

		//Y Check
		if ((planeY - playerY) < -max) {
			Vector3 currentPlanePos = currentPlane->getPosition();
			Vector3 idealPos = Vector3(currentPlanePos.x , currentPlanePos.y + max * 2, currentPlanePos.z);
			currentPlane->setPosition(idealPos);
		}
		else if ((planeY - playerY) > max) {
			Vector3 currentPlanePos = currentPlane->getPosition();
			Vector3 idealPos = Vector3(currentPlanePos.x , currentPlanePos.y - max * 2, currentPlanePos.z);
			currentPlane->setPosition(idealPos);
		}
	}
}
