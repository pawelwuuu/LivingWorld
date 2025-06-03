#pragma once

#include <SDL.h>
#include "world/World.h"
#include "managers/movementManager/DefaultMovementManager.h"
#include "managers/interactionManager/DefaultInteractionManager.h"
#include "gui/LifeGameRenderer.h"

class Application {
public:
    Application(int worldWidth = 10, int worldHeight = 10, int windowW = 800, int windowH = 700);
    ~Application();

    void run();

private:
    World world;
    LifeGameRenderer renderer;
    bool running = false;

    void handleEvents();
    void handleMouseClick(int button, int x, int y);
};
