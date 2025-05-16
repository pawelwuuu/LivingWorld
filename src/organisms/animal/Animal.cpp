#include "Animal.h"

#include <istream>

#include "../../world/World.h"

Animal::Animal() : Organism() {}

void Animal::setFood(std::vector<char> food) {
    this->food = std::move(food);
}

const std::vector<char>& Animal::getFood() const {
    return food;
}

void Animal::move(int dx, int dy) {
    lastPosition = getPosition(); // zapamiętaj poprzednią pozycję
    Organism::move(dx, dy);       // wykonaj ruch
}

std::optional<Position> Animal::getLastPosition() const {
    return lastPosition;
}