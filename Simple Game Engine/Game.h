#pragma once
#include <vector>
#include "Window.h"
#include "RendererOGL.h"
#include "Vector2.h"
#include "Timer.h"
#include "Actor.h"
#include "Assets.h"
#include "Log.h"
#include "Player.h"
#include "SpriteComponent.h"


using std::vector;

class Game
{
public:
	static Game& instance() {
		static Game inst;
		return inst;
	}

	Game(const Game&) = delete;
	Game& operator=(const Game&) = delete;
	Game(Game&&) = delete;
	Game& operator=(Game&&) = delete;

private:
	Game() :
		isRunning(true),
		isUpdatingActors(false),
		player(nullptr)
	{}

public:
	bool initialize();
	void load();
	void loop();
	void unload();
	void close();

	Player* getPlayer() { return player; };

	void addActor(Actor* actor);
	void removeActor(Actor* actor);

	RendererOGL& getRenderer() { return renderer; }
	IRenderer::Type type() { return IRenderer::Type::OGL;}

private:
	void processInput();
	void update(float dt);
	void render();

	Window window;
	bool isRunning;
	RendererOGL renderer;

	Player* player;

	bool isUpdatingActors;
	vector<Actor*> actors;
	vector<Actor*> pendingActors;
};

