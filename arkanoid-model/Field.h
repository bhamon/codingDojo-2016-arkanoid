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
	void removeBrick(const Brick& brick);

	unsigned int getBrickNumber() const;

	bool canFitInside(const Brick& brick) const;

	const std::list<Brick>& getListBricks() const;

	std::list<Brick>::iterator begin();
	std::list<Brick>::iterator end();
	std::list<Brick>::const_iterator end() const;
	std::list<Brick>::const_iterator begin() const;

};

#endif