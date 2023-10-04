/*
 * Player.h
 *
 *  Created on: Aug. 31, 2023
 *      Author: Dong Won Kim
 */

#include <utility>

// Forward declarations
class Level;

#ifndef PLAYER_H_
#define PLAYER_H_

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
    Player(const Level *level);
    virtual ~Player() {}

    const Level *get_level() const { return level; }
    void set_level(const Level *level) { this->level = level; }
    unsigned int get_score() { return score; }
    void set_score(unsigned int score) { this->score = score; }
    unsigned int get_high_score() { return high_score; }
    void set_high_score(unsigned int high_score) { this->high_score = high_score; }
    PlayerState get_state() { return state; }
    void set_state(PlayerState state) { this->state = state; }

    void AddScore(int points)
    {
        score += points;
    }

private:
    const Level *level;          // Game level
    unsigned int score = 0;      // Game score
    unsigned int high_score = 0; // High game score
    PlayerState state = kIntro;  // Player status
};

#endif // PLAYER_H_