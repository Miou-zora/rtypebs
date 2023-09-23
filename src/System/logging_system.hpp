/*
** EPITECH PROJECT, 2023
** rtypebs [WSL : Ubuntu]
** File description:
** logging_system
*/

#pragma once

#include "registry.hpp"
#include "indexed_zipper.hpp"
#include "position.hpp"
#include "velocity.hpp"

void logging_system(registry &r,
                    sparse_array<component::position> const &positions,
                    sparse_array<component::velocity> const &velocities)
{
    (void)r;
    for (auto &&[i, pos, vel] : indexed_zipper(positions, velocities))
        std::cerr << i << ": Position = " << pos.value().Position << ", Velocity = " << vel.value().Velocity << std ::endl;
}
