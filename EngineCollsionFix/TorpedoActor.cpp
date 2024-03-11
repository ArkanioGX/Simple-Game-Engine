#include "TorpedoActor.h"
#include "MoveComponent.h"
#include "MeshComponent.h"
#include "TorpMoveComponent.h"
#include "Assets.h"

TorpedoActor::TorpedoActor()
{
	meshComponent = new MeshComponent(this);
	meshComponent->setMesh(Assets::getMesh("Mesh_Sphere"));

	moveComponent = new TorpMoveComponent(this);
}

