/*
 * player.cc
 *
 *  Created on: Sep. 7, 2023
 *      Author: Dong Won Kim
 */

#include "player.h"

Player::Player(const Level &level) : level_(level), score_(0)
{
}

bool Player::IsCompletedAllTutorials()
{
	for (auto &tutorial : tutorials_)
	{
		if (!tutorial->completed())
		{
			return false;
		}
	}
	return true;
}

void Player::AddTutorial(std::unique_ptr<Tutorial> tutorial)
{
	tutorials_.emplace_back(std::move(tutorial));
}

void Player::AddScore(int score)
{
	score_ += score;
}