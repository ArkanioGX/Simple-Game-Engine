#pragma once
#include <vector>
#include "SpriteComponent.h"
using std::vector;
class AnimSpriteComponent : public SpriteComponent
{
public:
	AnimSpriteComponent(Actor* ownerP, const vector<Texture*>& textureP, int drawOrderP = 100, Rectangle rP = Rectangle::nullRect);
	virtual ~AnimSpriteComponent();
	AnimSpriteComponent() = delete;
	AnimSpriteComponent(const AnimSpriteComponent&) = delete;
	AnimSpriteComponent& operator=(const AnimSpriteComponent&) = delete;

	float getAnimFps() const { return animFPS; }
	void setAnimTextures(const vector<Texture*>& texturesP);
	void setAnimFPS(float animFPSP);

	void update(float dt);

private:
	vector<Texture*> animTextures;
	float currentFrame;
	float animFPS;
};

