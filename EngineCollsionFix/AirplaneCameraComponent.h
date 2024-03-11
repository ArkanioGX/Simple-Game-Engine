#pragma once
#include "CameraComponent.h"
class AirplaneCameraComponent : public CameraComponent
{
public:
	AirplaneCameraComponent(Actor* ownerP);

	void update(float dt) override;

private:
	Vector3 offset;
};

