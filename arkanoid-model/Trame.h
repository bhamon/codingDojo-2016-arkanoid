#pragma once

#include <memory>

namespace arkanoid
{
	namespace network
	{

		class Trame
		{
			public:
			Trame(int id_) : id(id_) {}
			virtual ~Trame() {}

			virtual size_t serialize(char * buffer);
			static void serialize(int i, char* buffer);
			static void serialize(float i, char* buffer);

			template <typename T>
			static size_t deserialize(const char* buffer, T& out)
			{
				out = *(reinterpret_cast<const T*>(buffer)) ;
				return sizeof(out) ;
			}

			template <>
			static size_t deserialize(const char* buffer, bool& out)
			{
				out = buffer[0];
				return sizeof(out) ;
				// specialized implemenation
			}

			protected:
			int id;
		};
	}
}
