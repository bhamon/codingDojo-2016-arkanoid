#include "Brick.h"
#include "Field.h"

Field::Field(unsigned int width, unsigned int height)
	:_width(width),
	 _height(height),
	 _brickList()
{
}

unsigned int Field::getHeight() const
{
	return _height;
}

unsigned int Field::getWidth() const
{
	return _width;
}

void Field::setWidth(unsigned int width)
{
	_width = width;
}

void Field::setHeight(unsigned int height)
{
	_height = height;
}

bool Field::addBrick(const Brick& brick)
{
	bool hasBeenAdded = true;

	if(brick.getPosition().getX() >= 0
		&& brick.getPosition().getX() < _width
		&& brick.getPosition().getY() >= 0
		&& brick.getPosition().getY() < _height
		&& brick.isValid())
	{
		if(getBrick(brick.getPosition()).isValid() == false)
		{
			_brickList.push_front(brick);
		}
		else
		{
			hasBeenAdded = false;
		}
	}
	else
	{
		hasBeenAdded = false;
	}

	return hasBeenAdded;
}

unsigned int Field::getBrickNumber() const
{
	return static_cast<unsigned int>(_brickList.size());
}

Brick Field::getBrick(const Position& position)
{
	/*for(std::list<Brick>::iterator it = _brickList.begin(); it != _brickList.end(); ++it)
	{
	const Brick &b = *it;
	}*/

	for(const Brick &b : _brickList)
	{
		if(b.getPosition() == position)
		{
			return b;
		}
	}
	return Brick();
}