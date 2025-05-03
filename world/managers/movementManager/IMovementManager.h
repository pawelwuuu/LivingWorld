#pragma once
#include "../organisms/organism/Organism.h"

class World;

class IMovementManager {
public:
    virtual ~IMovementManager() = default;
    virtual bool tryMove(Organism* organism, World& world) = 0;
};
