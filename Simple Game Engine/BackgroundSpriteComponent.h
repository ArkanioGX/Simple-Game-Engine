#pragma once
#include "SpriteComponent.h"
#include <vector>
using std::vector;

class BackgroundSpriteComponent : public SpriteComponent
{
public:
	BackgroundSpriteComponent(Actor* ownerP, const vector<Texture*>& texturesP, int drawOrderP = 100, Rectangle rP = Rectangle::nullRect);
	virtual ~BackgroundSpriteComponent();
	BackgroundSpriteComponent() = delete;
	BackgroundSpriteComponent(const BackgroundSpriteComponent&) = delete;
	BackgroundSpriteComponent& operator=(const BackgroundSpriteComponent&) = delete;

	float getScrollSpeed() const { return scrollSpeed; }
	void setTextures(const vector<Texture*>& texturesP);
	void setScreenSize(const Vector2& screenSizeP);
	void setScrollSpeed(float scrollSpeedP);

	void update(float dt) override;
	void draw(Renderer& renderer) override;


private:
	struct BGTexture 
	{
		BGTexture(Texture& t, Vector2 o) : texture(t), offset(o) {}
			Texture& texture;
			Vector2 offset;
	};
	std::vector<BGTexture> textures;
	Vector2 screenSize;
	float scrollSpeed;
};

