#include "Game.h"
#include "Actor.h"
#include "SpriteComponent.h"
#include "AnimSpriteComponent.h"
#include "Timer.h"
#include "Assets.h"
#include "BackgroundSpriteComponent.h"
#include <iostream>
#include <algorithm>

bool Game::initialize() {
	bool isWindowInit = window.initialize();
	bool isRendererInit = renderer.initialize(window);

	int windowHeight = window.getHeight();
	int windowWidth = window.getWidth();

	topWall = { 0,0,static_cast<float>(windowWidth),wallThickness };
	bottomWall = { 0,windowHeight - wallThickness,static_cast<float>(windowWidth),wallThickness };
	rightWall = { windowWidth - wallThickness,0,wallThickness,static_cast<float>(windowHeight) };
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

	
	paddleDirection = keyboardState[SDL_SCANCODE_S] - keyboardState[SDL_SCANCODE_W];
}

void Game::update(float dt) {
	paddlePos += paddleVelocity * dt * paddleDirection;

	//Clamp Paddle Pos
	paddlePos.y = fmax((paddleHeight / 2 + wallThickness), fmin(paddlePos.y, (window.getHeight() - paddleHeight/2 - wallThickness)));

	//Ball move
	ballPos += ballVelocity * dt;

	if (ballPos.y < ballSize / 2 + wallThickness) {
		ballPos.y = ballSize / 2 + wallThickness;
		ballVelocity.y *= -1;
	}
	else if (ballPos.y > window.getHeight() - ballSize / 2 - wallThickness) {
		ballPos.y = window.getHeight() - ballSize / 2 - wallThickness;
		ballVelocity.y *= -1;
	}

	if (ballPos.x > window.getWidth() - ballSize / 2 - wallThickness) {
		ballPos.x = window.getWidth() - ballSize / 2 - wallThickness;
		ballVelocity.x *= -1;
	}

	//Ball Paddle collision
	Vector2 diff = ballPos - paddlePos;

	if (fabsf(diff.y) <= paddleHeight / 2 && fabsf(diff.x) <= paddleWidth / 2 + ballSize / 2 && ballVelocity.x < 0) {
		ballVelocity.x *= -1;
		ballPos.x = paddlePos.x + paddleWidth / 2 + ballSize / 2;
	}

	//Restart
	if (ballPos.x < 0) {
		ballVelocity.x *= -1;
		ballPos.x = window.getWidth() / 2.f;
	}

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

	renderer.drawRect(topWall);
	renderer.drawRect(rightWall);
	renderer.drawRect(bottomWall);

	Rectangle ballRect = { ballPos.x - ballSize / 2,ballPos.y - ballSize / 2,ballSize,ballSize };
	renderer.drawRect(ballRect);

	Rectangle paddleRect = { paddlePos.x - paddleWidth / 2, paddlePos.y - paddleHeight / 2,paddleWidth,paddleHeight };
	renderer.drawRect(paddleRect);

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
	Assets::loadTexture(renderer,"Res/Ship01.png","ship01");
	Assets::loadTexture(renderer, "Res/Ship02.png", "ship02");
	Assets::loadTexture(renderer, "Res/Ship03.png", "ship03");
	Assets::loadTexture(renderer, "Res/Ship04.png", "ship04");
	Assets::loadTexture(renderer, "Res/Farback01.png", "farback01");
	Assets::loadTexture(renderer, "Res/Farback02.png", "farback02");
	Assets::loadTexture(renderer, "Res/Stars.png", "Stars");

	Actor* actor = new Actor();
	SpriteComponent* sprite = new SpriteComponent(actor, Assets::getTexture("ship01"));
	actor->setPosition(Vector2{ 100,100 });

	vector<Texture*> animTextures{
		&Assets::getTexture("ship01"),
		&Assets::getTexture("ship02"),
		&Assets::getTexture("ship03"),
		&Assets::getTexture("ship04")
	};
	Actor* ship = new Actor();
	AnimSpriteComponent* animatedSprite = new AnimSpriteComponent(ship, animTextures,200, Rectangle::nullRect);
	ship->setPosition(Vector2{ 100,300 });

	vector<Texture*> bgTexsFar{
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
	bgSpriteClose->setScrollSpeed(-200.0f);


}

void Game::unload() {
	while (!actors.empty()) {
		delete actors.back();
	}

	Assets::clear();
}