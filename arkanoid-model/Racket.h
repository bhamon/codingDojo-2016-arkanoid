#ifndef RACKET_H
#define RACKET_H

#include "Point2.h"

class Racket
{
public:
	static const float WIDTH;
	static const float HEIGHT;
	static const float OFFSET;

private:
	math::Point2<float> _position;

public:
	Racket(const math::Point2<float>& position);

	const math::Point2<float>& getPosition() const;

	void setPosition(const math::Point2<float> &position);

	math::Point2<float>& position();

	float top() const;
	float bottom() const;
	float right() const;
	float left() const;
};

#endif