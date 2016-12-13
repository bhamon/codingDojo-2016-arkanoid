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
	virtual ~Player();

	bool operator==(const Player& p) const ;

	const std::string& getName() const;
	unsigned int getScore() const;
	unsigned int getLives() const;

	void setName(const std::string& name);
	void setScore(unsigned int score);
	void setLives(unsigned int lives);
	void lostOneLife();
	void incrementScore();

	unsigned int& score();
	unsigned int& lives();
};

#endif
