#include "Wolf.h"
#include <iostream>
#include "../../../world/World.h"

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
    food.push_back('D'); // jeśli masz np. dandelion = miniszek

    setFood(std::move(food));
}

Organism* Wolf::cloneAt(Position position) const {
    return new Wolf(position);
}
