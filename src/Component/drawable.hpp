/*
** EPITECH PROJECT, 2023
** B-CPP-500-NAN-5-1-bsrtype-alexandre.franquet
** File description:
** drawable
*/

#ifndef DRAWABLE_HPP_
#define DRAWABLE_HPP_

#include <memory>
#include <raylib.h>
#include "vector.hpp"

namespace component
{
    struct drawable
    {
        drawable(Texture2D _drawable, float _scale = 1) : Drawable(_drawable), scale(_scale) {}
        Texture2D Drawable;
        float scale;
    };
};

#endif /* !DRAWABLE_HPP_ */
