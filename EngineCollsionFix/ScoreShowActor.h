#pragma once
#include "Actor.h"
class ScoreShowActor : public Actor
{
public:
	ScoreShowActor();

	class MeshComponent* getMesh();
	class ScoreShowComponent* getScoreShow();

private:
	class MeshComponent* mesh;
	class ScoreShowComponent* show;
};

