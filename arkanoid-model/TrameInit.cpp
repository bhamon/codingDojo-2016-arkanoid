#include "TrameInit.h"

#include <sstream>



namespace arkanoid
{
	namespace network
	{
		TrameInit::TrameInit(const Field &field) : Trame(0), _field(field)
		{
		}


		size_t TrameInit::serialize(char *buffer)
		{
			size_t size = Trame::serialize(buffer);

			arkanoid::network::Trame::serialize(_field.getWidth(), &buffer[size]);
			size += sizeof(float);
			arkanoid::network::Trame::serialize(_field.getHeight(), &buffer[size]);
			size += sizeof(float);

			arkanoid::network::Trame::serialize(static_cast<int>(_field.getBrickNumber()), &buffer[size]);
			size += sizeof(int);

			for(const Brick &b : _field)
			{
				arkanoid::network::Trame::serialize(b.getPosition().getX(), &buffer[size]);
				size += sizeof(float);
				arkanoid::network::Trame::serialize(b.getPosition().getY(), &buffer[size]);
				size += sizeof(float);
				arkanoid::network::Trame::serialize(static_cast<int>(b.getStrength()), &buffer[size]);
				size += sizeof(int);
			}

			return size ;
		}
	}
}