#include "SceneLoader.h"
#include "Log.h"
#include "Wall.h"

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
	for (int y = 0; y < sizeof(mapContent[0]) / sizeof(std::string); y++) {
		for (int x = 0; x < sizeof(mapContent) / sizeof(mapContent[0]); x++) {
			string currentTile = mapContent[x][y];
			if (currentTile.at(0) == '1') {
				Wall* w = new Wall({ float(y),float(x) }, 2);
			}
		}
	}
}

void SceneLoader::unload()
{
}
