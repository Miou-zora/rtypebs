/*
** EPITECH PROJECT, 2023
** rtypebs [WSL : Ubuntu]
** File description:
** hurtbox
*/

#pragma once

namespace component
{
    struct hurtbox
    {
        hurtbox(int _width, int _height) : width(_width), height(_height) {};
        int width;
        int height;
    };
};
