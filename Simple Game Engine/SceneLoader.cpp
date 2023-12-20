#include "SceneLoader.h"
#include "Log.h"
#include "Wall.h"
#include "Ground.h"
#include "Key.h"
#include "Door.h"

SceneLoader* SceneLoader::instance = nullptr;

SceneLoader::SceneLoader(Actor* ownerP) : Component(ownerP)
{
	if (instance == nullptr) {
		instance = this;
	}
	else {
		delete this;
		return;
	}
	load();
}

SceneLoader::~SceneLoader()
{
	unload();
}

void SceneLoader::load() {
	float Scale = 2;
	for (int y = 0; y < sizeof(mapContent[0]) / sizeof(std::string); y++) {
		for (int x = 0; x < sizeof(mapContent) / sizeof(mapContent[0]); x++) {
			string currentTile = mapContent[x][y];
			Tile* t;
			Key* k;
				switch (currentTile.at(0)) {
				case '0':

					t = new Ground({ float(y),float(x) }, Scale);
					break;
				case '1':

					t = new Wall({ float(y),float(x) }, Scale);
					break;
				case '2':

					t = new Door({ float(y),float(x) }, Scale, currentTile.at(1));
					break;
				case '3':

					t = new Ground({ float(y),float(x) }, Scale);
					k = new Key({ float(y),float(x) }, Scale, currentTile.at(1));
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
