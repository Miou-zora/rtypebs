/*
** EPITECH PROJECT, 2023
** rtypebs [WSL : Ubuntu]
** File description:
** health
*/

#pragma once

namespace component
{
    struct health
    {
        health(int _value) : value(_value){};
        int value;
    };
}
