#pragma once
#include <string>
#include <unordered_map>
#include <functional>
#include <memory>
#include "../organisms/organism/Organism.h"

class OrganismFactory {
public:
    using CreatorFunc = std::function<std::unique_ptr<Organism>()>;

    static OrganismFactory& getInstance();

    void registerType(const std::string& typeId, CreatorFunc func);
    std::unique_ptr<Organism> create(const std::string& typeId) const;

private:
    std::unordered_map<std::string, CreatorFunc> registry;
};
