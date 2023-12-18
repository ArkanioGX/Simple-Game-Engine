#include "Collider.h"
#include "Collision.h"
#include "Log.h"

std::vector<Collider*> Collider::collList = {};

Collider::Collider(Actor* ownerP, Rectangle r, bool CPT = false) : Component(ownerP), rect(r)
{
	canPassThrough = CPT;
	addCollider(this);

	
}

Collider::~Collider()
{
	removeCollider(this);
}

std::vector<Collision*> Collider::checkCollision()
{
	std::vector<Collision*> list = {};
	for (Collider* c : collList)
	{
		if (c != this) {
			Rectangle r1 = { owner.getPosition().x + rect.x ,owner.getPosition().y + rect.y,rect.width,rect.height};
			Rectangle r2 = { c->getActor()->getPosition().x + rect.x ,c->getActor()->getPosition().y + rect.y,c->rect.width,c->rect.height};

			if (checkRectangle(r1, r2)){
				Log::info("If passed");
				list.push_back(new Collision(c->getActor(), c));
			}
		}
	}
	return list;
}

bool Collider::checkRectangle(Rectangle r1, Rectangle r2) {
	if (r1.x + r1.width >= r2.x &&    // r1 right edge past r2 left
		r1.x <= r2.x + r2.width &&    // r1 left edge past r2 right
		r1.y + r1.height >= r2.y &&    // r1 top edge past r2 bottom
		r1.y <= r2.y + r2.height) {    // r1 bottom edge past r2 top
		return true;
	}
	return false;
}




