/*
** EPITECH PROJECT, 2023
** rtypebs [WSL : Ubuntu]
** File description:
** shooter
*/

#pragma once

#include "prefab.hpp"

namespace component
{
    struct shooter {
        shooter(prefab &&_projectile, float _cooldown = 50) : cooldown(_cooldown), projectile(_projectile) {};
        float cooldown;
        float timer = 0;
        prefab projectile;
    };
};
