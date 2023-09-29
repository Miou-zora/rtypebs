/*
** EPITECH PROJECT, 2023
** rtypebs [WSL : Ubuntu]
** File description:
** player_shoot_system
*/

#pragma once

#include "registry.hpp"
#include "playerShooter.hpp"
#include "indexed_zipper.hpp"
#include "position.hpp"
#include "PrefabManager.hpp"
#include "controllable.hpp"

void player_shoot_system(registry &reg,
                  sparse_array<component::playerShooter> &shooters,
                  sparse_array<component::controllable> &controllables)
{
    (void)reg;
    for (auto &&[index, shooter, control] : indexed_zipper(shooters, controllables))
    {
        shooter.value().timer += reg.get_delta_time();
        shooter.value().playerWantToShoot = control.value().is_key_shoot_pressed();
        if (shooter.value().canShoot())
        {
            shooter.value().reset();
            entity_t proj = PrefabManager::get_instance().Instantiate(shooter.value().projectileName, reg);
            if (reg.has_component<component::position>(reg.entity_from_index(index)) &&
                reg.has_component<component::position>(reg.entity_from_index(proj)))
            {
                reg.get_components<component::position>()[proj].value().Position = reg.get_components<component::position>()[index].value().Position;
            }
        }
    }
}
