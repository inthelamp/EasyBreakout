/*
 * tutorial.h
 *
 *  Created on: Oct. 19, 2023
 *      Author: Dong Won Kim
 */

#ifndef TUTORIAL_H_
#define TUTORIAL_H_

#include <string.h>
#include "raylib.h"
#include "tutorial_condition.h"

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
    Tutorial(const char *instruction, const KeyboardKey &keyboard_key);
    Tutorial(std::shared_ptr<TutorialCondition> &tutorial_condition, const char *instruction, const KeyboardKey &keyboard_key);
    Tutorial(std::shared_ptr<TutorialCondition> &tutorial_condition, const char *instruction, const MouseButton &mouse_button);
    Tutorial(const char *instruction, const GamepadButton &gamepad_button);
    Tutorial(const char *instruction, const GamepadAxis &gamepad_axis);
    Tutorial(const Tutorial &) = delete;            // Copy constructor
    Tutorial(Tutorial &&) = delete;                 // Move constructor
    Tutorial &operator=(const Tutorial &) = delete; // Copy assignment operator
    Tutorial &operator=(Tutorial &&) = delete;      // Move assignment operator
    ~Tutorial() = default;

    std::shared_ptr<TutorialCondition> tutorial_condition{};

    bool completed() { return completed_; }
    void completed(bool completed) { completed_ = completed; }
    bool started() { return started_; }
    void started(bool started) { started_ = started; }
    const char *instruction() { return instruction_; }
    InputMethod input_method() { return input_method_; }

private:
    bool started_ = false;
    bool completed_ = false;
    const char *instruction_{}; // Shoud not delete in its destructor because it created using "", not new or new []
    InputMethod input_method_;
};

#endif // TUTORIAL_H_