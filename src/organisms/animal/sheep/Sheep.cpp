#include "Sheep.h"
#include <iostream>
#include "../../../world/World.h"
#include "organismFactory/OrganismFactory.h"

Sheep::Sheep(Position position)
    : Animal(3, position) // power = 3
{
    setInitiative(3);
    setLiveLength(10);
    setPowerToReproduce(6);
    setSign('S');
    std::string species = "S";
    setSpecies(species);

    vector<char> food;
    food.push_back('G');
    food.push_back('D');
    food.push_back('T');

    setFood(std::move(food));
}

Organism* Sheep::cloneAt(Position position) const {
    return new Sheep(position);
}

// rejestracja typu, serializacja

std::string Sheep::getTypeId() const {
    return "Sheep";
}

namespace {
    struct SheepRegistration {
        SheepRegistration() {
            OrganismFactory::getInstance().registerType("Sheep", []() {
                return std::make_unique<Sheep>(Position(0, 0));  // domyślna pozycja, nadpisywana później
            });
        }
    };

    static SheepRegistration reg;
}