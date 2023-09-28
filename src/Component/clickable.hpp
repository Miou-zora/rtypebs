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
        bool is_pressed = false;
        bool is_down = false;
    };
}
