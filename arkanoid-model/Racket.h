#ifndef RACKET_H
#define RACKET_H

class Racket
{
	public:
	static const float WIDTH;
	static const float HEIGHT;
	static const float OFFSET;

	private:
	float _position;

	public:
	Racket(float position);

	float getPosition() const;

	void setPosition(float position);

	float& position();
};

#endif