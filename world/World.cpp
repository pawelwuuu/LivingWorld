#include "World.h"
#include <fstream>
#include <algorithm>
#include <iostream>
#include <map>
#include <memory>

// ==========================
// Konstruktory i pomocnicze
// ==========================

World::World(int worldX, int worldY, IMovementManager* movementManager, IInteractionManager* interactionManager)
    : worldX(worldX), worldY(worldY), movementManager(movementManager), interactionManager(interactionManager) {}

int World::getWorldX() const { return worldX; }
void World::setWorldX(int worldX) { this->worldX = worldX; }

int World::getWorldY() const { return worldY; }
void World::setWorldY(int worldY) { this->worldY = worldY; }

int World::getTurn() { return turn; }

bool World::isPositionOnWorld(int x, int y) const {
    return (x >= 0 && y >= 0 && x < getWorldX() && y < getWorldY());
}

// ==========================
// Obsługa organizmów i pozycji
// ==========================

void World::addOrganism(Organism* organism) {
    organisms.push_back(std::unique_ptr<Organism>(organism));
}

bool World::containsOrganism(Organism* ptr) const {
    for (const auto& org : organisms)
        if (org.get() == ptr)
            return true;
    return false;
}

Organism* World::getOrganismAt(Position pos) {
    for (const auto& org : organisms) {
        if (org->getPosition() == pos)
            return org.get();
    }
    return nullptr;
}

void World::removeOrganism(Organism* org) {
    auto it = std::find_if(organisms.begin(), organisms.end(),
        [org](const std::unique_ptr<Organism>& ptr) {
            return ptr.get() == org;
        });

    if (it != organisms.end()) {
        // Aktualizacja historii przed usunięciem
        auto& orgPtr = *it;
        auto& anc = orgPtr->getAncestors();
        if (!anc.empty() && anc.back().deathTurn == -1) {
            anc.back().deathTurn = getTurn();  // oznacz jako zmarły
        }

        organisms.erase(it);
    }
}


bool World::isPositionFree(Position position) {
    return getOrganismFromPosition(position.getX(), position.getY()).empty();
}

std::string World::getOrganismFromPosition(int x, int y) {
    for (const auto& org : organisms) {
        if (org->getPosition().getX() == x && org->getPosition().getY() == y)
            return std::string("") + org->getSign();
    }
    return "";
}

std::vector<Organism*> World::getAliveOrganisms() const {
    std::vector<Organism*> result;
    for (const auto& org : organisms)
        result.push_back(org.get());
    return result;
}

std::vector<Position> World::getVectorOfAvailablePositionsAround(Position position) {
    std::vector<Position> result;
    int pos_x = position.getX(), pos_y = position.getY();

    for (int x = -1; x <= 1; ++x)
        for (int y = -1; y <= 1; ++y)
            if ((x != 0 || y != 0) && isPositionOnWorld(pos_x + x, pos_y + y)) {
                Position newPos(pos_x + x, pos_y + y);
                if (isPositionFree(newPos)) {
                    result.push_back(newPos);
                }
            }

    return result;
}

std::vector<Position> World::getPositionsAround(Position position) const {
    std::vector<Position> result;
    int x = position.getX(), y = position.getY();

    for (int dx = -1; dx <= 1; ++dx) {
        for (int dy = -1; dy <= 1; ++dy) {
            if (dx == 0 && dy == 0) continue;
            Position newPos(x + dx, y + dy);
            if (isPositionOnWorld(newPos.getX(), newPos.getY())) {
                result.push_back(newPos);
            }
        }
    }
    return result;
}

// ==========================
// Logika tury
// ==========================

