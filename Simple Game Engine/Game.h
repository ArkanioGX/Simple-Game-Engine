#pragma once
#include <vector>
#include "Window.h"
#include "Renderer.h"
#include "Vector2.h"
#include "Timer.h"
#include "Actor.h"
#include "Assets.h"
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
		ballPos({100,100}),
		ballVelocity({500,500}),
		paddlePos({50,100}),
		paddleVelocity({0,450}),
		paddleDirection(0),
		wallThickness(10),
		topWall(Rectangle()),
		bottomWall(Rectangle()),
		rightWall(Rectangle())
	{}

public:
	bool initialize();
	void load();
	void loop();
	void unload();
	void close();

	void addActor(Actor* actor);
	void removeActor(Actor* actor);

	Renderer& getRenderer() { return renderer; }

private:
	void processInput();
	void update(float dt);
	void render();

	Window window;
	bool isRunning;
	Renderer renderer;

	bool isUpdatingActors;
	vector<Actor*> actors;
	vector<Actor*> pendingActors;

	Rectangle topWall;
	Rectangle bottomWall;
	Rectangle rightWall;
	const float wallThickness = 10;

	Vector2 ballPos;
	Vector2 ballVelocity;
	const float ballSize = 30;

	Vector2 paddlePos;
	Vector2 paddleVelocity;
	const float paddleWidth = 10;
	const float paddleHeight = 128;
	float paddleDirection;
};

