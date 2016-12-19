#pragma once

#include "Trame.h"

class Racket;

namespace arkanoid
{

	namespace network
	{

		class TrameClientAction : public Trame
		{
			public:
			TrameClientAction(const float racketX) : Trame(2), _racketX(racketX) {}
			TrameClientAction() : Trame(2), _racketX(0.f) {}

			~TrameClientAction()
			{
			}

			size_t serialize(char *buffer);

			float getRacketX() const
			{
				return _racketX;
			}

			static TrameClientAction *deserialize(const char *buffer);

			private:
				const float _racketX;
		};
	}
}