#pragma once

#include "../organism/Organism.h"
#include "../../world/Position.h"
#include <vector>
#include <optional>

class Animal : public Organism {
protected:
    std::optional<Position> lastPosition;
    std::vector<char> food;

public:
    using Organism::Organism; // dziedziczenie konstruktorów

    Animal(); // domyślny konstruktor

    void setFood(std::vector<char> food);
    const std::vector<char>& getFood() const;

    void move(int dx, int dy);

    std::optional<Position> getLastPosition() const;

    void deserialize(std::istream& is) override;
    void serialize(std::ostream& os) const override;

    std::string toString() const override;
};
