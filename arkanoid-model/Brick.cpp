#include "Brick.h"

const float Brick::WIDTH = 40.0f;
const float Brick::HEIGHT = 20.0f;

Brick::Brick(const math::Point2<float>& position, unsigned int strength)
	: _position(position)
	, _strength(strength)
{
}

Brick::Brick(const Brick& brick)
	: _position(brick._position)
	, _strength(brick._strength)
{
}

Brick::~Brick()
{
}

const math::Point2<float>&
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
Brick::setPosition(const math::Point2<float>& position)
{
	_position = position;
}

void
Brick::setStrength(unsigned int strength)
{
	_strength = strength;
}

math::Point2<float>&
Brick::position()
{
	return _position;
}

unsigned int&
Brick::strength()
{
	return _strength;
}

bool
Brick::isValid() const
{
	return _strength > 0;
}

bool
Brick::overlap(const Brick& brick) const
{
	return
		std::abs(_position.getX() - brick._position.getX()) < Brick::WIDTH &&
		std::abs(_position.getY() - brick._position.getY()) < Brick::HEIGHT;
}

bool
Brick::operator==(const Brick& brick) const
{
	return _position.getX() == brick.getPosition().getX() && 
		   _position.getY() == brick.getPosition().getY();
}