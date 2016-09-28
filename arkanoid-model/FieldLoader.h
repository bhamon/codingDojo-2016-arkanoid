#ifndef FIELD_LOADER_H
#define FIELD_LOADER_H

#include <istream>

class Field;

class FieldLoader
{

	public:

	static void load(std::istream &is, Field &field);

};

#endif