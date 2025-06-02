#pragma once
#include <string>

class AncestorHistory {
public:
    int birthTurn;
    int deathTurn;
    AncestorHistory(int birth, int death) : birthTurn(birth), deathTurn(death) {}

    std::string toString() {
        return "AncestorHistory{birthTurn=" + std::to_string(birthTurn)
               + ", deathTurn=" + std::to_string(deathTurn) + "}";
    }
};
