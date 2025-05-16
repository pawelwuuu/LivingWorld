#include "OrganismFactory.h"

OrganismFactory& OrganismFactory::getInstance() {
    static OrganismFactory instance;
    return instance;
}

void OrganismFactory::registerType(const std::string& typeId, CreatorFunc func) {
    registry[typeId] = func;
}

std::unique_ptr<Organism> OrganismFactory::create(const std::string& typeId) const {
    auto it = registry.find(typeId);
    if (it != registry.end()) {
        return it->second();
    }
    return nullptr;
}
