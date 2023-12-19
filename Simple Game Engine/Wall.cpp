#include "Wall.h"
#include "TileComponent.h"
#include "Assets.h"
#include "Collider.h"


Wall::Wall(Vector2 pos = Vector2::zero, float size = 2) : Actor() {
	setScale(size);
	setPosition({ 16 + pos.x * 32 * size,16 + pos.y * 32 * size });

	TileComponent* tc =	new TileComponent(this, Assets::getTexture("Tileset"), 0);
	Collider* c = new Collider(this, { -16,-16,64,64 }, false);
}
