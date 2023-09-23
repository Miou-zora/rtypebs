/*
** EPITECH PROJECT, 2023
** rtypebs [WSL : Ubuntu]
** File description:
** path_system
*/

#pragma once

#include "registry.hpp"
#include "path.hpp"
#include "velocity.hpp"
#include "indexed_zipper.hpp"

void path_system(registry &reg,
                 sparse_array<component::velocity> &velocities,
                 sparse_array<component::path> &movements)
{
    for (auto &&[i, vel, mov] : indexed_zipper(velocities, movements)) {
        if (mov.value().is_finished()) {
            reg.remove_component<component::pattern_movement>(entity_t(i));
            continue;
        }
        mov.value().update(1.f);
        vel.value().Velocity = mov.value().get_direction();
    }
}
