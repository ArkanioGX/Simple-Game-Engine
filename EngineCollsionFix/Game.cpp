#include "Game.h"
#include "Actor.h"
#include "Timer.h"
#include "Assets.h"
#include "MeshComponent.h"
#include "CubeActor.h"
#include "SphereActor.h"
#include "PlaneActor.h"
#include "AudioComponent.h"
#include "FPSActor.h"
#include "FollowActor.h"
#include "OrbitActor.h"
#include "SplineActor.h"
#include "TargetActor.h"
#include "BowlingBallActor.h"
#include "PinActor.h"
#include "BowlingManager.h"
#include "ArrowIndicatorActor.h"
#include "BowlingManagerComponent.h"
#include <algorithm>
#include <algorithm>

bool Game::initialize()
{
	bool isWindowInit = window.initialize();
	bool isRendererInit = renderer.initialize(window);
	bool isAudioInit = audioSystem.initialize();
	bool isInputInit = inputSystem.initialize();

	return isWindowInit && isRendererInit && isAudioInit && isInputInit; // Return bool && bool && bool ...to detect error
}

void Game::load()
{
	inputSystem.setMouseRelativeMode(true);

	Assets::loadShader("Res\\Shaders\\Sprite.vert", "Res\\Shaders\\Sprite.frag", "", "", "", "Sprite");
	Assets::loadShader("Res\\Shaders\\Phong.vert", "Res\\Shaders\\Phong.frag", "", "", "", "Phong");
	Assets::loadShader("Res\\Shaders\\BasicMesh.vert", "Res\\Shaders\\BasicMesh.frag", "", "", "", "BasicMesh");

	Assets::loadTexture(renderer, "Res\\Textures\\Default.png", "Default");
	Assets::loadTexture(renderer, "Res\\Textures\\Cube.png", "Cube");
	Assets::loadTexture(renderer, "Res\\Textures\\Plane.png", "Plane");
	Assets::loadTexture(renderer, "Res\\Textures\\Sphere.png", "Sphere");
	Assets::loadTexture(renderer, "Res\\Textures\\Pin.png", "Pin");
	Assets::loadTexture(renderer, "Res\\Textures\\Planks.png", "Planks");
	Assets::loadTexture(renderer, "Res\\Textures\\Side.png", "Side");
	Assets::loadTexture(renderer, "Res\\Textures\\Arrow.png", "Arrow");

	Assets::loadMesh("Res\\Meshes\\Cube.gpmesh", "Mesh_Cube");
	Assets::loadMesh("Res\\Meshes\\Plane.gpmesh", "Mesh_Plane");
	Assets::loadMesh("Res\\Meshes\\Sphere.gpmesh", "Mesh_Sphere");
	Assets::loadMesh("Res\\Meshes\\Pin.gpmesh", "Mesh_Pin");
	Assets::loadMesh("Res\\Meshes\\Arrow.gpmesh", "Mesh_Arrow");

	BowlingManager* bm = new BowlingManager();

	Quaternion q(Vector3::unitY, -Maths::piOver2);
	q = Quaternion::concatenate(q, Quaternion(Vector3::unitZ, Maths::pi + Maths::pi / 4.0f));

	bm->getManager()->placePins();
	 /*
	//Pins Placement
	Vector3 basePos = Vector3(-100, 100, -100);
	float nRange = 4;
	float size = 200;
	for (int n = nRange; n > 0; n--) {
		for (int i = 0; i < n; i++) {
			PinActor* pin = new PinActor();
			Vector3 pos = Vector3::zero;

			pos.x = (size / (n + 1)) * (i + 1);
			pos.y = (size / nRange) * -n;

			pos += basePos;

			pin->setPosition(pos);

			pin->setScale(100.0f);
			//pin->setRotation(Quaternion(Vector3::unitX, Maths::piOver2));

			//pinsPlaced.emplace_back(pin);
		}
	}*/



	// Floor and walls

	// Setup floor
	const float start = -50;
	const float size = 100.0f;
	for (int i = 0; i < 2; i++)
	{
		for (int j = 0; j < 9; j++)
		{
			PlaneActor* p = new PlaneActor();
			p->setPosition(Vector3(start + i * size, start + j * size, -100.0f));

			if (j == 8) {
				p = new PlaneActor();
				p->setPosition(Vector3(start + i * size , start + j * size + 50, -150.0f));
				p->setRotation(Quaternion(Vector3::unitX, Maths::piOver2));
			}
		}
	}

	//Left Side Wall
	for (int j = 0; j < 9; j++)
	{
		CubeActor* c = new CubeActor();
		c->setPosition(Vector3(-150, start + j * size, -100.0f));
		c->setScale(100.0f);

		c = new CubeActor();
		c->setPosition(Vector3(150, start + j * size, -100.0f));
		c->setScale(100.0f);
	}

	// Setup lights
	renderer.setAmbientLight(Vector3(0.3f, 0.3f, 0.2f));
	DirectionalLight& dir = renderer.getDirectionalLight();
	dir.direction = Vector3(0.0f, -0.707f, -0.707f);
	dir.diffuseColor = Vector3(0.78f, 0.88f, 1.0f);
	dir.specColor = Vector3(0.8f, 0.8f, 0.8f);

	// Create spheres with audio components playing different sounds
	SphereActor* soundSphere = new SphereActor();
	soundSphere->setPosition(Vector3(500.0f, -75.0f, 0.0f));
	soundSphere->setScale(1.0f);
	AudioComponent* ac = new AudioComponent(soundSphere);
	ac->playEvent("event:/FireLoop");
	// Start music
	musicEvent = audioSystem.playEvent("event:/Music");
}

