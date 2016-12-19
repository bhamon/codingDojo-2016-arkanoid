#include "TrameClientAction.h"
#include "Racket.h"


namespace arkanoid
{
	namespace network
	{
		size_t TrameClientAction::serialize(char *buffer)
		{
			size_t size = Trame::serialize(buffer);

			arkanoid::network::Trame::serialize(_racketX, &buffer[size]);
			size += sizeof(float);

			return size ;
		}

		TrameClientAction *TrameClientAction::deserialize(const char *buffer)
		{
			float x = 0.f;
			Trame::deserialize<float>(buffer, x) ;
			return new TrameClientAction(x);
		}

	}
}