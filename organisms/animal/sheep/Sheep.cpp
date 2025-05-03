#include "Sheep.h"
#include <iostream>
#include "../../../world/World.h"

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

    setFood(std::move(food));
}

Organism* Sheep::cloneAt(Position position) const {
    return new Sheep(position);
}




