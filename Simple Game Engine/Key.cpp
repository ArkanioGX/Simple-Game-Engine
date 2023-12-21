#include "Key.h"
#include "SpriteComponent.h"
#include "KeyController.h"
#include "SceneLoader.h"
#include "Assets.h"
#include "Collider.h"


Key::Key(Vector2 p = Vector2::zero, float s = 2, char kID = '0', SceneLoader* sl = nullptr) : Actor() {
	Texture& tex = Assets::getTexture("Key");
	
	SpriteComponent* sc = new SpriteComponent(this, tex, 200);
	KeyController* kc = new KeyController(this, kID, sl);
	Collider* c = new Collider(this, { -10,-16,58,64 }, true);

	setScale(s*2);
	setPosition({ tex.getWidth()/2 + p.x * tex.getWidth() * 2 * s,tex.getHeight()/2 + p.y * tex.getHeight() * s * 2 });
}


