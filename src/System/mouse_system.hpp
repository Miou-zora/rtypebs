/*
** EPITECH PROJECT, 2023
** rtypebs [WSL : Ubuntu]
** File description:
** mouse_system
*/

#pragma once

#include "registry.hpp"
#include "raylib.h"
#include "EventManager.hpp"
#include "clickable.hpp"
#include "zipper.hpp"

class mouse_system
{
public:
    mouse_system() = default;
    ~mouse_system() = default;

    void operator()(registry &r, sparse_array<component::clickable> &clickables,
                 sparse_array<component::position> const &positions,
                 sparse_array<component::collider> const &colliders) const
    {
        (void)r;
        bool isButtonDown = IsMouseButtonDown(MOUSE_LEFT_BUTTON);

        for (auto &&[cli, pos, col] : zipper(clickables, positions, colliders))
        {
            if (isButtonDown)
            {
                if (collide_system::collideWith(col.value(), {GetMouseX(), GetMouseY()}, pos.value().Position))
                    press(cli.value());
            }
            else
            {
                release(cli.value());
            }
        }
    }

private:
    void press(component::clickable &cli) const
    {
        if (!cli.is_pressed && !cli.is_down)
        {
            cli.is_pressed = true;
        }
        else
            cli.is_pressed = false;
        cli.is_down = true;
    }

    void release(component::clickable &cli) const
    {
        cli.is_down = false;
        cli.is_pressed = false;
    }
};
