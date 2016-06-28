#ifndef FIELD_H
#define FIELD_H

#include "Brick.h"
#include <list>

class Field
{
	private:
	unsigned int _width;
	unsigned int _height;
	std::list<Brick> _brickList;

	public:
	Field(unsigned int width = 10, unsigned int height = 20);

	unsigned int getHeight() const;
	unsigned int getWidth() const;

	void setWidth(unsigned int width);
	void setHeight(unsigned int height);

	bool addBrick(const Brick& brick);
	Brick getBrick(const Position& position);

	unsigned int getBrickNumber() const;

};

#endif