void Game::processInput()
{
	inputSystem.preUpdate();

	// SDL Event
	SDL_Event event;
	while (SDL_PollEvent(&event))
	{
		isRunning = inputSystem.processEvent(event);
	}

	inputSystem.update();
	const InputState& input = inputSystem.getInputState();

	// Escape: quit game
	if (input.keyboard.getKeyState(SDL_SCANCODE_ESCAPE) == ButtonState::Released)
	{
		isRunning = false;
	}

	// Actor input
	isUpdatingActors = true;
	for (auto actor : actors)
	{
		actor->processInput(input);
	}
	isUpdatingActors = false;
}

void Game::update(float dt)
{
	// Update audio
	audioSystem.update(dt);

	// Update actors 
	isUpdatingActors = true;
	for(auto actor: actors) 
	{
		actor->update(dt);
	}
	isUpdatingActors = false;

	// Move pending actors to actors
	for (auto pendingActor: pendingActors)
	{
		pendingActor->computeWorldTransform();
		actors.emplace_back(pendingActor);
	}
	pendingActors.clear();

	// Delete dead actors
	vector<Actor*> deadActors;
	for (auto actor : actors)
	{
		if (actor->getState() == Actor::ActorState::Dead)
		{
			deadActors.emplace_back(actor);
		}
	}
	for (auto deadActor : deadActors)
	{
		delete deadActor;
	}
}

void Game::render()
{
	renderer.beginDraw();
	renderer.draw();
	renderer.endDraw();
}

void Game::loop()
{
	Timer timer;
	float dt = 0;
	while (isRunning)
	{
		float dt = timer.computeDeltaTime() / 1000.0f;
		processInput();
		update(dt);
		render();
		timer.delayTime();
	}
}

void Game::unload()
{
	// Delete actors
	// Because ~Actor calls RemoveActor, have to use a different style loop
	while (!actors.empty())
	{
		delete actors.back();
	}

	// Resources
	Assets::clear();
}

void Game::close()
{
	inputSystem.close();
	renderer.close();
	audioSystem.close();
	window.close();
	SDL_Quit();
}

void Game::addActor(Actor* actor)
{
	if (isUpdatingActors)
	{
		pendingActors.emplace_back(actor);
	}
	else
	{
		actors.emplace_back(actor);
	}
}

void Game::removeActor(Actor* actor)
{
	// Erase actor from the two vectors
	auto iter = std::find(begin(pendingActors), end(pendingActors), actor);
	if (iter != end(pendingActors))
	{
		// Swap to end of vector and pop off (avoid erase copies)
		std::iter_swap(iter, end(pendingActors) - 1);
		pendingActors.pop_back();
	}
	iter = std::find(begin(actors), end(actors), actor);
	if (iter != end(actors))
	{
		std::iter_swap(iter, end(actors) - 1);
		actors.pop_back();
	}
}

void Game::addPlane(PlaneActor* plane)
{
	planes.emplace_back(plane);
}

void Game::removePlane(PlaneActor* plane)
{
	auto iter = std::find(begin(planes), end(planes), plane);
	planes.erase(iter);
}
