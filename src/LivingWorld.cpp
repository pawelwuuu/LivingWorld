#include <iostream>
#include <SDL.h>
#include <set>
#include <gui/LifeGameRenderer.h>

#include "dandelion/Dandelion.h"
#include "managers/interactionManager/DefaultInteractionManager.h"
#include "managers/movementManager/DefaultMovementManager.h"
#include "world/Position.h"
#include "organisms/organism/Organism.h"
#include "organisms/plant/grass/Grass.h"
#include "world/World.h"
#include "organisms/animal/sheep/Sheep.h"
#include "toadstool/Toadstool.h"
#include "wolf/Wolf.h"

using namespace std;

void populateWorld(World& world, int grassCount, int sheepCount, int wolfCount, int dandelionCount, int toadstoolCount);

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

int main(int argc, char* argv[]) {
	// Inicjalizacja SDL
	if (SDL_Init(SDL_INIT_VIDEO)) {
		std::cerr << "SDL initialization failed: " << SDL_GetError() << std::endl;
		return 1;
	}

	World world(5, 5, new DefaultMovementManager(), new DefaultInteractionManager());

	populateWorld(world, 1, 2, 1, 1, 1);

	LifeGameRenderer renderer(world, 800, 700);

	bool running = true;
	while (running) {
		SDL_Event event;

		while (SDL_PollEvent(&event)) {
			switch (event.type) {
				case SDL_QUIT:
					running = false;
				break;

				case SDL_KEYDOWN:
					if (event.key.keysym.sym == SDLK_SPACE) {
						world.makeTurn();
						renderer.render();
					} else if (event.key.keysym.sym == SDLK_ESCAPE) {
						running = false;
					}
				break;

				case SDL_MOUSEBUTTONDOWN:
					if (event.button.button == SDL_BUTTON_LEFT) {
						// 1) Z jakichś LifeGameRenderer: cellSize, margin, window, world
						int mx = event.button.x;
						int my = event.button.y;
						int full = renderer.getCellSize() + renderer.getMargin();

						int cellX = mx / full;
						int cellY = my / full;
						// 2) Sprawdź, czy w granicach świata:
						if (cellX >= 0 && cellX < world.getWorldX() &&
							cellY >= 0 && cellY < world.getWorldY()) {
							// 3) Pobierz organizm (zakładam, że masz wskaźnik albo nullptr):
							Organism* org = world.getOrganismAt(Position(cellX, cellY));
							if (org) {
								// A) wypisz do konsoli
								std::cout << org->toString() << std::endl;

								// B) albo pokaż okienko SDL:
								std::string stats = org->toString();
								SDL_ShowSimpleMessageBox(
								  SDL_MESSAGEBOX_INFORMATION,
								  "Statystyki organizmu",
								  stats.c_str(),
								  renderer.getWindow()
								);
							}
							else {
								std::cout << "Brak organizmu w komórce ("
										  << cellX << "," << cellY << ")\n";
							}
							}
					}
				break;

				default:
					break;
			}
		}
	}

	// Zapis stanu na koniec
	world.writeWorld("world.bin");
	cout << world.toString();

	world.readWorld("world.bin");
	cout << world.toString();

	return 0;
}

void populateWorld(World& world, int grassCount, int sheepCount, int wolfCount, int dandelionCount, int toadstoolCount) {
	set<std::pair<int, int>> usedPositions;
	std::random_device rd;
	std::mt19937 gen(rd());
	std::uniform_int_distribution<> distX(0, world.getWorldX() - 1);
	std::uniform_int_distribution<> distY(0, world.getWorldY() - 1);

	auto getFreePosition = [&]() {
		while (true) {
			int x = distX(gen);
			int y = distY(gen);
			auto pos = std::make_pair(x, y);
			if (usedPositions.find(pos) == usedPositions.end()) {
				usedPositions.insert(pos);
				return Position(x, y);
			}
		}
	};

	for (int i = 0; i < grassCount; ++i)
		world.addOrganism(new Grass(getFreePosition()));
	for (int i = 0; i < sheepCount; ++i)
		world.addOrganism(new Sheep(getFreePosition()));
	for (int i = 0; i < wolfCount; ++i)
		world.addOrganism(new Wolf(getFreePosition()));
	for (int i = 0; i < dandelionCount; ++i)
		world.addOrganism(new Dandelion(getFreePosition()));
	for (int i = 0; i < toadstoolCount; ++i)
		world.addOrganism(new Toadstool(getFreePosition()));
}