/*
 * Player.h
 *
 *  Created on: Aug. 31, 2023
 *      Author: Dong Won Kim
 */

#ifndef PLAYER_H_
#define PLAYER_H_

#include <utility>
#include <vector>

#include "Level.h"
#include "Tutorial.h"
#include "TutorialCondition.h"

enum PlayerState
{
    kIntro,
    kPlay,
    kLevelUp,
    kOut,
    kEnd,
    kGoodbye
};

class Player
{
public:
    Player(const Level &level);

    const Level &level() const & { return level_; }
    Level level() && { return std::move(level_); }
    void set_level(const Level &level) { level_ = level; }
    unsigned int score() { return score_; }
    void set_score(unsigned int score) { score_ = score; }
    unsigned int high_score() { return high_score_; }
    void set_high_score(unsigned int high_score) { high_score_ = high_score; }
    PlayerState state() { return state_; }
    void set_state(PlayerState state) { state_ = state; }

    int current_tutorial_idx() { return current_tutorial_idx_; }
    void set_current_tutorial_idx(int index) { current_tutorial_idx_ = index; }
    std::shared_ptr<std::vector<Tutorial>> tutorials() { return tutorials_; }
    void set_tutorials(std::shared_ptr<TutorialCondition> const &hit_ball_back_condition);
    void set_tutorials(std::shared_ptr<TutorialCondition> const &move_to_left_condition, std::shared_ptr<TutorialCondition> const &move_to_right_condition, std::shared_ptr<TutorialCondition> const &start_game_condition, std::shared_ptr<TutorialCondition> const &hit_ball_back_condition);

    bool TutorialsCompleted();
    void AddScore(int points)
    {
        score_ += points;
    }

private:
    Level level_;                 // Game level
    unsigned int score_ = 0;      // Game score
    unsigned int high_score_ = 0; // High game score
    PlayerState state_ = kIntro;  // Player status
    int current_tutorial_idx_ = 0;
    std::shared_ptr<std::vector<Tutorial>> tutorials_; // A list of tutorials
};

#endif // PLAYER_H_