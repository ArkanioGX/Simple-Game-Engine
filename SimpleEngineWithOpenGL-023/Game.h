#pragma once
#include <algorithm>
#include <vector>
#include "Actor.h"
#include "SpriteComponent.h"
#include "Window.h"
#include "InputComponent.h"
#include "InputSystem.h"
#include "Vector2.h"
#include "RendererOGL.h"
#include "Camera.h"
#include "PhysicsSystem.h"
#include "PlaneActor.h"

using std::vector;

class Game
{
public:
	static Game& instance()
	{
		static Game inst;
		return inst;
	}

	Game(const Game&) = delete;
	Game& operator=(const Game&) = delete;
	Game(Game&&) = delete;
	Game& operator=(Game&&) = delete;

private:
	Game() : isRunning(true),
		isUpdatingActors(false),
		fps(nullptr),
		crosshair(nullptr),
		follow(nullptr),
		orbit(nullptr),
		path(nullptr)
	{}

public:
	bool initialize();
	void load();
	void loop();
	void unload();
	void close();

	void addActor(Actor* actor);
	void removeActor(Actor* actor);
	RendererOGL& getRenderer() { return renderer; }
	PhysicsSystem& getPhysicsSystem() { return physicsSystem; }

	// Game-specific
	void addPlane(class PlaneActor* plane);
	void removePlane(class PlaneActor* plane);
	vector<PlaneActor*>& getPlanes() { return planes; }

private:
	void processInput();
	void update(float dt);
	void render();

	void changeCamera(int mode);

	bool isRunning;
	Window window;
	RendererOGL renderer;
	InputSystem inputSystem;
	PhysicsSystem physicsSystem;

	bool isUpdatingActors;
	vector<Actor*> actors;
	vector<Actor*> pendingActors;
	Camera* camera;

	class FPSActor* fps;
	class SpriteComponent* crosshair;
	class FollowActor* follow;
	class OrbitActor* orbit;
	class SplineActor* path;

	vector<PlaneActor*> planes;
};

