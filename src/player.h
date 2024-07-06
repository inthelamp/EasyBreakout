/*
 * player.h
 *
 *  Created on: Aug. 31, 2023
 *      Author: Dong Won Kim
 */

#ifndef PLAYER_H_
#define PLAYER_H_

#include <utility>
#include <memory>
#include <vector>

#include "level.h"
#include "tutorial.h"
#include "tutorial_condition.h"

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
    void level(const Level &level) { level_ = level; }
    unsigned int score() { return score_; }
    void score(unsigned int score) { score_ = score; }
    unsigned int high_score() { return high_score_; }
    void high_score(unsigned int high_score) { high_score_ = high_score; }
    PlayerState state() { return state_; }
    void state(PlayerState state) { state_ = state; }

    int current_tutorial_idx() { return current_tutorial_idx_; }
    void current_tutorial_idx(int index) { current_tutorial_idx_ = index; }

    // Get tutorials
    std::vector<std::shared_ptr<Tutorial>> &tutorials() { return tutorials_; }

    bool IsCompletedAllTutorials();

    void AddTutorial(std::unique_ptr<Tutorial> tutorial);
    void AddScore(int score);

private:
    Level level_;                 // Game level
    unsigned int score_ = 0;      // Game score
    unsigned int high_score_ = 0; // High game score
    PlayerState state_ = kIntro;  // Player status
    int current_tutorial_idx_ = 0;
    std::vector<std::shared_ptr<Tutorial>> tutorials_{}; // A list of tutorials
};

#endif // PLAYER_H_