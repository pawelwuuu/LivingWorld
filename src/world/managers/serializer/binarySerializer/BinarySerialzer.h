#pragma once

#include <string>
#include "managers/serializer/WorldSerializer.h"

class World;

class BinaryWorldSerializer : public IWorldSerializer {
public:
    ~BinaryWorldSerializer() override = default;

    // Zapisuje stan całego obiektu World do pliku o podanej nazwie.
    void save(World& world, const std::string& fileName) override;

    // Wczytuje (deserializuje) stan świata z pliku i ustawia go w obiekcie world.
    void load(World& world, const std::string& fileName) override;
};
