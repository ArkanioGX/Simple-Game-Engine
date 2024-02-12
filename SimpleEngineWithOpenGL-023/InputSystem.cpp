#include "InputSystem.h"
#include <SDL_keyboard.h>
#include <cstring>

InputSystem::InputSystem() : inputState() {

}

bool InputSystem::initialize() {
	inputState.keyboard.currentState = SDL_GetKeyboardState(nullptr);
	memset(inputState.keyboard.previousState, 0, SDL_NUM_SCANCODES);

	return true;
}

void InputSystem::close() {

}

void InputSystem::preUpdate() {
	memcpy(inputState.keyboard.previousState, inputState.keyboard.currentState, SDL_NUM_SCANCODES);
}

void InputSystem::update() {

}