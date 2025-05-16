#pragma once

#include <string>
#include <vector>
#include "../../world/Position.h"
#include "AncestorHistory.h"

class Organism {
protected:
	int power;
	int initiative;
	Position position;
	int live_length;
	int powerToReproduce;
	char sign;
	std::string species;
	std::vector<AncestorHistory> ancestors;

public:
	// Konstruktory
	Organism();
	Organism(int power, Position position);
	Organism(int power, int initiative, Position position, int live_length,
			 int powerToReproduce, char sign, std::string species);

	Organism(const Organism& other);
	Organism(Organism&& other) noexcept;
	virtual ~Organism();

	// Operatory przypisania
	Organism& operator=(const Organism& other);
	Organism& operator=(Organism&& other) noexcept;

	// Gettery i settery
	int getPower() const;
	void setPower(int power);

	int getInitiative() const;
	void setInitiative(int initiative);

	int getLiveLength() const;
	void setLiveLength(int);

	int getPowerToReproduce() const;
	void setPowerToReproduce(int);

	char getSign() const;
	void setSign(char);

	Position getPosition() const;
	void setPosition(Position position);

	std::string getSpecies() const;
	void setSpecies(const std::string& spec);

	std::string toString() const;

	// Ruch i klonowanie
	virtual void move(int dx, int dy);
	virtual Organism* cloneAt(Position position) const = 0;

	// Historia przodków
	void addAncestor(int birthTurn, int deathTurn);
	std::vector<AncestorHistory>& getAncestors();
	const std::vector<AncestorHistory>& getAncestors() const;

	// serializacja
	virtual void serialize(std::ostream& os) const;
	virtual void deserialize(std::istream& is);
	virtual std::string getTypeId() const = 0;
};
