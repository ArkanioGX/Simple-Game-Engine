#include <iostream>
#include <SDL.h>

using std::cout;
int main(int argc, char** argv)
{

	// Screen dimension constants
	const int SCREEN_WIDTH = 800;
	const int SCREEN_HEIGHT = 450;
	// Window pointer
	SDL_Window* window = nullptr;

	// Initialize SDL
	SDL_Init(SDL_INIT_VIDEO);
	// Create window
	window = SDL_CreateWindow("First Window", SDL_WINDOWPOS_CENTERED, SDL_WINDOWPOS_CENTERED,SCREEN_WIDTH, SCREEN_HEIGHT, SDL_WINDOW_SHOWN);
	// Wait two seconds
	SDL_Delay(2000);
	// Destroy window
	SDL_DestroyWindow(window);
	// Quit SDL
	SDL_Quit();
	return 0;
}