#pragma once

class AncestorHistory {
public:
    int birthTurn;
    int deathTurn;
    AncestorHistory(int birth, int death) : birthTurn(birth), deathTurn(death) {}

    std::string toString();
};