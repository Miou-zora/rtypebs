/*
** EPITECH PROJECT, 2023
** rtypebs [WSL : Ubuntu]
** File description:
** projectile_system
*/

#pragma once

#include "registry.hpp"
#include "collider.hpp"
#include "projectile.hpp"
#include "indexed_zipper.hpp"

void projectile_system(registry &reg,
                    sparse_array<component::collider> &colliders,
                    sparse_array<component::projectile> const &projectiles)
{
    (void)reg;
    for (auto &&[index, collider, projectile] : indexed_zipper(colliders, projectiles))
    {
        if (!collider.value().collided_with.empty())
        {
            reg.kill_entity(reg.entity_from_index(index));
        }
    }

}
