/*
** EPITECH PROJECT, 2023
** rtypebs [WSL : Ubuntu]
** File description:
** collider
*/

#pragma once

#include "entity_t.hpp"
#include <vector>
#include "vector.hpp"

namespace component
{
    class collider
    {
        public:
            collider(int _width = 0, int _height = 0) : width(_width), height(_height) {};
            collider(const collider &other) : width(other.width), height(other.height) {};
            collider(const vector<float> &size) : width(size.x), height(size.y) {};
            virtual ~collider() = default;
            int width;
            int height;
            std::vector<entity_t> collided_with;
    };
};