void World::makeTurn() {
    std::sort(organisms.begin(), organisms.end(),
              [](const std::unique_ptr<Organism>& a, const std::unique_ptr<Organism>& b) {
                  return a->getInitiative() > b->getInitiative();
              });

    // Ruch
    for (auto& org : organisms) {
        movementManager->tryMove(org.get(), *this);
    }

    // Rozmnażanie
    for (Organism* org : getAliveOrganisms()) {
        if (containsOrganism(org) && org->getPower() >= org->getPowerToReproduce()) {
            interactionManager->reproduce(org, *this);
        }
    }

    // Interakcje (zjadanie)
    auto overlappingGroups = getOverlappingOrganisms();
    for (auto& group : overlappingGroups) {
        for (size_t i = 0; i < group.size(); ++i) {
            for (size_t j = i + 1; j < group.size(); ++j) {
                Organism* a = group[i];
                Organism* b = group[j];

                interactionManager->consume(a, b, *this);
                if (containsOrganism(a) && containsOrganism(b)) {
                    interactionManager->consume(b, a, *this);
                }
            }
        }
    }

    // Wzrost siły i zmniejszenie zycia
    std::vector<Organism*> toRemove;

    for (auto& org : organisms) {
        org->setPower(org->getPower() + 1);
        org->setLiveLength(org->getLiveLength() - 1);

        if (org->getLiveLength() <= 0) {
            toRemove.push_back(org.get());
        }
    }

    // usuniecie martwych
    for (Organism* dying : toRemove) {
        std::cout << dying->getSign() << " died" << std::endl;
        removeOrganism(dying);
    }

    // Dodanie nowych organizmów z bufora
    for (auto& newOrg : newOrganismsBuffer) {
        organisms.push_back(std::move(newOrg));
    }
    newOrganismsBuffer.clear();

    ++turn;
}

// ==========================
// Zapis świata
// ==========================

void World::writeWorld(std::string fileName) {
    std::fstream my_file(fileName, std::ios::out | std::ios::binary);
    if (!my_file.is_open()) return;

    my_file.write((char*)&worldX, sizeof(int));
    my_file.write((char*)&worldY, sizeof(int));
    my_file.write((char*)&turn, sizeof(int));

    int orgs_size = organisms.size();
    my_file.write((char*)&orgs_size, sizeof(int));

    for (const auto& org : organisms) {
        int data = org->getPower();
        my_file.write((char*)&data, sizeof(int));

        data = org->getPosition().getX();
        my_file.write((char*)&data, sizeof(int));

        data = org->getPosition().getY();
        my_file.write((char*)&data, sizeof(int));

        std::string s_data = org->getSpecies();
        int s_size = s_data.size();
        my_file.write((char*)&s_size, sizeof(int));
        my_file.write(s_data.data(), s_size);
    }

    my_file.close();
}

// ==========================
// Grupowanie
// ==========================

std::vector<std::vector<Organism*>> World::getOverlappingOrganisms() {
    std::map<Position, std::vector<Organism*>> positionsMap;

    for (const auto& org : organisms) {
        positionsMap[org->getPosition()].push_back(org.get());
    }

    std::vector<std::vector<Organism*>> result;
    for (const auto& [pos, list] : positionsMap) {
        if (list.size() >= 2) {
            result.push_back(list);
        }
    }

    return result;
}

// ==========================
// Debug
// ==========================

std::string World::toString() {
    std::string result = "\nturn: " + std::to_string(getTurn()) + "\n";

    for (int wY = 0; wY < getWorldY(); ++wY) {
        for (int wX = 0; wX < getWorldX(); ++wX) {
            std::string spec = getOrganismFromPosition(wX, wY);
            result += spec.empty() ? std::string(1, separator) : spec;
        }
        result += "\n";
    }

    return result;
}

// ==========================
// Deserializacja (zakomentowana)
// ==========================

/*
void World::readWorld(std::string fileName) {
    std::fstream my_file(fileName, std::ios::in | std::ios::binary);
    if (!my_file.is_open()) return;

    int result;
    my_file.read((char*)&result, sizeof(int));
    worldX = result;

    my_file.read((char*)&result, sizeof(int));
    worldY = result;

    my_file.read((char*)&result, sizeof(int));
    turn = result;

    my_file.read((char*)&result, sizeof(int));
    int orgs_size = result;

    std::vector<std::unique_ptr<Organism>> new_organisms;

    for (int i = 0; i < orgs_size; i++) {
        int power;
        my_file.read((char*)&result, sizeof(int));
        power = result;

        int pos_x, pos_y;
        my_file.read((char*)&result, sizeof(int));
        pos_x = result;
        my_file.read((char*)&result, sizeof(int));
        pos_y = result;

        Position pos(pos_x, pos_y);

        int s_size;
        my_file.read((char*)&result, sizeof(int));
        s_size = result;

        std::string species;
        species.resize(s_size);
        my_file.read(&species[0], s_size);

        // UWAGA: nie można tworzyć instancji abstrakcyjnej klasy Organism
        // auto org = std::make_unique<Organism>(power, pos);
        // org->setSpecies(species);
        // new_organisms.push_back(std::move(org));
    }

    // organisms = std::move(new_organisms);
    my_file.close();
}
*/