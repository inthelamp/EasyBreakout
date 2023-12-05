/*
 * Player.cpp
 *
 *  Created on: Sep. 7, 2023
 *      Author: Dong Won Kim
 */

#include "Player.h"

Player::Player(const Level &level) : level_(level), score_(0)
{
}

void Player::set_tutorials(std::shared_ptr<TutorialCondition> const &hit_ball_back_condition)
{
        Tutorial move_to_left("Press left arrow key to move to left.", KEY_LEFT);
        Tutorial move_to_right("Press right arrow key to move to right.", KEY_RIGHT);
        Tutorial start_game("Press space bar to start the game.", KEY_SPACE);
        Tutorial hit_ball_back("Press tab key when the ball hits the playing bar.", KEY_TAB, hit_ball_back_condition);

        std::vector<Tutorial> vector_of_tutorials{move_to_left, move_to_right, start_game, hit_ball_back};
        tutorials_ = std::make_shared<std::vector<Tutorial>>(vector_of_tutorials);
        current_tutorial_idx_ = 0;
}

void Player::set_tutorials(std::shared_ptr<TutorialCondition> const &move_to_left_condition, std::shared_ptr<TutorialCondition> const &move_to_right_condition, std::shared_ptr<TutorialCondition> const &start_game_condition, std::shared_ptr<TutorialCondition> const &hit_ball_back_condition)
{
        Tutorial move_to_left("Touch the second circle on the left to move to left.", MOUSE_BUTTON_LEFT, move_to_left_condition);
        Tutorial move_to_right("Touch the circle on the right to move to right.", MOUSE_BUTTON_LEFT, move_to_right_condition);
        Tutorial start_game("Touch the playing bar under the ball to start the game.", MOUSE_BUTTON_LEFT, start_game_condition);
        Tutorial hit_ball_back("Touch the first circle on the left when the ball hits the playing bar.", MOUSE_BUTTON_LEFT, hit_ball_back_condition);

        std::vector<Tutorial> vector_of_tutorials{move_to_left, move_to_right, start_game, hit_ball_back};
        tutorials_ = std::make_shared<std::vector<Tutorial>>(vector_of_tutorials);
        current_tutorial_idx_ = 0;
}

bool Player::TutorialsCompleted()
{
        auto tutorials = *tutorials_.get();
        for (Tutorial &tutorial : tutorials)
        {
                if (!tutorial.completed())
                {
                        return false;
                }
        }
        return true;
}