#include "Racket.h"

const float Racket::WIDTH = 200.0f;
const float Racket::HEIGHT = 15.0f;
const float Racket::OFFSET = 10.0f;

Racket::Racket(const math::Point2<float>& position)
	: _position(position)
{
}

const math::Point2<float>& Racket::getPosition() const
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

float Racket::top() const
{
	return _position.getY() - (HEIGHT / 2.f);
}

float Racket::bottom() const
{
	return _position.getY() + (HEIGHT / 2.f);
}

float Racket::right() const
{
	return _position.getX() + (WIDTH / 2.f);
}

float Racket::left() const
{
	return _position.getX() - (WIDTH / 2.f);
}
