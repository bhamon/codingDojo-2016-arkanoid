#ifndef RACKET_H
#define RACKET_H

class Racket
{
	private:
	unsigned int _position;

	public:
	Racket(unsigned int position);

	unsigned int getPosition() const;
	void setPosition(unsigned int position);
};

#endif