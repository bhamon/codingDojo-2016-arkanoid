#include "TrameDiff.h"
#include "Racket.h"
#include <sstream>



namespace arkanoid
{
	namespace network
	{
		TrameDiff::TrameDiff(const Ball &ball, const listTupleII &brickInfo, const Racket &racket1, const Racket &racket2)
			: Trame(1)
			, _ball(ball)
			, _brickInfo(brickInfo)
			, _racket1(racket1)
			, _racket2(racket2)
		{
		}

		size_t TrameDiff::serialize(char *buffer)
		{
			size_t size = Trame::serialize(buffer);

			arkanoid::network::Trame::serialize(_ball.getPosition().getX(), &buffer[size]);
			size += sizeof(float);
			arkanoid::network::Trame::serialize(_ball.getPosition().getY(), &buffer[size]);
			size += sizeof(float);

			arkanoid::network::Trame::serialize(_ball.getVelocity().getX(), &buffer[size]);
			size += sizeof(float);
			arkanoid::network::Trame::serialize(_ball.getVelocity().getY(), &buffer[size]);
			size += sizeof(float);

			arkanoid::network::Trame::serialize(_racket1.getPosition().getX(), &buffer[size]);
			size += sizeof(float);
			arkanoid::network::Trame::serialize(_racket2.getPosition().getX(), &buffer[size]);
			size += sizeof(float);

			arkanoid::network::Trame::serialize(static_cast<int>(_brickInfo.size()), &buffer[size]);
			size += sizeof(int);

			for(const auto &BI : _brickInfo)
			{
				arkanoid::network::Trame::serialize(std::get<0>(BI), &buffer[size]);
				size += sizeof(int);
				arkanoid::network::Trame::serialize(std::get<1>(BI), &buffer[size]);
				size += sizeof(int);
			}

			return size ;
		}
	}
}