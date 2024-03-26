#include "PinActor.h"
#include "MeshComponent.h"
#include "BoxComponent.h"
#include "Assets.h"
#include "PinMoveComponent.h"

PinActor::PinActor()
{
	MeshComponent* mc = new MeshComponent(this);
	mc->setMesh(Assets::getMesh("Mesh_Pin"));

	setScale(20.0f);

	box = new BoxComponent(this);
	box->setObjectBox(Assets::getMesh("Mesh_Pin").getBox());

	moveComponent = new PinMoveComponent(this);
}

PinMoveComponent* PinActor::getMoveComponent()
{
	return moveComponent;
}

BoxComponent* PinActor::getBoxComponent()
{
	return box;
}
