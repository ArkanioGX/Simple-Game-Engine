#pragma once
#include "Component.h"
#include <vector>


class BoatSpawnerComponent : public Component
{
public:
	BoatSpawnerComponent(Actor* ownerP); // Lower draw order: further back

	void update(float dt) override;

	void spawnBoat();
private:
	float yOffset;
	float xRange;
	float delay;

	float timeCount;

	std::vector<class BoatActor*> boatList;
};

