/*
** EPITECH PROJECT, 2023
** rtypebs [WSL : Ubuntu]
** File description:
** collider
*/

#pragma once

#include "entity_t.hpp"
#include <vector>

// struct COLLISION
// {
//     entity_t entity1;
//     entity_t entity2;
// };

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

            bool collideWith(const vector<int> &pos, const vector<float> &offset) const
            {
                if (pos.x >= offset.x && pos.x <= offset.x + this->width &&
                    pos.y >= offset.y && pos.y <= offset.y + this->height)
                    return true;
                return false;
            }

            bool collideWith(const vector<float> &offsetThis, const collider &other, const vector<float> &offsetOther) const
            {
                if (offsetThis.x < offsetOther.x + other.width &&
                    offsetThis.x + this->width > offsetOther.x &&
                    offsetThis.y < offsetOther.y + other.height &&
                    offsetThis.y + this->height > offsetOther.y)
                {
                    return true;
                }
                return false;
            }
    };
};
