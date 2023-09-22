/*
** EPITECH PROJECT, 2023
** rtypebs [WSL : Ubuntu]
** File description:
** damage_system
*/

#pragma once

#include "registry.hpp"
#include "collider.hpp"
#include "health.hpp"
#include "damage.hpp"
#include "zipper.hpp"

void damage_system(registry &reg,
                    sparse_array<component::collider> const &colliders,
                    sparse_array<component::health> &healths)
{
    (void)reg;
    for (auto &&[collider, health] : zipper(colliders, healths))
    {
        for (auto &collide_with : collider.value().collided_with)
        {
            if (reg.get_components<component::damage>()[collide_with].has_value())
            {
                health.value().Health -= reg.get_components<component::damage>()[collide_with].value().Damage;
                reg.kill_entity(collide_with);
            }
        }
    }
}
