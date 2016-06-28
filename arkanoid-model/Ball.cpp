#include "Ball.h"

const float Ball::RADIUS = 2;

Ball::Ball(const Position& position, const VectorF& vector)
	: _position(position)
	, _vector(vector)
{
}

Ball::~Ball()
{
}

const Position&
Ball::getPosition() const
{
	return _position;
}

const VectorF&
Ball::getVector() const
{
	return _vector;
}

void Ball::setPosition(const Position& position)
{
	_position = position;
}

void
Ball::setVector(const VectorF& vector)
{
	_vector = vector;
}