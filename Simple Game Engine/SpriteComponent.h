#pragma once
#include "Component.h"
#include "Texture.h"


class SpriteComponent : public Component
{
public:
	SpriteComponent(Actor* ownerP, Texture& textureP, int drawOrderP = 100, Rectangle rP = Rectangle::nullRect);
	virtual ~SpriteComponent();
	SpriteComponent() = delete;
	SpriteComponent(const SpriteComponent&) = delete;
	SpriteComponent& operator=(const SpriteComponent&) = delete;

	virtual void setTexture(const Texture& textureP);
	virtual void draw(Renderer& renderer);

	int getDrawOrder() const { return drawOrder; }
	int getTexWidth() const { return texWidth; }
	int getTxHeight() const { return texHeight; }

protected:
	Texture texture;
	int drawOrder;
	int texWidth;
	int texHeight;
	Rectangle rect;
};

