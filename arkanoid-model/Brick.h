#ifndef BRICK_H
#define BRICK_H

#include "Point2.h"

class Brick
{
public:
	static const float WIDTH;
	static const float HEIGHT;

private:
	math::Point2<float> _position;
	unsigned int _strength;

public:
	Brick(const math::Point2<float>& position, unsigned int strength);
	Brick(const Brick& brick);
	~Brick();

	const math::Point2<float>& getPosition() const;
	unsigned int getStrength() const;

	void setPosition(const math::Point2<float>& position);
	float top() const;
	float bottom() const;
	float right() const;
	float left() const;

	void setStrength(unsigned int strength);

	math::Point2<float>& position();
	unsigned int& strength();

	bool isValid() const;
	bool overlap(const Brick& brick) const;

	bool operator==(const Brick& brick) const;
};

#endif