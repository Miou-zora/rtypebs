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
#include "PrefabManager.hpp"

void shoot_system(registry &reg,
                  sparse_array<component::shooter> &shooters)
{
    (void)reg;
    for (auto &&[index, shooter] : indexed_zipper(shooters))
    {
        shooter.value().timer += reg.get_delta_time();
        if (shooter.value().timer >= shooter.value().cooldown)
        {
            shooter.value().timer -= shooter.value().cooldown;
            entity_t proj = PrefabManager::get_instance().Instantiate(shooter.value().projectileName, reg);
            if (reg.get_components<component::position>()[index].has_value() &&
                reg.get_components<component::position>()[proj].has_value())
            {
                reg.get_components<component::position>()[proj].value().Position = reg.get_components<component::position>()[index].value().Position;
            }
        }
    }
}
