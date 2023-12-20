#include "Game.h"
#include "Actor.h"
#include "SpriteComponent.h"
#include "TileComponent.h"
#include "AnimSpriteComponent.h"
#include "Timer.h"
#include "Assets.h"
#include "Wall.h"
#include "SceneLoader.h"
#include "BackgroundSpriteComponent.h"
#include "Player.h"
#include <iostream>
#include <algorithm>

bool Game::initialize() {
	bool isWindowInit = window.initialize();
	bool isRendererInit = renderer.initialize(window);

	int windowHeight = window.getHeight();
	int windowWidth = window.getWidth();

	return isWindowInit && isRendererInit;
}

void Game::loop() {
	Timer timer;
	float dt = 0;
	while (isRunning) {
		float dt = timer.computeDeltaTime() / 1000.0f;
		processInput();
		update(dt);
		render();
		timer.delayTime();
	}
}

void Game::close() {
	Log::info("Closed");
	renderer.close();
	window.close();
	SDL_Quit();
}

void Game::processInput() {
	SDL_Event event;
	while (SDL_PollEvent(&event))
	{
		switch (event.type) {
		case SDL_QUIT:
			isRunning = false;
			break;
		}
	}
	const Uint8* keyboardState = SDL_GetKeyboardState(nullptr);

	if (keyboardState[SDL_SCANCODE_ESCAPE]) {
		isRunning = false;
	}

	isUpdatingActors = true;
	for (auto actor:actors){
		actor->processInput(keyboardState);
	}
	isUpdatingActors = false;
}

void Game::update(float dt) {
	//Update Actors
	isUpdatingActors = true;
	for (auto actor : actors) {
		actor->update(dt);
	}
	isUpdatingActors = false;

	for (auto pendingActor : pendingActors) {
		actors.emplace_back(pendingActor);
	}
	pendingActors.clear();

	//Delete dead actors
	vector<Actor*> deadActors;
	for (auto actor : actors) {
		if (actor->getState() == Actor::ActorState::Dead) {
			deadActors.emplace_back(actor);
		}
	}
	for (auto deadActor : deadActors) {
		delete deadActor;
	}
}

void Game::render() {
	renderer.beginDraw();

	renderer.draw();

	renderer.endDraw();
}

void Game::addActor(Actor* actor) {
	if (isUpdatingActors) {
		pendingActors.emplace_back(actor);
	}
	else {
		actors.emplace_back(actor);
	}
}

void Game::removeActor(Actor* actor) {
	auto iter = std::find(begin(pendingActors), end(pendingActors), actor);
	if (iter != end(pendingActors)) {
		std::iter_swap(iter, end(pendingActors) - 1); 
		pendingActors.pop_back();
	}
	iter = std::find(begin(actors), end(actors), actor);
	if (iter != end(actors)) {
		std::iter_swap(iter, end(actors) - 1);
		actors.pop_back();
	}
}

void Game::load() {
	Assets::loadTexture(renderer,"Res/Ship01.png","Ship");
	Assets::loadTexture(renderer, "Res/Ship02.png", "ship02");
	Assets::loadTexture(renderer, "Res/Ship03.png", "ship03");
	Assets::loadTexture(renderer, "Res/Ship04.png", "ship04");
	Assets::loadTexture(renderer, "Res/Farback01.png", "farback01");
	Assets::loadTexture(renderer, "Res/Farback02.png", "farback02");
	Assets::loadTexture(renderer, "Res/Stars.png", "Stars");
	Assets::loadTexture(renderer, "Res/Hero.png", "Player");
	Assets::loadTexture(renderer, "Res/Key.png", "Key");
	Assets::loadTexture(renderer, "Res/TS_Dungeon1.png", "Tileset");
	

	Actor* Scene = new Actor();
	SceneLoader* sl = new SceneLoader(Scene);

	player = new Player();
	player->setPosition({ 100,400 });

	/*float scale = 2;
	for (int x = 0; x < 16; x++)
	{
		for (int y = 0; y < 12; y++)
		{
			Actor* wallAct = new Actor();
			int TileID = 1;
			if (x == 0 || x == 15 || y == 0 || y == 11) {
				Wall* w = new Wall({ float(x),float(y) }, 2);
			}
			TileComponent* wall = new TileComponent(wallAct, Assets::getTexture("Tileset"), TileID);
			wallAct->setScale(scale);
			wallAct->setPosition({ 16 + x * 32 * scale,16 + y * 32 * scale });
		}
	}*/

	player->getCollider()->checkCollision();
	player->setScale(4);

	

	/*float scale = 2;
	for (int x = 6; x < 8; x++)
	{
		for (int y = 4; y < 12; y++)
		{
			Actor* wallAct = new Actor();
			TileComponent* wall = new TileComponent(wallAct, Assets::getTexture("Tileset"), 0);
			wallAct->setScale(scale);
			wallAct->setPosition({ 16 + x * 32 * scale,16 + y * 32 * scale });
		}
	}

	for (int x = 9; x < 11; x++)
	{
		for (int y = 4; y < 12; y++)
		{
			Actor* wallAct = new Actor();
			TileComponent* wall = new TileComponent(wallAct, Assets::getTexture("Tileset"), 0);
			wallAct->setScale(scale);
			wallAct->setPosition({ 16 + x * 32 * scale,16 + y * 32 * scale });
		}
	}*/

	/*vector<Texture*> animTextures{
		&Assets::getTexture("ship01"),
		&Assets::getTexture("ship02"),
		&Assets::getTexture("ship03"),
		&Assets::getTexture("ship04")
	};
	Actor* ship = new Actor();
	AnimSpriteComponent* animatedSprite = new AnimSpriteComponent(ship, animTextures,200, Rectangle::nullRect);
	ship->setPosition(Vector2{ 100,300 });*/

	/*vector<Texture*> bgTexsFar{
		&Assets::getTexture("farback01"),
		&Assets::getTexture("farback02")
	};
	Actor* bgFar = new Actor();
	BackgroundSpriteComponent* bgSpriteFar = new BackgroundSpriteComponent(bgFar, bgTexsFar);
	bgSpriteFar->setScrollSpeed(-100.0f);

	vector<Texture*> bgTexsClose{
		&Assets::getTexture("Stars"),
		&Assets::getTexture("Stars")
	};
	Actor* bgClose = new Actor();
	BackgroundSpriteComponent* bgSpriteClose = new BackgroundSpriteComponent(bgClose, bgTexsClose,150, Rectangle::nullRect);
	bgSpriteClose->setScrollSpeed(-200.0f);*/


}

void Game::unload() {

	while (!actors.empty()) {
		delete actors.back();
	}

	Assets::clear();
}