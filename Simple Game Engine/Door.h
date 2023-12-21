#pragma once
#include "Tile.h"
#include "DoorController.h"

class Door : public Tile
{
	char keyID;
	DoorController* dc;


public:

	Door(Vector2 pos, float size, char kID);
	DoorController* getDoorController() { return dc; }
	
};

