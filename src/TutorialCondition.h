/*
 * TutorialCondition.h
 *
 *  Created on: November 28, 2023
 *      Author: Dong Won Kim
 */

#ifndef TUTORIAL_CONDITION_
#define TUTORIAL_CONDITION_

class TutorialCondition
{
public:
    TutorialCondition() {}
    virtual ~TutorialCondition() {}

    bool condition_started() { return condition_started_; }
    void set_condition_started(bool started) { condition_started_ = started; }

    bool condition_achieved() { return condition_achieved_; }
    void set_condition_achieved(bool achieved) { condition_achieved_ = achieved; }

private:
    bool condition_started_ = false;
    bool condition_achieved_ = false;
};

#endif // TUTORIAL_CONDITION_