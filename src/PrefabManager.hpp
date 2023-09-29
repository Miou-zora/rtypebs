/*
** EPITECH PROJECT, 2023
** rtypebs [WSL : Ubuntu]
** File description:
** PrefabManager
*/

#pragma once

#include <unordered_map>
#include <string>
#include "prefab.hpp"
#include <memory>

class PrefabManager {
    // Singleton part
    private:
        PrefabManager() = default;
    public:
        static PrefabManager &get_instance()
        {
            if (!m_instance)
                m_instance = new PrefabManager();
            return (*m_instance);
        }
    private:
        static PrefabManager *m_instance;

    public:
        ~PrefabManager();

        prefab &CreatePrefab(const std::string &name)
        {
            _prefabs[name] = std::make_unique<prefab>();
            return (*_prefabs[name]);
        }

        template <class Component, typename... Args>
        prefab &AddComponent(const std::string &name, Args... args)
        {
            if (_prefabs.find(name) == _prefabs.end())
                throw std::runtime_error("Prefab not found"); // TODO: throw a better exception
            return (_prefabs.at(name)->add_component<Component>(args...));
        }

        entity_t Instantiate(const std::string &name, registry &reg) const
        {
            if (_prefabs.find(name) == _prefabs.end())
                throw std::runtime_error("Prefab not found"); // TODO: throw a better exception
            return (_prefabs.at(name)->instantiate(reg));
        }

    private:
        std::unordered_map<std::string, std::unique_ptr<prefab>> _prefabs;
};

inline PrefabManager *PrefabManager::m_instance = nullptr;
