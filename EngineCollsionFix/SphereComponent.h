#pragma once
#include "Component.h"
#include "Sphere.h"

class SphereComponent : public Component
{
public:
	SphereComponent(class Actor* ownerP, int updateOrderP = 100);
	virtual ~SphereComponent();

	const Sphere& getWorldSphere() const { return worldSphere; }
	void setObjectSphere(const Sphere& objectBoxP);
	void setShouldRotate(bool shouldRotateP);

	void onUpdateWorldTransform() override;


private:
	Sphere objectSphere;
	Sphere worldSphere;
	bool shouldRotate;
};

