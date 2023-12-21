#pragma once
#include <vector>
#include <string>
#include "Vector2.h"
#include "Component.h"
class Door;
class SceneLoader : Component
{
public:
	struct doorInfo
	{
		Door* d;
		Vector2 pos;
		float scale;

		bool operator==(doorInfo const& a)
		{
			return a.d == d;
		}
	};


private:
	Vector2 tileSetSize;
	/// <summary>
	/// Cheat Sheet :
	/// 0 : Ground (0)
	/// 1 : Wall (1)
	/// 2 : Door + ID (2a) opens door when key with id "a" is picked
	/// 3 : Key + ID (3a) opens door with same id
	/// </summary>
	std::string mapContent[12][16] = {
		{"1","1","1","1","1","1","1","1","1","1","1","1","1","1","1","1"},
		{"1","0","0","0","1","0","0","0","1","1","1","1","1","1","1","1"},
		{"1","0","0","0","1","0","3b","0","2c","0","2d","0","0","1","1","1"},
		{"1","0","0","0","1","0","0","0","1","1","1","1","0","1","1","1"},
		{"1","1","1","2b","1","1","1","1","1","1","1","1","0","0","0","1"},
		{"1","0","0","0","1","0","0","0","1","3c","3e","1","0","0","0","1"},
		{"1","0","3a","0","1","0","3d","0","1","0","0","1","0","0","0","1"},
		{"1","0","0","0","1","0","0","0","1","0","0","1","0","0","0","1"},
		{"1","0","0","0","1","1","2e","1","1","2f","1","1","0","0","0","1"},
		{"1","0","0","0","2a","0","0","0","0","0","0","0","0","3f","0","1"},
		{"1","0","0","0","2a","0","0","0","0","0","0","0","0","0","0","1"},
		{"1","1","1","1","1","1","1","1","1","1","1","1","1","1","1","1"}, };

	std::vector<doorInfo > DoorList;

	Actor* mapActors[16][12];

public:
	SceneLoader(Actor* ownerP);
	~SceneLoader();
	SceneLoader() = delete;
	SceneLoader(const SceneLoader&) = delete;
	SceneLoader& operator=(const SceneLoader&) = delete;

	void checkDoors(char c);

	void load();
	void unload();
};

