/*
** EPITECH PROJECT, 2023
** B-CPP-500-NAN-5-1-bsrtype-alexandre.franquet
** File description:
** controllable
*/

#ifndef CONTROLLABLE_HPP_
#define CONTROLLABLE_HPP_

#include <functional>

namespace component
{
    struct controllable
    {
        std::function<bool(void) /* Why we can't make it const ? */> is_key_up_pressed;
        std::function<bool(void) /* Why we can't make it const ? */> is_key_down_pressed;
        std::function<bool(void) /* Why we can't make it const ? */> is_key_left_pressed;
        std::function<bool(void) /* Why we can't make it const ? */> is_key_right_pressed;
        std::function<bool(void) /* Why we can't make it const ? */> is_key_shoot_pressed;
        float speed = 300;
    };
};

#endif /* !CONTROLLABLE_HPP_ */
