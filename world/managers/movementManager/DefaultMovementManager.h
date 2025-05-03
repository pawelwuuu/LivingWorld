#pragma once
#include "IMovementManager.h"
#include "../organisms/animal/Animal.h"
#include <algorithm>
#include <iostream>
#include <random>
#include "../world/World.h"

class DefaultMovementManager : public IMovementManager {
public:
    bool tryMove(Organism* organism, World& world) override {
        Animal* animal = dynamic_cast<Animal*>(organism);
        if (!animal) return false;

        std::vector<Position> edibleTargets;
        std::vector<Position> freeTargets;

        auto around = world.getPositionsAround(animal->getPosition());

        for (Position& pos : around) {
            if (!world.isPositionOnWorld(pos.getX(), pos.getY()))
                continue;

            Organism* other = world.getOrganismAt(pos);
            if (other == nullptr) {
                freeTargets.push_back(pos);
            } else {
                char otherName = other->getSign();
                const auto& foodList = animal->getFood();

                for (char food : foodList) {
                    if (food == otherName) {
                        edibleTargets.push_back(pos);
                        break;
                    }
                }
            }
        }

        std::vector<Position>* targetList = nullptr;

        if (!edibleTargets.empty()) {
            targetList = &edibleTargets;
        } else if (!freeTargets.empty()) {
            targetList = &freeTargets;
        } else {
            return false;
        }

        // 👇 Filtrowanie poprzedniej pozycji jeśli istnieje
        if (animal->getLastPosition().has_value()) {
            Position lastPos = animal->getLastPosition().value();

            // usuwamy lastPos z targetList
            auto& list = *targetList;
            list.erase(std::remove(list.begin(), list.end(), lastPos), list.end());

            // jeśli po usunięciu nie ma już nic — używamy oryginalnej listy (dozwolony powrót)
            if (list.empty()) {
                list = *targetList == edibleTargets ? edibleTargets : freeTargets;
            }
        }

        if (targetList->empty()) return false;

        Position chosen = (*targetList)[rand() % targetList->size()];
        animal->move(chosen.getX(), chosen.getY());
        return true;
    }
};
