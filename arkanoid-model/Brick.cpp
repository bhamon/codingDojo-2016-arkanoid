#include "Brick.h"
#include "Position.h"

const float Brick::BRICK_WIDTH = 2;
const float Brick::BRICK_HEIGHT = 1;

Brick::Brick()
	: _position(0, 0)
	, _strength(0)
{
}

Brick::Brick(const Position& position, unsigned int strength)
	:_position(position)
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

bool Brick::isValid() const
{
	return _strength > 0;
}