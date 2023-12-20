#include "Tile.h"
#include "TileComponent.h"
#include "Assets.h"
#include "Collider.h"
#include "Log.h"

Tile::Tile(Vector2 p, float s, bool CPT, int tid) : pos(p),canPassThrough(CPT),size(s)
{
	Texture& tex = Assets::getTexture("Tileset");

	setScale(s);
	setPosition({ (tex.getWidth() / 2) + p.x * tex.getWidth() * s,(tex.getHeight() / 2) + p.y * tex.getHeight() * s });
	TileComponent* tc = new TileComponent(this, tex , tid);
	
	Collider* c = new Collider(this, { -16,-16,64,64 }, CPT);
}
