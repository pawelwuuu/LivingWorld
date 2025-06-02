#include "LifeGameRenderer.h"
#include <map>

LifeGameRenderer::LifeGameRenderer(World& gameWorld, int width, int height) 
    : world(gameWorld), cellSize(30), margin(2) {
    window = SDL_CreateWindow("Symulacja Ekosystemu", 
                            SDL_WINDOWPOS_CENTERED, 
                            SDL_WINDOWPOS_CENTERED,
                            width, height, 
                            SDL_WINDOW_SHOWN);
    renderer = SDL_CreateRenderer(window, -1, SDL_RENDERER_ACCELERATED);
}

LifeGameRenderer::~LifeGameRenderer() {
    SDL_DestroyRenderer(renderer);
    SDL_DestroyWindow(window);
}

void LifeGameRenderer::render() {
    SDL_SetRenderDrawColor(renderer, 40, 40, 40, 255);
    SDL_RenderClear(renderer);

    // Mapa kolorów dla organizmów
    static const std::map<char, SDL_Color> colorMap = {
        {'G', {0, 255, 0, 255}},      // Grass
        {'S', {255, 255, 255, 255}},  // Sheep
        {'W', {255, 0, 0, 255}},      // Wolf
        {'D', {255, 255, 0, 255}},    // Dandelion
        {'T', {128, 0, 128, 255}}     // Toadstool
    };

    for (int y = 0; y < world.getWorldY(); ++y) {
        for (int x = 0; x < world.getWorldX(); ++x) {
            SDL_Rect cell = {
                x * (cellSize + margin),
                y * (cellSize + margin),
                cellSize,
                cellSize
            };

            std::string org = world.getOrganismFromPosition(x, y);
            char orgSymbol = org.empty() ? ' ' : org[0];

            SDL_SetRenderDrawColor(renderer, 70, 70, 70, 255);
            SDL_RenderFillRect(renderer, &cell);

            if (orgSymbol != ' ') {
                auto it = colorMap.find(orgSymbol);
                SDL_Color color = (it != colorMap.end()) ? it->second : SDL_Color{255, 165, 0, 255};
                SDL_SetRenderDrawColor(renderer, color.r, color.g, color.b, color.a);
                SDL_RenderFillRect(renderer, &cell);
            }
        }
    }
    
    SDL_RenderPresent(renderer);
}