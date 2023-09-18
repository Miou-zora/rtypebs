/*
** EPITECH PROJECT, 2023
** B-CPP-500-NAN-5-1-bsrtype-alexandre.franquet
** File description:
** position
*/

#ifndef POSITION_HPP_
#define POSITION_HPP_

namespace component {
class position
{
public:
    position(int _x, int _y) : x(_x), y(_y) {}

    int x;
    int y;
};
};

#endif /* !POSITION_HPP_ */
