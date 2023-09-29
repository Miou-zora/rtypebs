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
        shooter(const std::string &projectileName_, float _cooldown = 50) : cooldown(_cooldown), projectileName(projectileName_) {};
        float cooldown;
        float timer = 0;
        std::string projectileName;
    };
};
