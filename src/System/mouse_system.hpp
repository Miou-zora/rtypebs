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

void mouse_system(registry &r, sparse_array<component::clickable> &clickables,
                    sparse_array<component::position> const &positions,
                    sparse_array<component::collider> const &colliders)
{
    (void)r;
    bool isButtonDown = IsMouseButtonDown(MOUSE_LEFT_BUTTON);

    for (auto &&[cli, pos, col] : zipper(clickables, positions, colliders))
    {
        if (isButtonDown) {
            if (col.value().collideWith({GetMouseX(), GetMouseY()}, pos.value().Position))
                cli.value().press();
        } else {
            cli.value().release();
        }
    }
}
