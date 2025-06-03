#include "Application.h"
#include "PopulateWorld.h"
#include "managers/serializer/binarySerializer/BinarySerialzer.h"
#include <iostream>

Application::Application(int worldWidth, int worldHeight, int windowW, int windowH)
    : world(worldWidth, worldHeight,
            new DefaultMovementManager(),
            new DefaultInteractionManager(),
            new BinaryWorldSerializer()),
      renderer(world, windowW, windowH),
      running(true)
{
    populateWorld(world, 1, 3, 2, 1, 1);
}

Application::~Application() {}

void Application::run() {
    while (running) {
        handleEvents();
    }

    std::cout << "Zapisuję stan świata...\n";
    world.saveToFile("world.bin");
    std::cout << world.toString();

    std::cout << "Wczytuję stan świata...\n";
    world.loadFromFile("world.bin");
    std::cout << world.toString();
}

void Application::handleMouseClick(int button, int x, int y) {
    int full = renderer.getCellSize() + renderer.getMargin();
    int cellX = x / full;
    int cellY = y / full;

    if (cellX < 0 || cellX >= world.getWorldX() || cellY < 0 || cellY >= world.getWorldY())
        return;

    Organism* org = world.getOrganismAt({cellX, cellY});
    if (button == SDL_BUTTON_LEFT) {
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
            std::cout << "Brak organizmu w komórce (" << cellX << "," << cellY << ")\n";
        }
    } else if (button == SDL_BUTTON_RIGHT && org) {
        cout << org->toString() << " REMOVED" << endl;
        world.removeOrganism(org);
    }
}

void Application::handleEvents() {
    SDL_Event event;
    while (SDL_PollEvent(&event)) {
        switch (event.type) {
            case SDL_QUIT:
                running = false;
                break;

            case SDL_KEYDOWN:
                switch (event.key.keysym.sym) {
                    case SDLK_SPACE:
                        world.makeTurn();
                        renderer.render();
                        break;
                    case SDLK_ESCAPE:
                        running = false;
                        break;
                }
                break;

            case SDL_MOUSEBUTTONDOWN:
                handleMouseClick(event.button.button, event.button.x, event.button.y);
                break;

            default:
                break;
        }
    }
}
