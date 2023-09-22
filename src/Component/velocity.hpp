/*
** EPITECH PROJECT, 2023
** B-CPP-500-NAN-5-1-bsrtype-alexandre.franquet
** File description:
** velocity
*/

#ifndef VELOCITY_HPP_
#define VELOCITY_HPP_

namespace component
{
    struct velocity {
        velocity(float _vx, float _vy) : vx(_vx), vy(_vy) {};
        float vx;
        float vy;
    };
};

#endif /* !VELOCITY_HPP_ */
