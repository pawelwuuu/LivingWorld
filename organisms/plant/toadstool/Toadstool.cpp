#include "Toadstool.h"
#include "../../../world/World.h"

Toadstool::Toadstool(Position position)
    : Plant(0, position) // power = 0
{
    setInitiative(0);
    setLiveLength(12);
    setPowerToReproduce(4);
    setSign('T');
    setSpecies("T");
}

Organism* Toadstool::cloneAt(Position position) const {
    return new Toadstool(position);
}
