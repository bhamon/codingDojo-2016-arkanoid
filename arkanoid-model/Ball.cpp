#include "Ball.h"
#include "Position.h"

Ball::Ball(unsigned int position_x, unsigned int position_y, unsigned int speed)
	: _pPosition(0)
	, _speed(speed) {
	_pPosition = new Position(position_x, position_y);
}

Ball::~Ball() {
	delete _pPosition;
}

unsigned int 
Ball::getPositionX() const {
	return _pPosition->getX();
}
unsigned int 
Ball::getPositionY() const {
	return _pPosition->getY();
}
unsigned int 
Ball::getSpeed() const {
	return _speed;
}