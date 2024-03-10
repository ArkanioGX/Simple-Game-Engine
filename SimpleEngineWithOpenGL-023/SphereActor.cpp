#include "SphereActor.h"
#include "Assets.h"
#include "MeshComponent.h"

SphereActor::SphereActor()
{
	MeshComponent* mc = new MeshComponent(this);
	mc->setMesh(Assets::getMesh("Mesh_Sphere"));
}
