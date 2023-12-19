#pragma once
#include <vector>
#include <string>
#include "Vector2.h"
#include "Actor.h"
class Scene
{
private:
	Vector2 tileSetSize;
	std::string mapContent[16][12];
	Actor* mapActors[16][12];

public:
	void load();
};

