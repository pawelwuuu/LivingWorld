#pragma once

#include "../plant/Plant.h"

class Grass : public Plant {
public:
    Grass(Position position);
    Grass();
    Organism* cloneAt(Position position) const override;

    std::string getTypeId() const override;
};
