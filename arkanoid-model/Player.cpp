#include "Player.h"

Player::Player(const std::string &name)
	: _name(name)
	, _score(0)
	, _lives(3)
{
}

Player::~Player()
{
}

bool Player::operator==(const Player& p) const
{
	return _name == p._name ;
}

const std::string &
Player::getName() const
{
	return _name;
}

unsigned int
Player::getScore() const
{
	return _score;
}

unsigned int
Player::getLives() const
{
	return _lives;
}

void
Player::setName(const std::string& name)
{
	_name = name;
}

void
Player::setScore(unsigned int score)
{
	_score = score;
}

void
Player::setLives(unsigned int lives)
{
	_lives = lives;
}

unsigned int& Player::score()
{
	return _score;
}

unsigned int& Player::lives()
{
	return _lives;
}