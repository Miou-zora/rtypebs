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
        shooter(prefab &&projectile, float _cooldown = 50) : cooldown(_cooldown), projectile(projectile) {};
        float cooldown;
        float timer = 0;
        prefab projectile;
    };
};
