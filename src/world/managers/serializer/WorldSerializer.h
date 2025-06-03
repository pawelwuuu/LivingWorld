// IWorldSerializer.h
#pragma once

#include <string>

class World;

class IWorldSerializer {
public:
    virtual ~IWorldSerializer() = default;

    virtual void save(World& world, const std::string& fileName) = 0;

    virtual void load(World& world, const std::string& fileName) = 0;
};
