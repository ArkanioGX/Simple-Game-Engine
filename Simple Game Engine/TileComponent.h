#pragma once
#include "SpriteComponent.h"

class TileComponent : public SpriteComponent
{
public:
	TileComponent(Actor* ownerP, Texture& textureP, int tileID = 0, int tileSize = 16, int drawOrderP = 100);
	virtual ~TileComponent();
	TileComponent() = delete;
	TileComponent(const TileComponent&) = delete;
	TileComponent& operator=(const TileComponent&) = delete;

private:
	int id, size;

	void setRectFromId();
};

