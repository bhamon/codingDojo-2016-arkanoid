#include "Brick.h"
#include "Position.h"

Brick::Brick(const Position& position, unsigned int strength)
	: _position(position)
	, _strength(strength)
{
}

Brick::Brick(const Brick& brick)
	:_position(brick._position)
	, _strength(brick._strength)
{
}

const Position&
Brick::getPosition() const
{
	return _position;
}

unsigned int
Brick::getStrength() const
{
	return _strength;
}

void
Brick::setPosition(const Position& position)
{
	_position = position;
}

void
Brick::setStrength(unsigned int strength)
{
	_strength = strength;
}