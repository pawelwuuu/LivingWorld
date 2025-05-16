#pragma once

#include "../../animal/Animal.h"

class Wolf : public Animal {
public:
    Wolf(Position position);
    Organism* cloneAt(Position position) const override;

    std::string getTypeId() const override;
};
