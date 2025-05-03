#include "Organism.h"
#include <utility>

// === KONSTRUKTORY ===

Organism::Organism()
    : power(0), initiative(0), position(Position()), live_length(0),
      powerToReproduce(0), sign('O'), species("O") {}

Organism::Organism(int power, Position position)
    : power(power), initiative(0), position(position),
      live_length(0), powerToReproduce(0), sign('O'), species("O") {}

Organism::Organism(int power, int initiative, Position position, int live_length,
                   int powerToReproduce, char sign, std::string species)
    : power(power), initiative(initiative), position(position),
      live_length(live_length), powerToReproduce(powerToReproduce),
      sign(sign), species(std::move(species)) {}

Organism::Organism(const Organism& other)
    : power(other.power), initiative(other.initiative),
      position(other.position), live_length(other.live_length),
      powerToReproduce(other.powerToReproduce), sign(other.sign),
      species(other.species), ancestors(other.ancestors) {}

Organism::Organism(Organism&& other) noexcept
    : power(other.power), initiative(other.initiative),
      position(std::move(other.position)), live_length(other.live_length),
      powerToReproduce(other.powerToReproduce), sign(other.sign),
      species(std::move(other.species)), ancestors(std::move(other.ancestors)) {}

Organism::~Organism() = default;

// === OPERATORY ===

Organism& Organism::operator=(const Organism& other) {
    if (this != &other) {
        power = other.power;
        initiative = other.initiative;
        position = other.position;
        live_length = other.live_length;
        powerToReproduce = other.powerToReproduce;
        sign = other.sign;
        species = other.species;
        ancestors = other.ancestors;
    }
    return *this;
}

Organism& Organism::operator=(Organism&& other) noexcept {
    if (this != &other) {
        power = other.power;
        initiative = other.initiative;
        position = std::move(other.position);
        live_length = other.live_length;
        powerToReproduce = other.powerToReproduce;
        sign = other.sign;
        species = std::move(other.species);
        ancestors = std::move(other.ancestors);
    }
    return *this;
}

// === GETTERY i SETTERY ===

int Organism::getPower() const { return power; }
void Organism::setPower(int power) { this->power = power; }

int Organism::getInitiative() const { return initiative; }
void Organism::setInitiative(int initiative) { this->initiative = initiative; }

int Organism::getLiveLength() const { return live_length; }
void Organism::setLiveLength(int l) { live_length = l; }

int Organism::getPowerToReproduce() const { return powerToReproduce; }
void Organism::setPowerToReproduce(int p) { powerToReproduce = p; }

char Organism::getSign() const { return sign; }
void Organism::setSign(char s) { sign = s; }

Position Organism::getPosition() const { return position; }
void Organism::setPosition(Position position) { this->position = position; }

std::string Organism::getSpecies() const { return species; }
void Organism::setSpecies(const std::string& spec) { species = spec; }

std::string Organism::toString() const {
    return "{ species: " + getSpecies() +
           ", power: " + std::to_string(getPower()) +
           ", position: " + getPosition().toString() + " }";
}

// === FUNKCJE ===

void Organism::move(int dx, int dy) {
    position.move(dx, dy);
}

void Organism::addAncestor(int birthTurn, int deathTurn) {
    ancestors.emplace_back(birthTurn, deathTurn);
}

const std::vector<AncestorHistory>& Organism::getAncestors() const {
    return ancestors;
}
std::vector<AncestorHistory>& Organism::getAncestors() {
    return ancestors;
}
