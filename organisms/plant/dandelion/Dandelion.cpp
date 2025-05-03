#include "Dandelion.h"
#include "../../../world/World.h"

Dandelion::Dandelion(Position position)
    : Plant(0, position) // power = 0
{
    setInitiative(0);
    setLiveLength(6);
    setPowerToReproduce(2);
    setSign('D');
    setSpecies("D"); // species = "D"
}

Organism* Dandelion::cloneAt(Position position) const {
    return new Dandelion(position);
}
