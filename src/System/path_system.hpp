/*
** EPITECH PROJECT, 2023
** rtypebs [WSL : Ubuntu]
** File description:
** path_system
*/

#pragma once

#include "registry.hpp"
#include "path.hpp"
#include "velocity.hpp"
#include "indexed_zipper.hpp"

void path_system(registry &reg,
                 sparse_array<component::velocity> &velocities,
                 sparse_array<component::path> &paths,
                 sparse_array<component::position> &positions)
{
    (void)reg;
    float deltaTime = reg.get_delta_time();
    for (auto &&[i, vel, path, pos] : indexed_zipper(velocities, paths, positions))
    {
        if (path.value().list_of_points.empty())
            continue;
        component::path::Point &current_point = path.value().list_of_points[0];
        vector<float> vectorToNextPoint = vector<float>::getVector(pos.value().Position, current_point.first);
        if (current_point.second == component::path::Referential::Entity)
            vectorToNextPoint = current_point.first;
        if (current_point.first.distance(pos.value().Position) >= (vectorToNextPoint.normalized() * path.value().speed * deltaTime).get_length())
        {
            vel.value().Velocity = vectorToNextPoint.normalized() * path.value().speed * deltaTime;
            if (current_point.second == component::path::Referential::Entity)
                current_point.first -= vel.value().Velocity;
        }
        else
        {
            if (path.value().list_of_points.size() == 1) {
                vel.value().Velocity = vectorToNextPoint;
                if (path.value().destroyAtEnd) {
                    reg.kill_entity(reg.entity_from_index(i));
                    continue;
                }
            } else {
                vector<float> overflowValue = (current_point.first - pos.value().Position).normalized() * path.value().speed * deltaTime - vectorToNextPoint;
                vectorToNextPoint += vector<float>::getVector(path.value().list_of_points[0].first, path.value().list_of_points[1].first).normalized() * overflowValue.get_length();
                vel.value().Velocity = vectorToNextPoint;
            }
            path.value().list_of_points.erase(path.value().list_of_points.begin());
        }
        if (component::path::Referential::Entity == current_point.second && current_point.first.get_length() <= 1)
            path.value().list_of_points.erase(path.value().list_of_points.begin());
        if (component::path::Referential::World == current_point.second && (current_point.first + vel.value().Velocity).distance(pos.value().Position) <= 1)
            path.value().list_of_points.erase(path.value().list_of_points.begin());
        if (path.value().list_of_points.empty() && path.value().destroyAtEnd)
            reg.kill_entity(reg.entity_from_index(i));
    }
}
