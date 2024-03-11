#include "SeaPlacerActor.h"
#include "SeaPlacerComponent.h"

SeaPlacerActor::SeaPlacerActor():
	SPComponent(nullptr)
{
	SPComponent = new SeaPlacerComponent(this);
}
