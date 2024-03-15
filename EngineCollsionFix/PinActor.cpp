#include "PinActor.h"
#include "MeshComponent.h"
#include "BoxComponent.h"
#include "Assets.h"

PinActor::PinActor()
{
	MeshComponent* mc = new MeshComponent(this);
	mc->setMesh(Assets::getMesh("Mesh_Pin"));

	box = new BoxComponent(this);
	box->setObjectBox(Assets::getMesh("Mesh_Pin").getBox());
}
