#ifndef POSITION_H
#define POSITION_H

class Position {
	private:
		unsigned int _x;
		unsigned int _y;

	public:
		Position(unsigned int x, unsigned int y);
		virtual ~Position();

		unsigned int getX() const;
		const unsigned int& getY() const;

		void setX(unsigned int x) ;
		void setY(const unsigned int& y) ;
};

#endif // POSITION_H