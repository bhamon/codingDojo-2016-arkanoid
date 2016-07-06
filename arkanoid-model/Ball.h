#ifndef BALL_H
#define BALL_H

#include "Point2.h"
#include "Vector2.h"

class Ball
{
	public:
	static const float RADIUS;

	private:
	math::Point2<float> _position;
	math::Vector2<float> _velocity;

	public:
	Ball(const math::Point2<float>& position, const math::Vector2<float> &velocity);
	Ball(const Ball& ball);
	~Ball();

	const math::Point2<float>& getPosition() const;
	const math::Vector2<float>& getVelocity() const;

	void setPosition(const math::Point2<float>& position);
	void setVelocity(const math::Vector2<float>& velocity);

	math::Point2<float>& position();
	math::Vector2<float>& velocity();
};


#endif