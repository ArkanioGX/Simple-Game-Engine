#pragma once
#include "Rectangle.h"
#include <SDL.h>
#include <SDL_image.h>
#include "Window.h"



class Renderer
{
public:
	Renderer();
	Renderer(const Renderer&) = delete;
	Renderer& operator=(const Renderer&) = delete;

	inline SDL_Renderer* toSDLRenderer() const { return SDLRenderer; }

	bool initialize(Window& window);
	void beginDraw();
	void drawRect(Rectangle& rect);
	void endDraw();
	void close();

private:
	SDL_Renderer* SDLRenderer = nullptr;
};

