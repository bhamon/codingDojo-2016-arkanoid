#include "Racket.h"

const float Racket::WIDTH = 60.0f;
const float Racket::HEIGHT = 15.0f;
const float Racket::OFFSET = 10.0f;

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