/*
** EPITECH PROJECT, 2023
** rtypebs [WSL : Ubuntu]
** File description:
** collide_system
*/

#pragma once

#include "registry.hpp"
#include "collider.hpp"
#include "position.hpp"
#include "indexed_zipper.hpp"
#include "EventManager.hpp"

void collide_system(registry &reg,
                    sparse_array<component::collider> &colliders,
                    sparse_array<component::position> const &positions)
{
    for (auto &&[index_first, col_first, pos_first] : indexed_zipper(colliders, positions))
    {
        col_first.value().collided_with.clear();
        for (auto &&[index_second, col_second, pos_second] : indexed_zipper(colliders, positions))
        {
            if (index_first == index_second)
                continue;
            if (col_second.value().collideWith(pos_second.value().Position, col_first.value(), pos_first.value().Position))
            {
                col_first.value().collided_with.push_back(reg.entity_from_index(index_second));
            }
        }
    }
}
