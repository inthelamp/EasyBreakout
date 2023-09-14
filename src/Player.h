/*
 * Player.h
 *
 *  Created on: Aug. 31, 2023
 *      Author: Dong Won Kim
 */

#ifndef PLAYER_H_
#define PLAYER_H_

#include <utility>
#include "Level.h"

enum player_status_t { intro, play, level_up, end, out };

class Player {
private:
    Level * level;                                  // Game level
    unsigned int score = 0;                         // Game score   
    unsigned int high_score = 0;                    // High game score   
    player_status_t status = intro;                 // Player status

public:     
    Player(Level * level);
    virtual ~Player() {}

	const Level * get_level() const { return level; }
    void set_level(Level * level) { this->level = level; }
    const unsigned int& get_score() const { return score; }
    void set_score(const unsigned int& score) { this->score = score; }
    const unsigned int& get_high_score() const { return high_score; }
    void set_high_score(const unsigned int& high_score) { this->high_score = high_score; }    
	const player_status_t& get_status() const & { return status; }
	player_status_t get_status() && { return std::move(status); }
    void set_status(const player_status_t& status) { this->status = status; }
    void set_status(player_status_t&& status) { this->status = std::move(status); }

    void AddScore(const int& points) {
        score += points;
    }
};

#endif // PLAYER_H_ 