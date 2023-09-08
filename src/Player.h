/*
 * Player.h
 *
 *  Created on: Aug. 31, 2023
 *      Author: Dong Won Kim
 */

#ifndef PLAYER_H_
#define PLAYER_H_

#include "Level.h"

class Player {
private:
    const Level * level;                            // Game level
    unsigned int score = 0;                         // Game score   
    const enum status_t { play, stop, end } status = stop;  

public:     
    Player(const Level * level);
    virtual ~Player() {}

	const Level * get_level() const { return level; }
    const unsigned int& get_score() const { return score; }

    void AddScore(const int& points) {
        score += points;
    }
};

#endif // PLAYER_H_ 