/*
** EPITECH PROJECT, 2023
** rtypebs [WSL : Ubuntu]
** File description:
** path
*/

#pragma once

#include <vector>
#include <memory>
#include <ctime>
#include <cmath>
#include "vector.hpp"

namespace component
{
    class pattern_movement
    {
    public:
        pattern_movement(){};
        virtual ~pattern_movement(){};

        virtual vector<float> get_direction() = 0;
        virtual void update(float dt) = 0;
        virtual void reset() = 0;
        virtual bool is_finished() = 0;
    };

    class linear_movement : virtual public pattern_movement
    {
    public:
        linear_movement(vector<float> target, float speed) : _direction(target / speed) {};

        linear_movement(float time, vector<float> target)
        {
            _direction = target / (target.get_length() / time);
        };

        vector<float> get_direction() override
        {
            return (vector<float>(_direction));
        }
        void update(float dt) override
        {
            if (_actual_position == _direction)
                return;
            if (_actual_position + _direction * dt > _direction)
                _actual_position = _direction;
            else
                _actual_position += _direction * dt;
        }
        void reset() override
        {
            _actual_position = 0;
        }
        bool is_finished() override
        {
            return (_actual_position >= _direction);
        }
    private:
        vector<float> _direction;
        vector<float> _actual_position;
    };

    class path : virtual public pattern_movement
    {
    private:
        using list_of_pattern = std::vector<std::shared_ptr<pattern_movement>>;

    public:
        path(float speed = 1, list_of_pattern _path = list_of_pattern()) : path_list(_path), _speed(speed){};

        void add_pattern(std::shared_ptr<pattern_movement> pattern)
        {
            if (pattern)
                path_list.push_back(pattern);
        }

        void update(float dt)
        {
            if (path_list.empty())
                return;
            if (path_list.front()->is_finished())
                path_list.erase(path_list.begin());
            if (path_list.empty())
                return;
            path_list.front()->update(dt * _speed);
        }

        vector<float> get_direction()
        {
            if (path_list.empty())
                return (vector<float>(0, 0));
            return (path_list.front()->get_direction());
        }

        void reset()
        {
            for (auto &&pattern : path_list)
                pattern->reset();
        }

        bool is_finished()
        {
            return (path_list.empty());
        }

    private:
        list_of_pattern path_list;
        float _speed;
    };
}
