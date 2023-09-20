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
        vel.value().vx = (cont.value().is_key_right_pressed() - cont.value().is_key_left_pressed());
        vel.value().vy = (cont.value().is_key_down_pressed() - cont.value().is_key_up_pressed());
    }
}

#endif /* !CONTROL_SYSTEM_HPP_ */
