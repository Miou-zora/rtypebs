/*
** EPITECH PROJECT, 2023
** rtypebs [WSL : Ubuntu]
** File description:
** spawner_system
*/

#pragma once

#include "registry.hpp"
#include "spawner.hpp"
#include "zipper.hpp"
#include "PrefabManager.hpp"

class spawner_system
{
public:
    spawner_system() = default;
    ~spawner_system() = default;

    void operator()(registry &reg,
        sparse_array<component::Spawner> &spawners
    ) const
    {
        float deltaTime = 0.0f;
        for (auto &&[spawner] : zipper(spawners))
        {
            if (spawner.value()._spawnList.empty())
                continue;
            deltaTime = reg.get_delta_time();
            if (spawner.value()._spawnList[0].first <= deltaTime)
            {
                deltaTime -= spawner.value()._spawnList[0].first;
                PrefabManager::get_instance().Instantiate(spawner.value()._spawnList[0].second, reg);
                spawner.value()._spawnList.erase(spawner.value()._spawnList.begin());
                if (spawner.value()._spawnList.empty())
                    continue;
                spawner.value()._spawnList[0].first -= deltaTime;
            }
            else
                spawner.value()._spawnList[0].first -= deltaTime;
        }
    }

};
