#include "Field.h"
#include "Calculator.h"

Field::Field(float width, float height)
	: _width(width),
	 _height(height),
	 _bricks()
{
}

float Field::getWidth() const
{
	return _width;
}

float Field::getHeight() const
{
	return _height;
}

bool Field::addBrick(const Brick& brick)
{
	if(
		!canFitInside(brick) ||
		!brick.isValid()
	)
	{
		return false;
	}

	for(Brick& b : _bricks)
	{
		if(brick.overlap(b))
		{
			return false;
		}
	}

	_bricks.push_back(brick);

	return true;
}

unsigned int Field::getBrickNumber() const
{
	return static_cast<unsigned int>(_bricks.size());
}

bool Field::canFitInside(const Brick& brick) const
{
	return
		brick.getPosition().getX() - Brick::WIDTH / 2.0 >= 0.0f &&
		brick.getPosition().getX() + Brick::WIDTH / 2.0 < _width &&
		brick.getPosition().getY() - Brick::HEIGHT / 2.0 >= 0.0f &&
		brick.getPosition().getY() + Brick::HEIGHT / 2.0 < _height;
}
