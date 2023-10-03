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
    Player(Level *level);
    virtual ~Player() {}

    Level *get_level() { return level; }
    void set_level(Level *level) { this->level = level; }
    const unsigned int &get_score() const { return score; }
    void set_score(const unsigned int &score) { this->score = score; }
    const unsigned int &get_high_score() const { return high_score; }
    void set_high_score(const unsigned int &high_score) { this->high_score = high_score; }
    const PlayerState &get_state() const & { return state; }
    PlayerState get_state() && { return std::move(state); }
    void set_state(const PlayerState &state) { this->state = state; }

    void AddScore(int points)
    {
        score += points;
    }

private:
    Level *level;                // Game level
    unsigned int score = 0;      // Game score
    unsigned int high_score = 0; // High game score
    PlayerState state = kIntro;  // Player status
};

#endif // PLAYER_H_