#ifndef PLAYER_H
#define PLAYER_H

#include <string>

class Player
{
	private:
	std::string _name;
	unsigned int _score;
	unsigned int _lives;

	public:
	Player(const std::string &name);

	const std::string &getName() const;
	unsigned int getScore() const;
	unsigned int getLives() const;

	void setName(const std::string& name);
	void setScore(const unsigned int score);
	void setLives(const unsigned int lives);

};

#endif // PLAYER_H