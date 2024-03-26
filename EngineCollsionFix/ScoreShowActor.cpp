#include "ScoreShowActor.h"
#include "ScoreShowComponent.h"
#include "MeshComponent.h"
#include "Assets.h"

ScoreShowActor::ScoreShowActor():
	Actor()
{
	mesh = new MeshComponent(this);
	mesh->setMesh(Assets::getMesh("Mesh_ScorePlane"));

	show = new ScoreShowComponent(this);
}

MeshComponent* ScoreShowActor::getMesh()
{
	return mesh;
}

ScoreShowComponent* ScoreShowActor::getScoreShow()
{
	return show;
}
