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

void position_system(registry &reg,
                     sparse_array<component::position> &positions,
                     sparse_array<component::velocity> const &velocities)
{
    (void)reg;
    for (size_t i = 0; i < positions.size() && i < velocities.size(); ++i)
    {
        auto const &pos = positions[i];
        auto const &vel = velocities[i];

        if (pos.has_value() && vel.has_value())
        {
            positions[i].value().x = (pos.value().x + vel.value().vx);
            positions[i].value().y = (pos.value().y + vel.value().vy);
        }
    }
}

#endif /* !POSITION_SYSTEM_HPP_ */
