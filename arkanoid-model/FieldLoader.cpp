#include <sstream>
#include <istream>
#include "FieldLoader.h"

#include "Field.h"
#include "Brick.h"

void FieldLoader::load(std::istream &is, Field &field)
{
	const unsigned int BUF_SIZE = 50;
	//Brick brick(p, 1u);
	char line[BUF_SIZE];
	//is.getline(line, 50);

	float x = .0;
	float y = .0;

	while(!is.eof() && is.good())
	{
		is.getline(line, BUF_SIZE);
		std::string lineStr(line);
		std::istringstream el(lineStr);
		int elt = 0;
		x = .0;
			
		while(!el.eof())
		{
			el >> elt;
			if(elt != 0)
			{
				math::Point2<float> pt(x*Brick::WIDTH + Brick::WIDTH / 2, y*Brick::HEIGHT + Brick::HEIGHT/2);
				Brick brick(pt, elt);
				field.addBrick(brick);
			}
			x++;
		}
		y++;
	}
}