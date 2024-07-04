/*
 * tutorial_condition.h
 *
 *  Created on: November 28, 2023
 *      Author: Dong Won Kim
 */

#ifndef TUTORIAL_CONDITION_
#define TUTORIAL_CONDITION_

class TutorialCondition
{
public:
    TutorialCondition() = default;
    TutorialCondition(const TutorialCondition &) = default;           // Copy constructor
    TutorialCondition(TutorialCondition &&) = delete;                 // Move constructor
    TutorialCondition &operator=(const TutorialCondition &) = delete; // Copy assignment operator
    TutorialCondition &operator=(TutorialCondition &&) = delete;      // Move assignment operator
    virtual ~TutorialCondition() = default;

    bool condition_started() { return condition_started_; }
    void condition_started(bool started) { condition_started_ = started; }

    bool condition_achieved() { return condition_achieved_; }
    void condition_achieved(bool achieved) { condition_achieved_ = achieved; }

private:
    bool condition_started_ = false;
    bool condition_achieved_ = false;
};

#endif // TUTORIAL_CONDITION_