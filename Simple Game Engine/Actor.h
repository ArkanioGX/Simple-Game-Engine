#pragma once
#include <vector>
#include <memory>
#include <set>
#include "Vector2.h"
#include <SDL_stdinc.h>

using std::vector;

class Game;
class Component;

class Actor
{
public:

	enum class ActorState
	{
		Active, Paused, Dead
	};

	Actor();
	virtual ~Actor();
	Actor(const Actor&) = delete;
	Actor& operator=(const Actor&) = delete;

	void processInput(const Uint8* keyState);
	virtual void actorInput(const Uint8* keyState);

	Game& getGame() const { return game; }
	const ActorState getState() const { return state; }
	const Vector2 getPosition() const { return position; }
	const float getScale() const { return scale; }
	const float getRotation() const { return rotation; }
	const Vector2 getForward() const;

	void setPosition(Vector2 positionP);
	void setScale(float scaleP);
	void setRotation(float rotation);

	void update(float dt);
	void updateComponents(float dt);
	virtual void updateActor(float dt);
	void addComponent(Component* component);
	void removeComponent(Component* component);

	/*template <typename T> std::shared_ptr<T> GetComponent()
	{
		// Removed check to see if we are trying to get a class that 
		// derives from component.

		for (auto exisitingComponent : components)
		{
			if (std::dynamic_cast<T*>(p)(exisitingComponent))
			{
				return std::dynamic_cast<T*>(p)(exisitingComponent);
			}
		}

		return nullptr;
	};*/

private:
	Game& game;
	ActorState state;
	Vector2 position;
	float scale;
	float rotation;  // Rotation in radians.

	vector<Component*> components;
};


