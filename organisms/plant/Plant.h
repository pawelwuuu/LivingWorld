#pragma once
#include "../organism/Organism.h"

class Plant : public Organism {
public:
	Plant(int power, Position position);
	Plant();

	void move(int dx, int dy) override;
};
