#include "PinActor.h"
#include "MeshComponent.h"
#include "BoxComponent.h"
#include "Assets.h"

PinActor::PinActor()
{
	Mesh* mesh = &Assets::getMesh("Mesh_Pin");

	meshComponent = new MeshComponent(this);
	meshComponent->setMesh(*mesh);

	setScale(13.0f);
	setRotation(Quaternion(Vector3::unitX, Maths::piOver2));

	boxComponent = new BoxComponent(this);
	boxComponent->setObjectBox(mesh->getBox());
}
