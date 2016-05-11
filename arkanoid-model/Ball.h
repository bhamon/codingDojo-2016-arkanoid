#ifndef BALL_H
#define BALL_H

class Position;

class Ball
{
	private:
	Position* _pPosition;
	unsigned int _speed;

	public:
	Ball(unsigned int position_x, unsigned int position_y, unsigned int speed);
	virtual ~Ball();

	unsigned int getPositionX() const;
	unsigned int getPositionY() const;
	unsigned int getSpeed() const;
};


#endif