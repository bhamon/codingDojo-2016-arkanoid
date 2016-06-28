#ifndef BALL_H
#define BALL_H

#include "Position.h"
#include "Vector.h"

class Ball
{
	public:
	static const float RADIUS;

	private:
	Position _position;
	VectorF _vector;

	public:
	Ball(const Position& position, const VectorF &vector);
	virtual ~Ball();

	const Position& getPosition() const;
	const VectorF& getVector() const;

	void setPosition(const Position& position);
	void setVector(const VectorF& vector);
};


#endif