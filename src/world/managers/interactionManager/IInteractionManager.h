#pragma once
#include "../organisms/organism/Organism.h"

class World;

class IInteractionManager {
public:
    virtual ~IInteractionManager() = default;

    virtual void consume(Organism* predator, Organism* target, World& world) = 0;
    virtual void reproduce(Organism* parent, World& world) = 0;
};
