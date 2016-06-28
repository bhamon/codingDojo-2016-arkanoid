#ifndef BRICK_H
#define BRICK_H

#include "Position.h"
#include "Ball.h"

class Brick
{
	public:
	static const float BRICK_WIDTH;
	static const float BRICK_HEIGHT;

	private:
	Position _position;
	unsigned int _strength;

	public:
	Brick();
	Brick(const Position& position, unsigned int strength);
	Brick(const Brick& brick);

	const Position& getPosition() const;
	unsigned int getStrength() const;

	void setPosition(const Position& position);
	void setStrength(unsigned int strength);

	bool isValid() const;
};

#endif