#pragma once
#include "Tile.h"
class Door : public Tile
{
	char keyID;

public:

	Door(Vector2 pos, float size, char kID);

	bool checkKeyID(char keyID) {

	}


};

