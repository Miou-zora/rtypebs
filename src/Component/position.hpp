/*
** EPITECH PROJECT, 2023
** B-CPP-500-NAN-5-1-bsrtype-alexandre.franquet
** File description:
** position
*/

#pragma once

#include "vector.hpp"

namespace component
{
    struct position {
        position(float x, float y) : Position(x, y) {};
        position(const vector<float> &pos) : Position(pos) {};
        position() : Position(0, 0) {};
        vector<float> Position;
    };
};
