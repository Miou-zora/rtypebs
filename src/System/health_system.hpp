/*
** EPITECH PROJECT, 2023
** rtypebs [WSL : Ubuntu]
** File description:
** health_system
*/

#pragma once

#include "registry.hpp"
#include "health.hpp"
#include "indexed_zipper.hpp"

void health_system(registry &reg,
                   sparse_array<component::health> &healths)
{
    (void)reg;
    for (auto &&[index, health] : indexed_zipper(healths))
    {
        if (health.value().value <= 0)
        {
            reg.kill_entity(reg.entity_from_index(index));
        }
    }
}
