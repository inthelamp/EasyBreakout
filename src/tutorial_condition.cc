/*
 * tutorial_condition.h
 *
 *  Created on: Jul. 5, 2024
 *      Author: Dong Won Kim
 */

#include "tutorial_condition.h"

// Copy assignment operator
TutorialCondition &TutorialCondition::operator=(const TutorialCondition &that)
{
    started_ = that.started_;
    achieved_ = that.achieved_;
    return *this;
}

// Move assignment operator
TutorialCondition &TutorialCondition::operator=(TutorialCondition &&that) noexcept
{
    started_ = std::exchange(that.started_, 0);
    achieved_ = std::exchange(that.achieved_, 0);
    return *this;
}