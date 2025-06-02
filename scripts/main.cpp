#include <SDL.h>

int main(int argc, char* args []) {
    SDL_Init(SDL_INIT_VIDEO);

    SDL_Window* window = SDL_CreateWindow("Blank Window", SDL_WINDOWPOS_CENTERED, SDL_WINDOWPOS_CENTERED, 800, 600, SDL_WINDOW_SHOWN);
    if (window == nullptr) {
        SDL_Log("Failed to create window: %s", SDL_GetError());
        return 1;
    }

    SDL_Renderer* renderer = SDL_CreateRenderer(window, -1, SDL_RENDERER_ACCELERATED);
    if (renderer == nullptr) {
        SDL_Log("Failed to create renderer: %s", SDL_GetError());
        SDL_DestroyWindow(window);
        SDL_Quit();
        return 1;
    }

    bool running = true;
    SDL_Event event;

    while (running) {
        // Close window with any input
        while (SDL_PollEvent(&event)) {
            if (event.type == SDL_QUIT || event.type == SDL_KEYDOWN || event.type == SDL_MOUSEBUTTONDOWN) {
                running = false;
                break;
            }
        }

        SDL_SetRenderDrawColor(renderer, 100, 100, 180, 255); // Set the background color to purple
        SDL_RenderClear(renderer);
        SDL_RenderPresent(renderer);
    }

    SDL_DestroyRenderer(renderer);
    SDL_DestroyWindow(window);
    SDL_Quit();
    return 0;
}


//old main

// int main(int argc, char* argv[])
// {
// 	World world(5, 5, new DefaultMovementManager(), new DefaultInteractionManager());
//
// 	// Automatyczne rozmieszczenie organizmów
// 	populateWorld(world,
// 		2,  // grass
// 		1,  // sheep
// 		1,  // wolf
// 		2,  // dandelion
// 		2   // toadstool
// 	);
//
// 	// Obserwujemy świat
// 	for (int i = 0; i < 1; ++i) {
// 		cout << world.toString();
// 		world.makeTurn();
// 	}
//
// 	cout << world.toString();
// 	// Zapis i przywracanie stanu
// 	world.writeWorld("world.bin");
// 	cout << "\nStan zapisany. Wczytujemy ponownie:\n";
// 	world.readWorld("world.bin");
// 	cout << world.toString();
//
// 	return 0;
// }