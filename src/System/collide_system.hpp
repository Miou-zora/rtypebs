/*
** EPITECH PROJECT, 2023
** rtypebs [WSL : Ubuntu]
** File description:
** collide_system
*/

#pragma once

#include "registry.hpp"
#include "collider.hpp"
#include "position.hpp"
#include "indexed_zipper.hpp"
#include "EventManager.hpp"

void collide_system(registry &reg,
                    sparse_array<component::collider> &colliders,
                    sparse_array<component::position> const &positions)
{
    for (auto &&[index_first, hb_first, pos_first] : indexed_zipper(colliders, positions))
    {
        hb_first.value().collided_with.clear();
        for (auto &&[index_second, hb_second, pos_second] : indexed_zipper(colliders, positions))
        {
            if (index_first == index_second)
                continue;
            if (pos_first.value().Position.x < pos_second.value().Position.x + hb_second.value().width &&
                pos_first.value().Position.x + hb_first.value().width > pos_second.value().Position.x &&
                pos_first.value().Position.y < pos_second.value().Position.y + hb_second.value().height &&
                pos_first.value().Position.y + hb_first.value().height > pos_second.value().Position.y)
            {
                hb_first.value().collided_with.push_back(reg.entity_from_index(index_second));
                // ecs::EventManager::getInstance().emit<COLLISION>({reg.entity_from_index(index_first), reg.entity_from_index(index_second)});
            }
        }
    }
}
