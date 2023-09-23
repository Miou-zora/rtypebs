/*
** EPITECH PROJECT, 2023
** B-CPP-500-NAN-5-1-bsrtype-alexandre.franquet
** File description:
** velocity
*/

#pragma once

#include "vector.hpp"

namespace component
{
    struct velocity {
        velocity(float x, float y) : Velocity(x, y) {};
        velocity(const vector<float> &pos) : Velocity(pos) {};
        velocity() : Velocity(0, 0) {};
        vector<float> Velocity;
    };
};
