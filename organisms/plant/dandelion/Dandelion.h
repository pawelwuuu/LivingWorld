#pragma once

#include "../../plant/Plant.h"

class Dandelion : public Plant {
public:
    Dandelion(Position position);
    Organism* cloneAt(Position position) const override;
};
