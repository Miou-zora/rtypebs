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
    class collider
    {
        public:
            collider(int _width = 0, int _height = 0) : width(_width), height(_height) {};
            virtual ~collider() = default;
            int width;
            int height;
            std::vector<entity_t> collided_with;
    };
};
