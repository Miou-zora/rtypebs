/*
** EPITECH PROJECT, 2023
** B-CPP-500-NAN-5-1-bsrtype-alexandre.franquet
** File description:
** position_system
*/

#ifndef POSITION_SYSTEM_HPP_
#define POSITION_SYSTEM_HPP_

#include "registry.hpp"
#include "position.hpp"
#include "velocity.hpp"
#include "zipper.hpp"

void position_system(registry &reg,
                     sparse_array<component::position> &positions,
                     sparse_array<component::velocity> const &velocities)
{
    (void)reg;
    for (auto &&[pos, vel] : zipper(positions, velocities))
    {
        pos.value().Position += vel.value().Velocity;
    }
}

#endif /* !POSITION_SYSTEM_HPP_ */
