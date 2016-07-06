#ifndef FIELD_H
#define FIELD_H

#include "Brick.h"
#include <list>

class Field
{
	private:
	float _width;
	float _height;
	std::list<Brick> _bricks;

	public:
	Field(float width, float height);

	float getWidth() const;
	float getHeight() const;

	bool addBrick(const Brick& brick);

	unsigned int getBrickNumber() const;

	bool canFitInside(const Brick& brick) const;

};

#endif