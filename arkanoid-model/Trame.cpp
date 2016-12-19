#include "Trame.h"

#include <sstream>


namespace arkanoid
{
	namespace network
	{

		size_t Trame::serialize(char *buffer)
		{			
			size_t size = sizeof(id);
			memcpy(buffer, &id, size);
			return size;
		}

		void Trame::serialize(int i, char* buffer)
		{
			memcpy(buffer, &i, sizeof(int));
		}

		void Trame::serialize(float i, char* buffer)
		{
			memcpy(buffer, &i, sizeof(float));
		}


	}
}