/*
** EPITECH PROJECT, 2023
** rtypebs [WSL : Ubuntu]
** File description:
** clickable
*/

#pragma once

#include "collider.hpp"
#include "position.hpp"
#include "vector.hpp"

struct MOUSE_BUTTON_DOWN
{
    int x;
    int y;
};

struct MOUSE_BUTTON_PRESSED
{
    int x;
    int y;
};

namespace component
{
    struct clickable
    {
        void press()
        {
            if (!is_pressed && !is_down) {
                std::cout << "clicked" << std::endl;
                is_pressed = true;
            } else
                is_pressed = false;
            is_down = true;
        }

        void release()
        {
            is_down = false;
            is_pressed = false;
        }
        bool is_pressed = false;
        bool is_down = false;
    };
}
