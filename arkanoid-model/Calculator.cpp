#include "Calculator.h"
#include "Ball.h"
#include "Vector.h"

void Calculator::move(Ball& ball)
{
	Position newPos(ball.getPosition());

	newPos += ball.getVector();

	ball.setPosition(newPos);
}


void Calculator::collision(Ball& ball, const VectorF& normal)
{
	VectorF vectorX(0, 0);
	VectorF vectorY(0, 0);
	vectorX = normal * normal.dot(-ball.getVector());
	vectorY = vectorX + ball.getVector();

	ball.setVector(vectorX + vectorY);
}