#include <iostream>
#include <SDL.h>
#include "gui/Application.h"
#include "managers/movementManager/DefaultMovementManager.h"
#include "world/World.h"

using namespace std;

int main(int argc, char* argv[]) {
	if (SDL_Init(SDL_INIT_VIDEO)) {
		std::cerr << "SDL initialization failed: " << SDL_GetError() << std::endl;
		return 1;
	}

	Application app;
	app.run();

	SDL_Quit();
	return 0;
}