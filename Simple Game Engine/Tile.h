#pragma once
#include "Actor.h"
class Tile : public Actor
{
public:
	Tile() = delete;
	Tile(Vector2 p, float s, bool hasC, bool CPT, int tid);

private:

	bool canPassThrough;
	Vector2 pos;
	float size;

};

