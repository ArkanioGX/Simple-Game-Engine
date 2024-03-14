#include "BowlingBallActor.h"
#include "MeshComponent.h"
#include "Assets.h"

BowlingBallActor::BowlingBallActor()
{
	MeshComponent* mc = new MeshComponent(this);
	mc->setMesh(Assets::getMesh("Mesh_Sphere"));
	setScale(1.4f);
	setPosition(Vector3(0, 780, -80));
	
}