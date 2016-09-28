#include "Racket.h"

const float Racket::WIDTH = 200.0f;
const float Racket::HEIGHT = 15.0f;
const float Racket::OFFSET = 10.0f;

Racket::Racket(const math::Point2<float>& position)
	: _position(position)
{
}

math::Point2<float> Racket::getPosition() const
{
	return _position;
}

void Racket::setPosition(const math::Point2<float>& position)
{
	_position = position;
}

math::Point2<float>& Racket::position()
{
	return _position;
}