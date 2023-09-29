/*
** EPITECH PROJECT, 2023
** rtypebs [WSL : Ubuntu]
** File description:
** spawner
*/

#pragma once

#include <vector>
#include <string>

namespace component
{
    class Spawner
    {
    private:
        using prefabName = std::string;
        using entityWaitTime = float;
        using entitySpawnInfo = std::pair<entityWaitTime, prefabName>;
    public:
        Spawner() = default;
        ~Spawner() = default;

        std::vector<entitySpawnInfo> _spawnList;
    };
}
