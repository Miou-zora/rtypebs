/*
** EPITECH PROJECT, 2023
** B-CPP-500-NAN-5-1-bsrtype-alexandre.franquet
** File description:
** registry
*/

#ifndef REGISTRY_HPP_
#define REGISTRY_HPP_

#include "sparse_array.hpp"
#include "entity_t.hpp"
#include "assets_manager.hpp"
#include <unordered_map>
#include <typeindex>
#include <any>
#include <functional>
#include <chrono>

class registry
{
private:
    struct component_t
    {
        std::any list_of_instances;
        std::function<void(registry &, entity_t const &)> destructor;
    };

public:
    registry() {}
    ~registry() {}

    template <class Component>
    sparse_array<Component> &register_component()
    {
        _components[std::type_index(typeid(Component))] = component_t{
            sparse_array<Component>(),
            [](registry &reg, entity_t const &entity)
            {
                sparse_array<Component> &arr = reg.get_components<Component>();
                arr.erase(entity);
            }};
        return (std::any_cast<sparse_array<Component> &>(_components[std::type_index(typeid(Component))].list_of_instances));
    }

    template <class Component>
    sparse_array<Component> &get_components()
    {
        return (std::any_cast<sparse_array<Component> &>(_components[std::type_index(typeid(Component))].list_of_instances));
    }

    template <class Component>
    sparse_array<Component> const &get_components() const
    {
        return (std::any_cast<sparse_array<Component> const &>(_components.at(std::type_index(typeid(Component))).list_of_instances));
    }

    template <class Component>
    bool has_component(entity_t const &e) const
    {
        if (get_components<Component>().size() > e)
            if (get_components<Component>()[e].has_value())
                return (true);
        return (false);
    }

    entity_t spawn_entity()
    {
        static int id = 0;

        if (_dead_entities.empty())
        {
            return (entity_t(id++));
        }

        entity_t e = _dead_entities.back();
        _dead_entities.pop_back();
        return (e);
    }

    entity_t entity_from_index(std::size_t idx)
    {
        return (entity_t(idx));
    }

    void kill_entity(entity_t const &e)
    {
        for (auto &component : _components)
        {
            component.second.destructor(*this, e);
        }
        _dead_entities.push_back(e);
    }

    template <typename Component>
    typename sparse_array<Component>::reference_type add_component(entity_t const &to,
                                                                   Component &&c)
    {
        sparse_array<Component> &arr = get_components<Component>();
        arr.insert_at(to, std::forward<Component>(c));
        return (arr[to]);
    }

    template <typename Component, typename... Params>
    typename sparse_array<Component>::reference_type emplace_component(entity_t const &to, Params &&...p)
    {
        sparse_array<Component> &arr = get_components<Component>();
        arr.emplace_at(to, std::in_place, std::forward<Params>(p)...);
        return (arr[to]);
    }

    template <typename Component>
    void remove_component(entity_t const &from)
    {
        sparse_array<Component> &arr = get_components<Component>();
        arr.erase(from);
    }

    template <class... Components, typename Function>
    void add_system(Function &&f)
    {
        _systems.push_back([f](registry &reg)
                           { f(reg, reg.get_components<Components>()...); });
    }
    // or
    template <class... Components, typename Function>
    void add_system(Function const &f)
    {
        _systems.push_back([f](registry &reg)
                           { f(reg, reg.get_components<Components>()...); });
    }

    void run_systems()
    {
        for (auto &system : _systems)
        {
            system(*this);
        }
    }

    assets_manager &get_assets_manager()
    {
        return (_assets_manager);
    }

    float get_delta_time() const
    {
        return (_delta_time);
    }

    void update_delta_time()
    {
        static std::chrono::time_point<std::chrono::system_clock> last = std::chrono::system_clock::now();
        std::chrono::time_point<std::chrono::system_clock> now = std::chrono::system_clock::now();
        std::chrono::duration<float> elapsed_seconds = now - last;
        _delta_time = elapsed_seconds.count();
        last = now;
    }

private:
    std::unordered_map<std::type_index, component_t> _components;
    std::vector<std::function<void(registry &)>> _systems;
    std::vector<entity_t> _dead_entities;
    assets_manager _assets_manager;
    float _delta_time;
};

#endif /* !REGISTRY_HPP_ */
