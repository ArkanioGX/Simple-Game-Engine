#include "BowlingBallActor.h"
#include "MeshComponent.h"
#include "BoxComponent.h"
#include "BowlingMoveComponent.h"
#include "Assets.h"

BowlingBallActor::BowlingBallActor()
{
	meshComponent = new MeshComponent(this);
	meshComponent->setMesh(Assets::getMesh("Mesh_Sphere"));

	boxComponent = new BoxComponent(this);
	boxComponent->setObjectBox(Assets::getMesh("Mesh_Sphere").getBox());

	moveComponent = new BowlingMoveComponent(this);

	setScale(1.3f);
	setPosition(Vector3(0, 780, -80));
	
}

BowlingMoveComponent* BowlingBallActor::getMoveComponent()
{
	return moveComponent;
}

BoxComponent* BowlingBallActor::getBoxComponent()
{
	return boxComponent;
}
