#pragma once
#include "Actor.h"
#include "Vector2.h"
#include "Tile.h"
class Wall : public Tile
{
public:
	Wall(Vector2 pos, float size);
};

