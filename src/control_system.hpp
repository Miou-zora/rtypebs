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

void control_system(registry &reg)
{
    auto &controllables = reg.get_components<component::controllable>();
    auto &velocities = reg.get_components<component::velocity>();

    for (size_t i = 0; i < controllables.size() && i < velocities.size(); ++i)
    {
        auto &cont = controllables[i];
        auto &vel = velocities[i];

        if (cont.has_value() && vel.has_value()) {
            velocities[i].value().vx = (cont.value().is_key_right_pressed() - cont.value().is_key_left_pressed());
            velocities[i].value().vy = (cont.value().is_key_down_pressed() - cont.value().is_key_up_pressed());
        }
    }
}

#endif /* !CONTROL_SYSTEM_HPP_ */
