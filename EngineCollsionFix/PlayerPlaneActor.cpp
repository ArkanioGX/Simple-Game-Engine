#include "PlayerPlaneActor.h"
#include "MeshComponent.h"
#include "Assets.h"
#include "AudioComponent.h"
#include "AirplaneCameraComponent.h"
#include "MoveComponent.h"
#include "Game.h"
#include "TorpedoActor.h"
#include "Log.h"

PlayerPlaneActor::PlayerPlaneActor() {
	MeshComponent* mc = new MeshComponent(this);
	mc->setMesh(Assets::getMesh("Mesh_Airplane"));
	audio = new AudioComponent(this);
	cameraComponent = new AirplaneCameraComponent(this);
	moveComponent = new MoveComponent(this);

	moveComponent->setForwardSpeed(350);
}

void PlayerPlaneActor::actorInput(const InputState& inputState)
{
	float strafeSpeed = 0;
	if (inputState.keyboard.getKeyValue(SDL_SCANCODE_A))
	{
		strafeSpeed -= 500.0f;
	}
	if (inputState.keyboard.getKeyValue(SDL_SCANCODE_D))
	{
		strafeSpeed += 500.0f;
	}
	
	moveComponent->setStrafeSpeed(strafeSpeed);

	// Shoot
	if (inputState.mouse.getButtonState(1) == ButtonState::Pressed)
	{
		shoot();
	}
}

void PlayerPlaneActor::shoot()
{
	TorpedoActor* torp = new TorpedoActor();
	torp->setPosition(getPosition());
}

void PlayerPlaneActor::ding()
{
	audio->playEvent("event:/Ding");
}
