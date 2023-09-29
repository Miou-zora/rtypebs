/*
** EPITECH PROJECT, 2023
** B-CPP-500-NAN-5-1-bsrtype-alexandre.franquet
** File description:
** control_system
*/

#ifndef CONTROL_SYSTEM_HPP_
#define CONTROL_SYSTEM_HPP_

#include "registry.hpp"
#include "controllable.hpp"
#include "velocity.hpp"
#include "zipper.hpp"

void control_system(registry &reg,
    sparse_array<component::controllable> const &controllables,
    sparse_array<component::velocity> &velocities)
{
    (void)reg;
    for (auto &&[cont, vel] : zipper(controllables, velocities))
    {
        vector<float> direction((cont.value().is_key_right_pressed() - cont.value().is_key_left_pressed()), (cont.value().is_key_down_pressed() - cont.value().is_key_up_pressed()));
        if (direction.get_length() != 0)
            vel.value().Velocity = direction.normalized() * cont.value().speed * reg.get_delta_time();
        else
            vel.value().Velocity = vector<float>(0, 0);
    }
}

#endif /* !CONTROL_SYSTEM_HPP_ */
