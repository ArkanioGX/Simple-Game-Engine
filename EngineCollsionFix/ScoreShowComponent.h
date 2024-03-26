#pragma once
#include "Component.h"
class ScoreShowComponent : public Component
{
public:
	ScoreShowComponent(class Actor* ownerP);

	void setScore(int s);
};

