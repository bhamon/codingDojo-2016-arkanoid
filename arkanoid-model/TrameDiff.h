#pragma once

#include <memory>

#include "Trame.h"
#include "Ball.h"

#include <list>
#include <tuple>


class Racket;

namespace arkanoid
{

	namespace network
	{

		class TrameDiff : public Trame
		{
			public:
			
				typedef std::list<std::tuple<int, int>> listTupleII;

				TrameDiff(const Ball &ball, const listTupleII &brickInfo, const Racket &racket1, const Racket &racket2);

				~TrameDiff() {}


			size_t serialize(char *buffer);

			private :
			const Ball& _ball;
			const listTupleII& _brickInfo;
			const Racket& _racket1;
			const Racket& _racket2;
		};
	}
}