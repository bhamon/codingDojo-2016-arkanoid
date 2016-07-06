#include "Racket.h"

const float Racket::WIDTH = 50.0f;
const float Racket::HEIGHT = 10.0f;

Racket::Racket(float position)
	: _position(position)
{
}

float
Racket::getPosition() const
{
	return _position;
}

void
Racket::setPosition(float position)
{
	_position = position;
}

float&
Racket::position()
{
	return _position;
}