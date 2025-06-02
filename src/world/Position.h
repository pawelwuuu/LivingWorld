#pragma once
#include <string>
#include <tuple>

using namespace std;

class Position {
private:
	int x;
	int y;

public:
	Position(int x, int y);
	Position() : x(0), y(0) {}

	int getX();
	void setX(int x);
	int getY();
	void setY(int y);

	int  getX() const;
	int  getY() const;

	string toString();

	bool operator==(const Position& other) const {
		return this->x == other.x && this->y == other.y;
	}

	bool operator<(const Position& other) const {
		return std::tie(x, y) < std::tie(other.x, other.y);
	}

	double distance(Position position);
	void move(int dx, int dy);
};
