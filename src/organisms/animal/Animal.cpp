#include "Animal.h"
#include <sstream>
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

void Animal::serialize(std::ostream& os) const {
    Organism::serialize(os);

    bool hasLast = lastPosition.has_value();
    os.write(reinterpret_cast<const char*>(&hasLast), sizeof(hasLast));
    if (hasLast) {
        int lx = lastPosition->getX();
        int ly = lastPosition->getY();
        os.write(reinterpret_cast<const char*>(&lx), sizeof(lx));
        os.write(reinterpret_cast<const char*>(&ly), sizeof(ly));
    }

    int foodCount = static_cast<int>(food.size());
    os.write(reinterpret_cast<const char*>(&foodCount), sizeof(foodCount));
    if (foodCount > 0) {
        os.write(reinterpret_cast<const char*>(food.data()), foodCount * sizeof(char));
    }
}

void Animal::deserialize(std::istream& is) {
    Organism::deserialize(is);

    bool hasLast;
    is.read(reinterpret_cast<char*>(&hasLast), sizeof(hasLast));
    if (hasLast) {
        int lx, ly;
        is.read(reinterpret_cast<char*>(&lx), sizeof(lx));
        is.read(reinterpret_cast<char*>(&ly), sizeof(ly));
        lastPosition = Position(lx, ly);
    } else {
        lastPosition = std::nullopt;
    }

    int foodCount;
    is.read(reinterpret_cast<char*>(&foodCount), sizeof(foodCount));
    food.clear();
    if (foodCount > 0) {
        food.resize(foodCount);
        is.read(reinterpret_cast<char*>(food.data()), foodCount * sizeof(char));
    }
}

std::string Animal::toString() const {
    std::ostringstream ss;
    ss << Organism::toString();

    ss << ", lastPosition=";
    if (lastPosition) {
        ss << "X:" << lastPosition->getX() << ", Y:" << lastPosition->getY();
    } else {
        ss << "none";
    }

    ss << ", food=[";
    for (size_t i = 0; i < food.size(); ++i) {
        ss << food[i];
        if (i + 1 < food.size()) ss << ',';
    }
    ss << ']';

    return ss.str();
}
