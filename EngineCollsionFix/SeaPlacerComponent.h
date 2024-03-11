#pragma once
#include "Component.h"
#include <Vector>

class SeaPlacerComponent : public Component
{
public:
	SeaPlacerComponent(Actor* ownerP); // Lower draw order: further back
	SeaPlacerComponent() = delete;
	SeaPlacerComponent(const SeaPlacerComponent&) = delete;
	SeaPlacerComponent& operator=(const SeaPlacerComponent&) = delete;

	void update(float dt) override;
private:
	float seaSize;
	std::vector<class PlaneActor*> seaPlane;

	const float planeSize = 1000.0f;

};

