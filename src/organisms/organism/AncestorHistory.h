#pragma once
#include <string>

class Organism;

class AncestorHistory {
public:
    int birthTurn;
    mutable int deathTurn;
    Organism* parent;
    AncestorHistory(int birth, int death, Organism* self, Organism* parent) :
        birthTurn(birth), deathTurn(death), parent(parent) {}

    std::string toString() {
        return "AncestorHistory{birthTurn=" + std::to_string(birthTurn)
               + ", deathTurn=" + std::to_string(deathTurn) + "}";
    }
};
