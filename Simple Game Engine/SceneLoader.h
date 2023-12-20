#pragma once
#include <vector>
#include <string>
#include "Vector2.h"
#include "Component.h"
class Door;
class SceneLoader : Component
{
private:
	Vector2 tileSetSize;
	/// <summary>
	/// Cheat Sheet :
	/// 0 : Ground (0)
	/// 1 : Wall (1)
	/// 2 : Wall Inside (2)
	/// 3 : Door + ID (3a) opens door when key with id a is picked
	/// 4 : Key + ID (4a) opens door with same id
	/// </summary>
	std::string mapContent[12][16] = {
		{"1","1","1","1","1","1","1","1","1","1","1","1","1","1","1","1"},
		{"1","0","0","0","0","0","0","0","0","0","0","0","0","0","0","1"},
		{"1","0","0","0","0","0","0","0","0","0","0","0","0","0","0","1"},
		{"1","0","0","0","0","0","0","0","0","0","0","0","0","0","0","1"},
		{"1","0","0","0","0","0","0","0","0","0","0","0","0","0","0","1"},
		{"1","0","0","0","0","0","0","0","0","0","0","0","0","0","0","1"},
		{"1","0","0","0","0","0","0","0","0","0","0","0","0","0","0","1"},
		{"1","0","0","0","0","0","0","0","0","0","0","0","0","0","0","1"},
		{"1","0","0","0","0","0","0","0","0","0","0","0","0","0","0","1"},
		{"1","0","0","0","0","0","0","0","0","0","0","0","0","0","0","1"},
		{"1","0","0","0","0","0","0","0","0","0","0","0","0","0","0","1"},
		{"1","1","1","1","1","1","1","1","1","1","1","1","1","1","1","1"}, };

	//std::vector<Door*> DoorList;

	Actor* mapActors[16][12];

public:
	static SceneLoader* instance;

	SceneLoader(Actor* ownerP);
	~SceneLoader();
	SceneLoader() = delete;
	SceneLoader(const SceneLoader&) = delete;
	SceneLoader& operator=(const SceneLoader&) = delete;

	void load();
	void unload();
};

