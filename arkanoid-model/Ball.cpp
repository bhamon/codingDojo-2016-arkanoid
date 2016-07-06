#include "Ball.h"

const float Ball::RADIUS = 10.0f;

Ball::Ball(const math::Point2<float>& position, const math::Vector2<float>& velocity)
	: _position(position)
	, _velocity(velocity)
{
}

Ball::Ball(const Ball& ball)
	: _position(ball._position)
	, _velocity(ball._velocity)
{
}

Ball::~Ball()
{
}

const math::Point2<float>&
Ball::getPosition() const
{
	return _position;
}

const math::Vector2<float>&
Ball::getVelocity() const
{
	return _velocity;
}

void Ball::setPosition(const math::Point2<float>& position)
{
	_position = position;
}

void
Ball::setVelocity(const math::Vector2<float>& velocity)
{
	_velocity = velocity;
}

math::Point2<float>&
Ball::position()
{
	return _position;
}

math::Vector2<float>&
Ball::velocity()
{
	return _velocity;
}