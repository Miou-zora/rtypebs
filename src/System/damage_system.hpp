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
            if (reg.has_component<component::damage>(collide_with))
            {
                if ((reg.has_component<component::enemy>(reg.entity_from_index(index)) &&
                     reg.has_component<component::player>(collide_with)) ||
                    (reg.has_component<component::player>(reg.entity_from_index(index)) &&
                     reg.has_component<component::enemy>(collide_with)))
                {
                    std::cout << "Entity " << reg.entity_from_index(index) << " collided with " << collide_with << std::endl;
                    health.value().value -= reg.get_components<component::damage>()[collide_with].value().value;
                    if (reg.has_component<component::projectile>(collide_with))
                        reg.kill_entity(collide_with);
                }
            }
        }
    }
}
