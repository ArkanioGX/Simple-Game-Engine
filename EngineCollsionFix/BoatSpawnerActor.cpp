#include "BoatSpawnerActor.h"
#include "BoatSpawnerComponent.h"

BoatSpawnerActor::BoatSpawnerActor()
{
	BoatSpawnerComponent* BSComponent = new BoatSpawnerComponent(this);
}
