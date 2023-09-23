/*
** EPITECH PROJECT, 2023
** rtypebs [WSL : Ubuntu]
** File description:
** collider
*/

#pragma once

#include "entity_t.hpp"
#include <vector>

namespace component
{
    struct collider
    {
        collider(int _width, int _height) : width(_width), height(_height) {};
        int width;
        int height;
        std::vector<entity_t> collided_with;
    };
};