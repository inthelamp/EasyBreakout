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

Tutorial::Tutorial(std::shared_ptr<TutorialCondition> &tutorial_condition, const char *instruction, const KeyboardKey &keyboard_key) : tutorial_condition(tutorial_condition), instruction_(instruction)
{
    input_method_.keyboard_key = keyboard_key;
}

Tutorial::Tutorial(std::shared_ptr<TutorialCondition> &tutorial_condition, const char *instruction, const MouseButton &mouse_button) : tutorial_condition(tutorial_condition), instruction_(instruction)
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

// Tutorial::Tutorial(const Tutorial &that)
// {
//     tutorial_condition = that.tutorial_condition;
//     started_ = that.started_;
//     completed_ = that.completed_;
//     char *local_instruction = new char[strlen(that.instruction_) + 1];
//     strcpy(local_instruction, that.instruction_);
//     if (instruction_)
//         delete[] instruction_;
//     instruction_ = local_instruction;
//     input_method_ = that.input_method_;
// }

// // Move constructor
// Tutorial::Tutorial(Tutorial &&that) noexcept
// {
//     tutorial_condition = std::move(that.tutorial_condition);
//     started_ = std::exchange(that.started_, 0);
//     completed_ = std::exchange(that.completed_, 0);
//     instruction_ = std::move(that.instruction_);
//     input_method_ = std::move(that.input_method_);
// }

// Tutorial &Tutorial::operator=(const Tutorial &that)
// {
//     tutorial_condition = that.tutorial_condition;
//     started_ = that.started_;
//     completed_ = that.completed_;
//     char *local_instruction = new char[strlen(that.instruction_) + 1];
//     strcpy(local_instruction, that.instruction_);
//     if (instruction_)
//         delete[] instruction_;
//     instruction_ = local_instruction;
//     input_method_ = that.input_method_;
//     return *this;
// }

// // Move assignment operator
// Tutorial &Tutorial::operator=(Tutorial &&that) noexcept
// {
//     tutorial_condition = std::move(that.tutorial_condition);
//     started_ = std::exchange(that.started_, 0);
//     completed_ = std::exchange(that.completed_, 0);
//     instruction_ = std::move(that.instruction_);
//     input_method_ = std::move(that.input_method_);
//     return *this;
// }