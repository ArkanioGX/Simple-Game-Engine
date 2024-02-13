#pragma once
#include "KeyboardState.h"
#include "MouseState.h"
#include <SDL_events.h>

enum class ButtonState {
	None,
	Pressed,
	Released,
	Held
};

struct InputState
{
	KeyboardState keyboard;
	MouseState mouse;
};

class InputSystem {
public:
	InputSystem();

	bool initialize();
	void close();

	bool processEvent(SDL_Event& event);

	const InputState getInputState() const { return inputState; }

	void preUpdate();
	void update();

	bool getIsCursorDisplayed() const { return isCursorDisplayed; }
	void setMouseCursor(bool isCursorDisplayedP);
	void setMouseRelativeMode(bool isMouseRelativeOnP);

private:
	InputState inputState;
	bool isCursorDisplayed;
};

