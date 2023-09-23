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
                 sparse_array<component::path> &paths)
{
    (void)reg;
    for (auto &&[i, vel, path] : indexed_zipper(velocities, paths)) {
        if (path.value().is_finished()) {
            continue;
        }
        path.value().update(1.f);
        vel.value().Velocity = path.value().get_direction();
    }
}
