/*
 * Tutorial.cpp
 *
 *  Created on: Oct. 19, 2023
 *      Author: Dong Won Kim
 */

#include "Tutorial.h"

Tutorial::Tutorial(const std::string &instruction, const KeyboardKey &keyboard_key) : instruction_(instruction)
{
    input_method_.keyboard_key = keyboard_key;
}

Tutorial::Tutorial(const std::string &instruction, const KeyboardKey &keyboard_key, std::shared_ptr<TutorialCondition> const &tutorial_condition) : instruction_(instruction), tutorial_condition_(tutorial_condition)
{
    input_method_.keyboard_key = keyboard_key;
}

Tutorial::Tutorial(const std::string &instruction, const MouseButton &mouse_button, std::shared_ptr<TutorialCondition> const &tutorial_condition) : instruction_(instruction), tutorial_condition_(tutorial_condition)
{
    input_method_.mouse_button = mouse_button;
}

Tutorial::Tutorial(const std::string &instruction, const GamepadButton &gamepad_button) : instruction_(instruction)
{
    input_method_.gamepad_button = gamepad_button;
}

Tutorial::Tutorial(const std::string &instruction, const GamepadAxis &gamepad_axis) : instruction_(instruction)
{
    input_method_.gamepad_axis = gamepad_axis;
}