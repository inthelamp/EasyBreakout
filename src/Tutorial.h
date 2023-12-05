/*
 * Tutorial.h
 *
 *  Created on: Oct. 19, 2023
 *      Author: Dong Won Kim
 */

#ifndef TUTORIAL_H_
#define TUTORIAL_H_

#include <string>
#include <memory>

#include "raylib.h"
#include "TutorialCondition.h"

union InputMethod
{
    KeyboardKey keyboard_key;
    MouseButton mouse_button;
    GamepadButton gamepad_button;
    GamepadAxis gamepad_axis;
};

class Tutorial
{
public:
    Tutorial(){};
    Tutorial(const std::string &instruction, const KeyboardKey &keyboard_key);
    Tutorial(const std::string &instruction, const KeyboardKey &keyboard_key, std::shared_ptr<TutorialCondition> const &tutorial_condition);
    Tutorial(const std::string &instruction, const MouseButton &mouse_button, std::shared_ptr<TutorialCondition> const &tutorial_condition);
    Tutorial(const std::string &instruction, const GamepadButton &gamepad_button);
    Tutorial(const std::string &instruction, const GamepadAxis &gamepad_axis);

    bool completed() { return completed_; }
    void set_completed(bool completed) { completed_ = completed; }
    bool started() { return started_; }
    void set_started(bool started) { started_ = started; }
    const std::string &instruction() const & { return instruction_; }
    std::string instruction() && { return std::move(instruction_); }
    InputMethod input_method() { return input_method_; }
    std::shared_ptr<TutorialCondition> tutorial_condition() { return tutorial_condition_; }

private:
    bool started_ = false;
    bool completed_ = false;
    std::string instruction_;
    InputMethod input_method_;
    std::shared_ptr<TutorialCondition> tutorial_condition_;
};

#endif // TUTORIAL_H_