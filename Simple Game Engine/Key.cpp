#include "Key.h"
#include "AnimSpriteComponent.h"
#include "KeyController.h"
#include "SceneLoader.h"
#include "Assets.h"
#include "Collider.h"


Key::Key(Vector2 p = Vector2::zero, float s = 2, char kID = '0', SceneLoader* sl = nullptr) : Actor() {
	Texture& tex = Assets::getTexture("Key");
	
	setPosition({p.x * 32 * s + tex.getWidth()/2,p.y * 32 * s + tex.getHeight()/2 });
	s /= (tex.getWidth() / 32);
	//SpriteComponent* sc = new SpriteComponent(this, tex, 200);
	AnimSpriteComponent* asc = new AnimSpriteComponent(this, tex, 200, 16);
	KeyController* kc = new KeyController(this, kID, sl);
	Collider* c = new Collider(this, { -10,-16,58,64 }, true);

	setScale(s);
	
}


