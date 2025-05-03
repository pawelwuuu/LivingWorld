#pragma once

#include "../../plant/Plant.h"

class Toadstool : public Plant {
public:
    Toadstool(Position position);
    Organism* cloneAt(Position position) const override;
};
