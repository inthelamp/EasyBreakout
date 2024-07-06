/*
 * tutorial_condition.h
 *
 *  Created on: November 28, 2023
 *      Author: Dong Won Kim
 */

#ifndef TUTORIAL_CONDITION_
#define TUTORIAL_CONDITION_

#include <memory>

class TutorialCondition
{
public:
    TutorialCondition() = default;
    TutorialCondition(const TutorialCondition &) = default;      // Copy constructor
    TutorialCondition(TutorialCondition &&) = delete;            // Move constructor
    TutorialCondition &operator=(const TutorialCondition &);     // Copy assignment operator
    TutorialCondition &operator=(TutorialCondition &&) noexcept; // Move assignment operator
    ~TutorialCondition() = default;

    bool started() { return started_; }
    void started(bool started) { started_ = started; }

    bool achieved() { return achieved_; }
    void achieved(bool achieved) { achieved_ = achieved; }

private:
    bool started_ = false;
    bool achieved_ = false;
};

#endif // TUTORIAL_CONDITION_