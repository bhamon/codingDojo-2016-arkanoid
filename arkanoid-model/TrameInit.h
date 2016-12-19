#pragma once

#include <memory>

#include "Trame.h"
#include "Field.h"

namespace arkanoid
{
	namespace network
	{

		class TrameInit : public Trame
		{
			public:
			TrameInit(const Field &field);

			~TrameInit()
			{
			}
	

			size_t serialize(char *buffer);

			private:
			const Field& _field;
		};
	}
}