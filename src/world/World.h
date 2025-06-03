#pragma once

#include <vector>
#include <memory>
#include <string>

#include "./managers/movementManager/IMovementManager.h"
#include "./managers/interactionManager/IInteractionManager.h"
#include "../organisms/organism/Organism.h"
#include "managers/serializer/WorldSerializer.h"

class Organism;
class Position;

class World {
private:
	int worldX;
	int worldY;
	int turn = 0;
	char separator = '.';

	std::vector<std::unique_ptr<Organism>> organisms;
	IWorldSerializer* serializer;

	bool isPositionFree(Position position);
public:
	// Konstruktor
	World(int worldX, int worldY, IMovementManager* movementManager, IInteractionManager* interactionManager, IWorldSerializer* serializer);

	// Gettery i settery
	int getWorldX() const;
	void setWorldX(int worldX);
	int getWorldY() const;
	void setWorldY(int worldY);
	int getTurn();
	void setTurn(int turn);
	bool isPositionOnWorld(int x, int y) const;

	// Zarządzanie organizmami
	void addOrganism(Organism* organism);
	void removeOrganism(Organism* organism);
	Organism* getOrganismAt(Position pos);
	bool containsOrganism(Organism* ptr) const;

	std::vector<Organism*> getAliveOrganisms() const;
	std::vector<std::unique_ptr<Organism>> newOrganismsBuffer;
	std::vector<std::unique_ptr<Organism>>& getOrganisms();
	void propagateDeathTurn(Organism* orgPtr);

	// Ruch i interakcje
	void makeTurn();
	std::vector<std::vector<Organism*>> getOverlappingOrganisms();

	// Pozycje
	std::vector<Position> getVectorOfAvailablePositionsAround(Position position);
	std::vector<Position> getPositionsAround(Position position) const;
	std::string getOrganismFromPosition(int x, int y);
	char** getOrganismsGrid();

	// IO
	void setSerializer(IWorldSerializer* serializer);
	void saveToFile(const std::string& fileName);
	void loadFromFile(const std::string& fileName);

	// Debug / wizualizacja
	std::string toString();

	// Menedżery
	std::unique_ptr<IMovementManager> movementManager;
	std::unique_ptr<IInteractionManager> interactionManager;
};
