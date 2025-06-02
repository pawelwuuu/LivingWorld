#include "Application.h"
#include "PopulateWorld.h"
#include <iostream>

Application::Application(int worldWidth, int worldHeight, int windowW, int windowH)
    : world(worldWidth, worldHeight,
            new DefaultMovementManager(),
            new DefaultInteractionManager()),
      renderer(world, windowW, windowH),
      running(true)
{
    // Rozmieść organizmy (przykładowe wartości można zmienić)
    populateWorld(world,
                  /*grassCount=*/2,
                  /*sheepCount=*/2,
                  /*wolfCount=*/2,
                  /*dandelionCount=*/2,
                  /*toadstoolCount=*/2);

}

Application::~Application() {
    // world i renderer zniszczą kursory
}

// Główna pętla aplikacji
void Application::run() {
    while (running) {
        handleEvents();
    }

    // Przed wyjściem zapiszemy i wczytamy stan świata:
    std::cout << "Zapisuję stan świata...\n";
    world.writeWorld("world.bin");
    std::cout << world.toString();

    std::cout << "Wczytuję stan świata...\n";
    world.readWorld("world.bin");
    std::cout << world.toString();
}

// Obsługa zdarzeń SDL
void Application::handleEvents() {
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
                }
                else if (event.key.keysym.sym == SDLK_ESCAPE) {
                    running = false;
                }
                break;

            case SDL_MOUSEBUTTONDOWN:
                if (event.button.button == SDL_BUTTON_LEFT) {
                    int mx = event.button.x;
                    int my = event.button.y;
                    int full = renderer.getCellSize() + renderer.getMargin();
                    int cellX = mx / full;
                    int cellY = my / full;
                    if (cellX >= 0 && cellX < world.getWorldX() &&
                        cellY >= 0 && cellY < world.getWorldY()) {
                        Organism* org = world.getOrganismAt({cellX, cellY});
                        if (org) {
                            std::string stats = org->toString();
                            std::cout << stats << std::endl;
                            SDL_ShowSimpleMessageBox(
                                SDL_MESSAGEBOX_INFORMATION,
                                "Statystyki organizmu",
                                stats.c_str(),
                                renderer.getWindow()
                            );
                        } else {
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
