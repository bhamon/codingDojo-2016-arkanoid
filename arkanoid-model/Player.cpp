#include "Player.h"

Player::Player(const std::string &name)
	: _name(name)
	, _score(0)
	, _lives(3)
{
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
Player::setScore(const unsigned int score)
{
	_score = score;
}

void
Player::setLives(const unsigned int lives)
{
	_lives = lives;
}