#pragma once
#include <SDL.h>
#include "../world/World.h"

class LifeGameRenderer {
private:
    SDL_Window* window;
    SDL_Renderer* renderer;
    World& world;
    int cellSize;
    int margin;

public:
    LifeGameRenderer(World& gameWorld, int width = 800, int height = 600);
    ~LifeGameRenderer();
    void render();

    int getCellSize() const { return cellSize; }
    int getMargin()   const { return margin;   }
    SDL_Window* getWindow() const { return window; }
};