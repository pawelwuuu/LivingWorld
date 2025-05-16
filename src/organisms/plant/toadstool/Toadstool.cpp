#include "Toadstool.h"
#include "../../../world/World.h"
#include "organismFactory/OrganismFactory.h"

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

std::string Toadstool::getTypeId() const {
    return "Toadstool";
}

namespace {
    struct ToadstoolRegistration {
        ToadstoolRegistration() {
            OrganismFactory::getInstance().registerType("Toadstool", []() {
                return std::make_unique<Toadstool>(Position(0, 0));
            });
        }
    };
    static ToadstoolRegistration reg;
}