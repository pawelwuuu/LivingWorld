#include "PopulateWorld.h"
#include "organisms/plant/grass/Grass.h"
#include "organisms/animal/sheep/Sheep.h"
#include "wolf/Wolf.h"
#include "dandelion/Dandelion.h"
#include "toadstool/Toadstool.h"

#include <random>
#include <set>

void populateWorld(World& world,
                   int grassCount,
                   int sheepCount,
                   int wolfCount,
                   int dandelionCount,
                   int toadstoolCount)
{
    std::set<std::pair<int, int>> usedPositions;
    std::random_device rd;
    std::mt19937 gen(rd());
    std::uniform_int_distribution<> distX(0, world.getWorldX() - 1);
    std::uniform_int_distribution<> distY(0, world.getWorldY() - 1);

    auto getFreePosition = [&]() {
        while (true) {
            int x = distX(gen);
            int y = distY(gen);
            auto posPair = std::make_pair(x, y);
            if (usedPositions.find(posPair) == usedPositions.end()) {
                usedPositions.insert(posPair);
                return Position(x, y);
            }
        }
    };

    for (int i = 0; i < grassCount; ++i) {
        world.addOrganism(new Grass(getFreePosition()));
    }
    for (int i = 0; i < sheepCount; ++i) {
        world.addOrganism(new Sheep(getFreePosition()));
    }
    for (int i = 0; i < wolfCount; ++i) {
        world.addOrganism(new Wolf(getFreePosition()));
    }
    for (int i = 0; i < dandelionCount; ++i) {
        world.addOrganism(new Dandelion(getFreePosition()));
    }
    for (int i = 0; i < toadstoolCount; ++i) {
        world.addOrganism(new Toadstool(getFreePosition()));
    }
}
