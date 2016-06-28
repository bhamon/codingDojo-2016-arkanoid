#include "Position.h"
#include "Vector.h"


Position::Position(int x, int y)
	: _x(x)
	, _y(y)
{
}

Position::~Position()
{
}

int
Position::getX() const
{
	return _x;
}

const int&
Position::getY() const
{
	return _y;
}

void
Position::setX(int x)
{
	_x = x;
}

void
Position::setY(const int& y)
{
	_y = y;
}

bool
Position::operator==(const Position &pos) const
{
	return pos._x == _x && pos._y == _y;
}

Position& Position::operator+=(const Vector<float> &v)
{
	_x += v.getX();
	_y += v.getY();

	return *this;
}