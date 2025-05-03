#pragma once

#include "../../animal/Animal.h"

class Sheep : public Animal {
public:
    Sheep(Position position);
    Organism* cloneAt(Position position) const override;
};

