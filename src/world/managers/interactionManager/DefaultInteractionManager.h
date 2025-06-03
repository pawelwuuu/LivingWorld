#pragma once
#include <Sheep.h>

#include "IInteractionManager.h"
#include "../world/World.h"
#include "../organism/Organism.h"
#include <iostream>

class DefaultInteractionManager : public IInteractionManager {
public:
    void consume(Organism* predator, Organism* target, World& world) override {
        if (predator == nullptr || target == nullptr) return;
        if (!world.containsOrganism(predator) || !world.containsOrganism(target)) return;

        Animal* animalPredator = dynamic_cast<Animal*>(predator);
        if (!animalPredator) return;

        if (target->getSign() == 'T') {
            world.removeOrganism(target);
            world.removeOrganism(predator);
            cout << predator->getSign() << " id " << std::hash<Organism*>()(predator) << " on postion " << predator->getPosition().getX() << " " << predator->getPosition().getY() << " consumed T and died";
            return;
        }

        const auto& foodList = animalPredator->getFood();
        char targetSign = target->getSign();

        bool canEat = false;
        for (char food : foodList) {
            if (food == targetSign) {
                canEat = true;
                break;
            }
        }
        if (!canEat) return;

        world.removeOrganism(target);
        cout << predator->getSign() << " id " << std::hash<Organism*>()(predator) << " on postion " << predator->getPosition().getX() << " " << predator->getPosition().getY() << " consumed " << target->getSign() << endl;
    }

    void reproduce(Organism* parent, World& world) override {
        std::vector<Position> free = world.getVectorOfAvailablePositionsAround(parent->getPosition());
        if (free.empty()) return;

        Position childPos = free[rand() % free.size()];
        Organism* child = parent->cloneAt(childPos);

        // === ZAPISZ PRZODKÓW ===
        for (const auto& ancestor : parent->getAncestors()) {
            child->addAncestor(ancestor.birthTurn, ancestor.deathTurn, ancestor.organism);
        }
        child->addAncestor(world.getTurn(), -1, child);  // -1 = jeszcze nie umarł

        parent->getChildren().push_back(child);
        child->setPosition(childPos);
        parent->setPower(parent->getPower() / 2);
        world.newOrganismsBuffer.push_back(std::unique_ptr<Organism>(child));
    }

};
