#ifndef BRICK_H
#define BRICK_H

#include "Position.h"

class Brick
{
	private:
	Position _position;
	unsigned int _strength;

	public:
	Brick(const Position& position, unsigned int strength);
	Brick(const Brick& brick);

	const Position& getPosition() const;
	unsigned int getStrength() const;

	void setPosition(const Position& position);
	void setStrength(unsigned int strength);
};

#endif