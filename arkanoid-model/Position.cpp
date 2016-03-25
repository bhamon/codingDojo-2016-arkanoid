#include "Position.h"


Position::Position(unsigned int x, unsigned int y) 
	: _x(x)
	, _y(y) {
}

Position::~Position() {
}

unsigned int Position::getX() const {
	return _x;
}

const unsigned int& Position::getY() const {
	return _y;
}

void Position::setX(unsigned int x) {
	_x = x;
}

void Position::setY(const unsigned int& y) {
	_y = y ;
}