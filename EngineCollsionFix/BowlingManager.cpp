#include "BowlingManager.h"
#include "PinActor.h"
#include "BowlingBallActor.h"
#include "BowlingCameraComponent.h"
#include "BowlingManagerComponent.h"
#include "InputSystem.h"
#include "Log.h"
BowlingManager::BowlingManager()
{
	manager = new BowlingManagerComponent(this);
	camera = new BowlingCameraComponent(this);
	
	camera->setTarget(manager->getBall());
}

void BowlingManager::actorInput(const InputState& inputState)
{
	Vector2 mousePosition = inputState.mouse.getPosition();
	float x = mousePosition.x;
	float y = mousePosition.y;
	if (inputState.mouse.getButtonState(3) == ButtonState::Held)
	{
		const float maxMouseSpeed = 500.0f;
		const float maxOrbitSpeed = Maths::pi * 8;

		float yawSpeed = 0.0f;
		if (!Maths::nearZero(x))
		{
			yawSpeed = x / maxMouseSpeed;
			yawSpeed *= maxOrbitSpeed;
		}
		camera->setYawSpeed(yawSpeed);

		float pitchSpeed = 0.0f;
		if (!Maths::nearZero(y))
		{
			pitchSpeed = y / maxMouseSpeed;
			pitchSpeed *= maxOrbitSpeed;
		}
		camera->setPitchSpeed(pitchSpeed);
	}
	else if (inputState.mouse.getButtonState(3) == ButtonState::Released) {
		camera->setYawSpeed(0);
		camera->setPitchSpeed(0); 
	}

	if (inputState.keyboard.getKeyState(SDL_SCANCODE_SPACE) == ButtonState::Pressed) {
		manager->Interact();
		Log::info("HELLO");
	}
}

BowlingCameraComponent* BowlingManager::getCamera()
{
	return camera;
}

BowlingManagerComponent* BowlingManager::getManager()
{
	return manager;
}
