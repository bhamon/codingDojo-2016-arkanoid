#include "Racket.h"

Racket::Racket(unsigned int position)
	: _position(position) {
}

unsigned int 
Racket::getPosition() const {
	return _position;
}
void 
Racket::setPosition(unsigned int position) {
	_position = position;
}