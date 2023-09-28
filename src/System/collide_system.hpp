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

class collide_system
{
public:
    collide_system() = default;
    ~collide_system() = default;
    void operator()(registry &reg,
                    sparse_array<component::collider> &colliders,
                    sparse_array<component::position> const &positions) const
    {
        for (auto &&[index_first, col_first, pos_first] : indexed_zipper(colliders, positions))
        {
            col_first.value().collided_with.clear();
            for (auto &&[index_second, col_second, pos_second] : indexed_zipper(colliders, positions))
            {
                if (index_first == index_second)
                    continue;
                if (collideWith(col_second.value(), pos_second.value().Position, col_first.value(), pos_first.value().Position))
                {
                    col_first.value().collided_with.push_back(reg.entity_from_index(index_second));
                }
            }
        }
    }

    static bool collideWith(const component::collider &col, const vector<int> &pos, const vector<float> &offset)
    {
        if (pos.x >= offset.x && pos.x <= offset.x + col.width &&
            pos.y >= offset.y && pos.y <= offset.y + col.height)
            return true;
        return false;
    };

    static bool collideWith(const component::collider &colA, const vector<float> &offsetA, const component::collider &colB, const vector<float> &offsetB)
    {
        if (offsetA.x < offsetB.x + colB.width &&
            offsetA.x + colA.width > offsetB.x &&
            offsetA.y < offsetB.y + colB.height &&
            offsetA.y + colA.height > offsetB.y)
        {
            return true;
        }
        return false;
    };
};
