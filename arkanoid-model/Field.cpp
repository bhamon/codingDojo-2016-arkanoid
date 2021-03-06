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

void Field::removeBrick(const Brick& brick)
{
	_bricks.remove(brick);
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

const std::list<Brick>& Field::getListBricks() const
{
	return _bricks;
}

std::list<Brick>::iterator Field::begin()
{
	return _bricks.begin();
}

std::list<Brick>::iterator Field::end()
{
	return _bricks.end();
}
std::list<Brick>::const_iterator Field::begin() const
{
	return _bricks.begin();
}
std::list<Brick>::const_iterator Field::end() const
{
	return _bricks.end();
}