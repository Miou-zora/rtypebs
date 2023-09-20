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
    class velocity // TODO: transform this into a struct
    {
    public:
        velocity(int x, int y) : vx(x), vy(y) {}

        int vx;
        int vy;
    };
};

#endif /* !VELOCITY_HPP_ */
