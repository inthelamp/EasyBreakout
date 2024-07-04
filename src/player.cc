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

void Player::tutorials(std::unique_ptr<TutorialCondition> hit_ball_back_condition)
{
        Tutorial move_to_left("Press left arrow key to move to left.", KEY_LEFT);
        Tutorial move_to_right("Press right arrow key to move to right.", KEY_RIGHT);
        Tutorial start_game("Press space bar to start the game.", KEY_SPACE);
        Tutorial hit_ball_back("Press tab key when the ball hits the playing bar.", KEY_TAB, std::move(hit_ball_back_condition));

        tutorials_.emplace_back(std::make_shared<Tutorial>(std::move(move_to_left)));
        tutorials_.emplace_back(std::make_shared<Tutorial>(std::move(move_to_right)));
        tutorials_.emplace_back(std::make_shared<Tutorial>(std::move(start_game)));
        tutorials_.emplace_back(std::make_shared<Tutorial>(std::move(hit_ball_back)));
        current_tutorial_idx_ = 0;
}

void Player::tutorials(std::unique_ptr<TutorialCondition> move_to_left_condition, std::unique_ptr<TutorialCondition> move_to_right_condition, std::unique_ptr<TutorialCondition> start_game_condition, std::unique_ptr<TutorialCondition> hit_ball_back_condition)
{
        Tutorial move_to_left("Touch the second circle on the left to move to left.", MOUSE_BUTTON_LEFT, std::move(move_to_left_condition));
        Tutorial move_to_right("Touch the circle on the right to move to right.", MOUSE_BUTTON_LEFT, std::move(move_to_right_condition));
        Tutorial start_game("Touch the playing bar under the ball to start the game.", MOUSE_BUTTON_LEFT, std::move(start_game_condition));
        Tutorial hit_ball_back("Touch the first circle on the left when the ball hits the playing bar.", MOUSE_BUTTON_LEFT, std::move(hit_ball_back_condition));

        tutorials_.emplace_back(std::make_shared<Tutorial>(std::move(move_to_left)));
        tutorials_.emplace_back(std::make_shared<Tutorial>(std::move(move_to_right)));
        tutorials_.emplace_back(std::make_shared<Tutorial>(std::move(start_game)));
        tutorials_.emplace_back(std::make_shared<Tutorial>(std::move(hit_ball_back)));
        current_tutorial_idx_ = 0;
}

bool Player::IsCompletedAllTutorials()
{
        for (auto tutorial : tutorials_)
        {
                if (!tutorial->completed())
                {
                        return false;
                }
        }
        return true;
}