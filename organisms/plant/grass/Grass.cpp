#include "Grass.h"

Grass::Grass(Position position)
    : Plant(1, position) // power = 1, np.
{
    setSign('G');
    setSpecies("Grass");
    setInitiative(0);
    setLiveLength(999); // żyje bardzo długo
    setPowerToReproduce(2); // rozrasta się przy mocy 2+
}

Grass::Grass() : Grass(Position(0, 0)) {}

Organism* Grass::cloneAt(Position position) const {
    return new Grass(position);
}

