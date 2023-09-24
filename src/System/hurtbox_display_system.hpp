/*
** EPITECH PROJECT, 2023
** rtypebs [WSL : Ubuntu]
** File description:
** hurtbox_display_system
*/

#pragma once

#include "registry.hpp"
#include "collider.hpp"
#include "displayable_hurtbox.hpp"
#include "indexed_zipper.hpp"
#include "draw_system.hpp"

void hurtbox_display_system(registry &reg,
                    sparse_array<component::collider> const &colliders,
                    sparse_array<component::displayable_hurtbox> const &displayable_hurtboxes,
                    sparse_array<component::position> const &positions)
{
    (void)reg;
    for (auto &&[i, hb, displayable_hb, pos] : indexed_zipper(colliders, displayable_hurtboxes, positions))
    {
        if (!displayable_hb.value().is_displayed)
            continue;
        DrawRectangleLines(pos.value().Position.x,
        pos.value().Position.y,
        hb.value().width,
        hb.value().height,
        hb.value().collided_with.empty() ? GREEN : RED);
    }
}
