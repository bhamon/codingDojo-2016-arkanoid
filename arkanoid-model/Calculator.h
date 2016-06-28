#ifndef CALCULATOR_H
#define CALCULATOR_H


#include "Vector.h"

class Ball;

class Calculator
{
	public:
	static void move(Ball &ball);

	static void collision(Ball& ball, const VectorF& normal);
};


#endif