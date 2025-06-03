// BinaryWorldSerializer.cpp

#include "BinarySerialzer.h"

#include "World.h"
#include "organismFactory/OrganismFactory.h"

#include <fstream>
#include <iostream>

void BinaryWorldSerializer::save(World& world, const std::string& fileName) {
    std::ofstream file(fileName, std::ios::out | std::ios::binary);
    if (!file.is_open()) {
        std::cerr << "Nie można otworzyć pliku do zapisu: " << fileName << std::endl;
        return;
    }

    // Zapisujemy wymiary i numer tury
    int worldX = world.getWorldX();
    int worldY = world.getWorldY();
    int turn   = world.getTurn();
    file.write(reinterpret_cast<const char*>(&worldX), sizeof(int));
    file.write(reinterpret_cast<const char*>(&worldY), sizeof(int));
    file.write(reinterpret_cast<const char*>(&turn),   sizeof(int));

    // Zapisujemy liczbę organizmów
    int orgCount = static_cast<int>(world.getAliveOrganisms().size());
    file.write(reinterpret_cast<const char*>(&orgCount), sizeof(int));

    // Dla każdego organizmu najpierw zapisujemy jego typeId, a potem wywołujemy serialize()
    for (Organism* org : world.getAliveOrganisms()) {
        std::string typeId = org->getTypeId();
        int typeSize = static_cast<int>(typeId.size());
        file.write(reinterpret_cast<const char*>(&typeSize), sizeof(int));
        file.write(typeId.c_str(), typeSize);

        // Każdy organizm sam zapisuje swoje pola we własnej metodzie
        org->serialize(file);
    }

    file.close();
}

void BinaryWorldSerializer::load(World& world, const std::string& fileName) {
    std::ifstream file(fileName, std::ios::in | std::ios::binary);
    if (!file.is_open()) {
        std::cerr << "Nie można otworzyć pliku do odczytu: " << fileName << std::endl;
        return;
    }

    // Odczytujemy wymiary i numer tury
    int worldX, worldY, turn;
    file.read(reinterpret_cast<char*>(&worldX), sizeof(int));
    file.read(reinterpret_cast<char*>(&worldY), sizeof(int));
    file.read(reinterpret_cast<char*>(&turn),   sizeof(int));

    // Ustawiamy odczytane wartości w obiekcie world
    world.setWorldX(worldX);
    world.setWorldY(worldY);
    world.setTurn(turn);

    // Odczytujemy liczbę organizmów
    int orgCount;
    file.read(reinterpret_cast<char*>(&orgCount), sizeof(int));

    // Czyścimy bieżącą listę organizmów w świecie
    world.getOrganisms().clear();

    // Dla każdego rekordu: odczytujemy typeId, tworzymy organizm z fabryki i delegujemy deserialize
    for (int i = 0; i < orgCount; ++i) {
        int typeSize;
        file.read(reinterpret_cast<char*>(&typeSize), sizeof(int));

        std::string typeId(typeSize, ' ');
        file.read(&typeId[0], typeSize);

        // Fabryka tworzy nowy Organism* o odpowiednim typie
        std::unique_ptr<Organism> orgPtr{ OrganismFactory::getInstance().create(typeId) };
        if (!orgPtr) {
            std::cerr << "Nieznany typ organizmu (podczas load): " << typeId << std::endl;
            continue;
        }

        // Każdy organizm odczytuje swoje pola we własnej metodzie
        orgPtr->deserialize(file);

        // Dodajemy do świata (transfer własności)
        world.addOrganism(orgPtr.release());
    }

    file.close();
}
