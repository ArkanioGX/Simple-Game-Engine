#include "BoatActor.h"
#include "MeshComponent.h"
#include "Assets.h"
#include "BoxComponent.h"

BoatActor::BoatActor()
{
	setScale(150);

	MeshComponent* mc = new MeshComponent(this);
	mc->setMesh(Assets::getMesh("Mesh_Cube"));
	// Add collision box
	BoxComponent* bc = new BoxComponent(this);
	bc->setObjectBox(Assets::getMesh("Mesh_Cube").getBox());
}
