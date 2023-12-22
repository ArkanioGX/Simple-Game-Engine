#include "SceneLoader.h"
#include "Log.h"
#include "Wall.h"
#include "Ground.h"
#include "Key.h"
#include "Door.h"


SceneLoader::SceneLoader(Actor* ownerP) : Component(ownerP)
{
	load();
}

SceneLoader::~SceneLoader()
{
	unload();
}

void SceneLoader::checkDoors(char c)
{
	std::vector<doorInfo> toErase;
	for (doorInfo d : DoorList) {
		if (d.d->getDoorController()->checkKeyID(c)) {
			Tile* t = new Ground({ float(d.pos.x),float(d.pos.y) }, d.scale);
			d.d->getDoorController()->destroyDoor();
			toErase.push_back(d);
		}
	}
	for (doorInfo d : toErase) {
		DoorList.erase(std::remove(DoorList.begin(), DoorList.end(), d), DoorList.end());
	}
}

void SceneLoader::load() {
	float Scale = 2;
	for (int y = 0; y < sizeof(mapContent[0]) / sizeof(std::string); y++) {
		for (int x = 0; x < sizeof(mapContent) / sizeof(mapContent[0]); x++) {
			string currentTile = mapContent[x][y];
			Tile* t;
			Key* k;
			Door* d;
			doorInfo di;
				switch (currentTile.at(0)) {
				case '0':

					t = new Ground({ float(y),float(x) }, Scale);
					break;
				case '1':

					t = new Wall({ float(y),float(x) }, Scale);
					break;
				case '2':
					d = new Door({ float(y),float(x) }, Scale, currentTile.at(1));
					t = d;
					di.d = d;
					di.pos = { float(y),float(x) };
					di.scale = Scale;
					DoorList.push_back(di);

					break;
				case '3':

					t = new Ground({ float(y),float(x) }, Scale);
					k = new Key({ float(y),float(x) }, Scale, currentTile.at(1), this);
					break;
				default:

					break;
				}
		}
	}
}



void SceneLoader::unload()
{
}
