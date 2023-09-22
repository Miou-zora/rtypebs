/*
** EPITECH PROJECT, 2023
** B-CPP-500-NAN-5-1-bsrtype-alexandre.franquet
** File description:
** position
*/

#ifndef POSITION_HPP_
#define POSITION_HPP_

namespace component
{
    struct position {
        position(float _x, float _y) : x(_x), y(_y) {};
        float x;
        float y;
    };
};

#endif /* !POSITION_HPP_ */
