#pragma once
#include <vector>
#include "Actor.h"
#include "SpriteComponent.h"
#include "Window.h"
#include "Vector2.h"
#include "RendererOGL.h"
//#include "AudioSystem.h"
#include "InputSystem.h"
#include "PhysicsSystem.h"
#include "PlaneActor.h"

using std::vector;

enum class GameState
{
	Gameplay, Pause, Quit
};

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
	Game() : isRunning(true), isUpdatingActors(false), fps(nullptr), crosshair(nullptr), state(GameState::Gameplay) {}

public:
	bool initialize();
	void load();
	void loop();
	void unload();
	void close();

	void addActor(Actor* actor);
	void removeActor(Actor* actor);
	RendererOGL& getRenderer() { return renderer; }
	//AudioSystem& getAudioSystem() { return audioSystem; }
	PhysicsSystem& getPhysicsSystem() { return physicsSystem; }

	// Game-specific
	void addPlane(class PlaneActor* plane);
	void removePlane(class PlaneActor* plane);
	vector<PlaneActor*>& getPlanes() { return planes; }

	const vector<class UIScreen*>& getUIStack() { return UIStack; }
	void pushUI(class UIScreen* screen);

	GameState getState() const { return state; }
	void setState(GameState stateP);
	InputSystem& getInputSystem() { return inputSystem; }

private:
	void processInput();
	void update(float dt);
	void render();

	bool isRunning;
	Window window;
	RendererOGL renderer;
	//AudioSystem audioSystem;
	InputSystem inputSystem;
	PhysicsSystem physicsSystem;

	bool isUpdatingActors;
	vector<Actor*> actors;
	vector<Actor*> pendingActors;

	GameState state;

	// Game specific
	//SoundEvent musicEvent;
	class FPSActor* fps;
	class SpriteComponent* crosshair;
	vector<PlaneActor*> planes;

	vector<class UIScreen*> UIStack;
};

