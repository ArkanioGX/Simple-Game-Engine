#include "PlayerPlaneActor.h"
#include "MeshComponent.h"
#include "Assets.h"
#include "AudioComponent.h"
#include "Log.h"

PlayerPlaneActor::PlayerPlaneActor() {
	MeshComponent* mc = new MeshComponent(this);
	mc->setMesh(Assets::getMesh("Mesh_AirPlane"));
	audio = new AudioComponent(this);

	Log::info("Hello");
}
