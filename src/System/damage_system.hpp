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
#include "indexed_zipper.hpp"
#include "enemy.hpp"
#include "player.hpp"
#include "projectile.hpp"

void damage_system(registry &reg,
                    sparse_array<component::collider> const &colliders,
                    sparse_array<component::health> &healths)
{
    (void)reg;
    for (auto &&[index, collider, health] : indexed_zipper(colliders, healths))
    {
        for (auto &collide_with : collider.value().collided_with)
        {
            if (reg.get_components<component::damage>()[collide_with].has_value() &&
                (
                    ((reg.get_components<component::enemy>()[collide_with].has_value() &&
                    !reg.get_components<component::player>()[collide_with].has_value()) &&
                    (reg.get_components<component::player>()[index].has_value() &&
                    !reg.get_components<component::enemy>()[index].has_value())) ||
                    ((reg.get_components<component::player>()[collide_with].has_value() &&
                    !reg.get_components<component::enemy>()[collide_with].has_value()) &&
                    (reg.get_components<component::enemy>()[index].has_value() &&
                    !reg.get_components<component::player>()[index].has_value()))
                )
            )
            {
                health.value().value -= reg.get_components<component::damage>()[collide_with].value().value;
                std::cout << "Entity " << index << " took " << reg.get_components<component::damage>()[collide_with].value().value << " damage" << std::endl;
            }
        }
    }
}
