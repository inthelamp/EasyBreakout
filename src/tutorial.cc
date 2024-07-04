/*
 * tutorial.cc
 *
 *  Created on: Oct. 19, 2023
 *      Author: Dong Won Kim
 */

#include "tutorial.h"

Tutorial::Tutorial(const char *instruction, const KeyboardKey &keyboard_key) : instruction_(instruction)
{
    input_method_.keyboard_key = keyboard_key;
}

Tutorial::Tutorial(const char *instruction, const KeyboardKey &keyboard_key, std::unique_ptr<TutorialCondition> tutorial_condition) : instruction_(instruction), tutorial_condition_(std::move(tutorial_condition))
{
    input_method_.keyboard_key = keyboard_key;
}

Tutorial::Tutorial(const char *instruction, const MouseButton &mouse_button, std::unique_ptr<TutorialCondition> tutorial_condition) : instruction_(instruction), tutorial_condition_(std::move(tutorial_condition))
{
    input_method_.mouse_button = mouse_button;
}

Tutorial::Tutorial(const char *instruction, const GamepadButton &gamepad_button) : instruction_(instruction)
{
    input_method_.gamepad_button = gamepad_button;
}

Tutorial::Tutorial(const char *instruction, const GamepadAxis &gamepad_axis) : instruction_(instruction)
{
    input_method_.gamepad_axis = gamepad_axis;
}

// Move constructor
Tutorial::Tutorial(Tutorial &&that) noexcept
{
    started_ = std::exchange(that.started_, 0);
    completed_ = std::exchange(that.completed_, 0);
    instruction_ = std::move(that.instruction_);
    input_method_ = std::move(that.input_method_);
    if (that.tutorial_condition_)
    {
        tutorial_condition_ = std::move(that.tutorial_condition_);
    }
}

// Tutorial &Tutorial::operator=(const Tutorial &that)
// {
//     started_ = that.started_;
//     completed_ = that.completed_;
//     char *local_instruction = new char[strlen(that.instruction_) + 1];
//     strcpy(local_instruction, that.instruction_);
//     delete[] instruction_;
//     instruction_ = local_instruction;
//     input_method_ = that.input_method_;
//     tutorial_condition_ = that.tutorial_condition_;
//     return *this;
// }

// Move assignment operator
Tutorial &Tutorial::operator=(Tutorial &&that) noexcept
{
    started_ = std::exchange(that.started_, 0);
    completed_ = std::exchange(that.completed_, 0);
    instruction_ = std::move(that.instruction_);
    input_method_ = std::move(that.input_method_);
    if (that.tutorial_condition_)
    {
        tutorial_condition_ = std::move(that.tutorial_condition_);
    }
    return *this;
}