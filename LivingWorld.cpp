#include <iostream>
#include <set>

#include "dandelion/Dandelion.h"
#include "managers/interactionManager/DefaultInteractionManager.h"
#include "managers/movementManager/DefaultMovementManager.h"
#include "world/Position.h"
#include "organisms/organism/Organism.h"
#include "organisms/plant/grass/Grass.h"
#include "world/World.h"
#include "organisms/animal/sheep/Sheep.h"
#include "toadstool/Toadstool.h"
#include "wolf/Wolf.h"

using namespace std;

void populateWorld(World& world, int grassCount, int sheepCount, int wolfCount, int dandelionCount, int toadstoolCount);

int main()
{
	World world(20, 20, new DefaultMovementManager(), new DefaultInteractionManager());

	// Automatyczne rozmieszczenie organizmów
	populateWorld(world,
		6,  // grass
		3,  // sheep
		2,  // wolf
		3,  // dandelion
		3   // toadstool
	);

	// Obserwujemy świat
	for (int i = 0; i < 20; ++i) {
		cout << "\nTura: " << world.getTurn() << endl;
		cout << world.toString();
		world.makeTurn();
	}

	// Zapis i przywracanie stanu
	// world.writeWorld("world.bin");
	// cout << "\nStan zapisany. Wczytujemy ponownie:\n";
	// world.readWorld("world.bin");
	// cout << world.toString();

	return 0;
}

void populateWorld(World& world, int grassCount, int sheepCount, int wolfCount, int dandelionCount, int toadstoolCount) {
	set<std::pair<int, int>> usedPositions;
	std::random_device rd;
	std::mt19937 gen(rd());
	std::uniform_int_distribution<> distX(0, world.getWorldX() - 1);
	std::uniform_int_distribution<> distY(0, world.getWorldY() - 1);

	auto getFreePosition = [&]() {
		while (true) {
			int x = distX(gen);
			int y = distY(gen);
			auto pos = std::make_pair(x, y);
			if (usedPositions.find(pos) == usedPositions.end()) {
				usedPositions.insert(pos);
				return Position(x, y);
			}
		}
	};

	for (int i = 0; i < grassCount; ++i)
		world.addOrganism(new Grass(getFreePosition()));
	for (int i = 0; i < sheepCount; ++i)
		world.addOrganism(new Sheep(getFreePosition()));
	for (int i = 0; i < wolfCount; ++i)
		world.addOrganism(new Wolf(getFreePosition()));
	for (int i = 0; i < dandelionCount; ++i)
		world.addOrganism(new Dandelion(getFreePosition()));
	for (int i = 0; i < toadstoolCount; ++i)
		world.addOrganism(new Toadstool(getFreePosition()));
}