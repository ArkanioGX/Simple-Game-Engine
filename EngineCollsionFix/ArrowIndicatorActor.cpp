#include "ArrowIndicatorActor.h"
#include "MeshComponent.h"
#include "Assets.h"

ArrowIndicatorActor::ArrowIndicatorActor()
{
	MeshComponent* mc = new MeshComponent(this);
	mc->setMesh(Assets::getMesh("Mesh_Arrow"));
	setScale(15);
	setPosition(Vector3(0, 750, -100));
	setRotation(Quaternion(Vector3::unitX, Maths::pi));
}
