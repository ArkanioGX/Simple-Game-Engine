#include "Key.h"
#include "SpriteComponent.h"
#include "Assets.h"

Key::Key(Vector2 p = Vector2::zero, float s = 2, char kID = '0') {
	Texture& tex = Assets::getTexture("Key");
	SpriteComponent* sc = new SpriteComponent(this, tex, 200);

	setScale(s*2);
	setPosition({ tex.getWidth()/2 + p.x * tex.getWidth() * 2 * s,tex.getHeight()/2 + p.y * tex.getHeight() * s * 2 });
}
