#include "CubeActor.h"
#include "MeshComponent.h"
#include "BoxComponent.h"
#include "Assets.h"

CubeActor::CubeActor()
{
	MeshComponent* mc = new MeshComponent(this);
	mc->setMesh(Assets::getMesh("Mesh_Cube"));

	box = new BoxComponent(this);
	box->setObjectBox(Assets::getMesh("Mesh_Cube").getBox());
}
