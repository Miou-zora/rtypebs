/*
** EPITECH PROJECT, 2023
** rtypebs [WSL : Ubuntu]
** File description:
** shoot_system
*/

#pragma once

#include "registry.hpp"
#include "shooter.hpp"
#include "indexed_zipper.hpp"

void shoot_system(registry &reg,
                  sparse_array<component::shooter> &shooters)
{
    (void)reg; // TODO: add delta time
    for (auto &&[index, shooter] : indexed_zipper(shooters))
    {
        shooter.value().timer += 1;
        if (shooter.value().timer >= shooter.value().cooldown)
        {
            shooter.value().timer = 0;
            entity_t proj = shooter.value().projectile.instantiate(reg);
            if (reg.get_components<component::position>()[index].has_value() &&
                reg.get_components<component::position>()[proj].has_value())
            {
                reg.get_components<component::position>()[proj].value().Position = reg.get_components<component::position>()[index].value().Position;
            }
        }
    }
}
