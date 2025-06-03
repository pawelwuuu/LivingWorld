#pragma once
#include <string>

class Organism;

class AncestorHistory {
public:
    int birthTurn;
    mutable int deathTurn;
    Organism* organism;
    AncestorHistory(int birth, int death, Organism* organism) :
        birthTurn(birth), deathTurn(death), organism(organism) {}

    std::string toString() {
        return "AncestorHistory{birthTurn=" + std::to_string(birthTurn)
               + ", deathTurn=" + std::to_string(deathTurn) + "}";
    }
};
