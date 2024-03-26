#include "ScoreShowComponent.h"
#include "Actor.h"
#include "ScoreShowActor.h"
#include "MeshComponent.h"
#include "Assets.h"

ScoreShowComponent::ScoreShowComponent(Actor* ownerP) :
	Component(ownerP)
{
}

void ScoreShowComponent::setScore(int s)
{
	ScoreShowActor* actor = static_cast<ScoreShowActor*>(&owner);
	actor->getMesh()->setTextureIndex(s);
}
