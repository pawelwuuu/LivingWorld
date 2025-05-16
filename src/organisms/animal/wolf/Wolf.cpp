#include "Wolf.h"
#include <iostream>
#include "../../../world/World.h"
#include "organismFactory/OrganismFactory.h"

Wolf::Wolf(Position position)
    : Animal(8, position) // power = 8
{
    setInitiative(5);
    setLiveLength(20);
    setPowerToReproduce(16);
    setSign('W');
    std::string species = "W";
    setSpecies(species);

    std::vector<char> food;
    food.push_back('S'); // zjada owce
    food.push_back('T'); // muhomor

    setFood(std::move(food));
}

Organism* Wolf::cloneAt(Position position) const {
    return new Wolf(position);
}

// rejestracja typu, serializacja

std::string Wolf::getTypeId() const {
    return "Wolf";
}

namespace {
    struct WolfRegistration {
        WolfRegistration() {
            OrganismFactory::getInstance().registerType("Wolf", []() {
                return std::make_unique<Wolf>(Position(0, 0));
            });
        }
    };

    static WolfRegistration reg;
}