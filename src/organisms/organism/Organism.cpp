#include "Organism.h"

#include <istream>
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

void Organism::serialize(std::ostream& os) const {
    int power = getPower();
    int initiative = getInitiative();
    int liveLength = getLiveLength();
    int powerToReproduce = getPowerToReproduce();
    char sign = getSign();
    std::string species = getSpecies();
    int x = getPosition().getX(), y = getPosition().getY();

    os.write((char*)&power, sizeof(int));
    os.write((char*)&initiative, sizeof(int));
    os.write((char*)&liveLength, sizeof(int));
    os.write((char*)&powerToReproduce, sizeof(int));
    os.write((char*)&sign, sizeof(char));

    int specSize = species.size();
    os.write((char*)&specSize, sizeof(int));
    os.write(species.data(), specSize);

    os.write((char*)&x, sizeof(int));
    os.write((char*)&y, sizeof(int));

    // Serializacja ancestors
    const auto& ancestors = getAncestors();
    int ancCount = ancestors.size();
    os.write((char*)&ancCount, sizeof(int));
    for (const auto& anc : ancestors) {
        int birth = anc.birthTurn;
        int death = anc.deathTurn;
        os.write((char*)&birth, sizeof(int));
        os.write((char*)&death, sizeof(int));
    }
}

void Organism::deserialize(std::istream& is) {
    int power, initiative, liveLength, powerToReproduce, x, y;
    char sign;
    int specSize;
    std::string species;

    is.read((char*)&power, sizeof(int));
    is.read((char*)&initiative, sizeof(int));
    is.read((char*)&liveLength, sizeof(int));
    is.read((char*)&powerToReproduce, sizeof(int));
    is.read((char*)&sign, sizeof(char));

    is.read((char*)&specSize, sizeof(int));
    species.resize(specSize);
    is.read(&species[0], specSize);

    is.read((char*)&x, sizeof(int));
    is.read((char*)&y, sizeof(int));

    setPower(power);
    setInitiative(initiative);
    setLiveLength(liveLength);
    setPowerToReproduce(powerToReproduce);
    setSign(sign);
    setSpecies(species);
    setPosition(Position(x, y));

    // Ancestors
    int ancCount;
    is.read((char*)&ancCount, sizeof(int));
    for (int i = 0; i < ancCount; ++i) {
        int birth, death;
        is.read((char*)&birth, sizeof(int));
        is.read((char*)&death, sizeof(int));
        addAncestor(birth, death);
    }
}