#include "Plant.h"
#include <iostream>

Plant::Plant(int power, Position position)
	: Organism(power, position) {
	setSign('P');
	std::string s = "P";
	setSpecies(s);
}

Plant::Plant() : Plant(1, Position(0, 0)) {}

void Plant::move(int dx, int dy) {
	// Rośliny się nie poruszają
}
