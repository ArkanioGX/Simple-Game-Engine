#include "TileComponent.h"

TileComponent::TileComponent(Actor* ownerP, Texture& textureP, int tileID, int tileSize, int drawOrderP) :
	SpriteComponent(ownerP, textureP, drawOrderP, Rectangle::nullRect),
	id(tileID),
	size(tileSize)
{
	setRectFromId();
}

TileComponent::~TileComponent()
{
}

void TileComponent::setRectFromId() {
	int nRow = texture.getWidth() / size;

	float x = int(id % nRow) * size;
	float y = int(id / nRow) * size;

	rect = { x,y,x + size,y + size };
}