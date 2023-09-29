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

class pattern_movement
{
public:
    pattern_movement(){};
    virtual ~pattern_movement(){};

    virtual vector<float> get_last_direction() = 0;
    virtual void update(float dt) = 0;
    virtual void reset() = 0;
    virtual bool is_finished() = 0;
};

class linear_movement : virtual public pattern_movement
{
public:
    linear_movement(vector<float> target, float speed = 1) : _target(target), _direction(target.normalized() * speed), _actual_position(0, 0){};
    linear_movement(float time, vector<float> target) : _target(target), _direction(target / time), _actual_position(0, 0){};
    linear_movement(const linear_movement &other) : _target(other._target), _direction(other._direction), _actual_position(other._actual_position), _last_direction(other._last_direction) {};

    vector<float> get_last_direction() override
    {
        return (_last_direction);
    }

    void update(float dt) override
    {
        if (_actual_position >= _target) {
            _last_direction = vector<float>(0, 0);
        } if (_actual_position + _direction * dt >= _target) {
            _actual_position = _target;
            _last_direction = _target - _actual_position;
        } else {
            _actual_position += _direction * dt;
            _last_direction = _direction * dt;
        }
    }
    void reset() override
    {
        _actual_position = 0;
        _last_direction = vector<float>(0, 0);
    }
    bool is_finished() override
    {
        return (_actual_position >= _target);
    }

protected:
    vector<float> _target;
    vector<float> _direction;
    vector<float> _actual_position;
    vector<float> _last_direction;
};

class infinite_linear_movement : virtual public linear_movement
{
public:
    infinite_linear_movement(vector<float> target, float speed = 1) : linear_movement(target, speed) {};
    infinite_linear_movement(float time, vector<float> target) : linear_movement(time, target) {};

    void update(float dt) override
    {
        _actual_position += _direction * dt;
        _last_direction = _direction * dt;
    }

    bool is_finished() override
    {
        return (false);
    }
};

class reverse_linear_movement : virtual public linear_movement
{
public:
    reverse_linear_movement(vector<float> target, float speed = 1) : linear_movement(target, speed) {};
    reverse_linear_movement(float time, vector<float> target) : linear_movement(time, target) {};
    reverse_linear_movement(const reverse_linear_movement &other) : linear_movement(other), reverse(other.reverse) {};

    vector<float> get_last_direction() override
    {
        return (_last_direction);
    }

    void update(float dt) override
    {
        if (!reverse)
        {
            if (_actual_position >= _target) {
                _last_direction = vector<float>(0, 0);
            } if (_actual_position + _direction * dt >= _target)
            {
                _actual_position = _target;
                reverse = !reverse;
                _direction = -_direction;
                _last_direction = _target - _actual_position;
            }
            else {
                _actual_position += _direction * dt;
                _last_direction = _direction * dt;
            }
        }
        else
        {
            if (_actual_position.x && _actual_position.y == 0) {
                _last_direction = vector<float>(0, 0);
            }
            if (std::signbit((_actual_position + _direction * dt).x) != std::signbit(_actual_position.x) ||
                std::signbit((_actual_position + _direction * dt).y) != std::signbit(_actual_position.y))
            {
                _actual_position = 0;
                reverse = !reverse;
                _direction = -_direction;
                _last_direction = _direction * dt;
            }
            else {
                _actual_position += _direction * dt;
                _last_direction = _direction * dt;
            }
        }
    }
    void reset() override
    {
        _actual_position = 0;
        _last_direction = vector<float>(0, 0);
    }

    bool is_finished() override
    {
        return (false);
    }

private:
    bool reverse = false;
};

namespace component
{
    class path : virtual public pattern_movement
    {
    private:
        using list_of_pattern = std::vector<std::shared_ptr<pattern_movement>>;

    public:
        path(float speed = 1, list_of_pattern _path = list_of_pattern()) : path_list(_path), _speed(speed){};

        path(const path &other) : path_list(other.path_list), _speed(other._speed){};

        void add_pattern(std::shared_ptr<pattern_movement> pattern)
        {
            if (pattern)
                path_list.push_back(pattern);
        }

        void add_pattern(list_of_pattern pattern)
        {
            for (auto &&pat : pattern)
                add_pattern(pat);
        }

        template <class Pattern, typename... Args>
        path &add_pattern(Args... args)
        {
            add_pattern(std::make_shared<Pattern>(args...));
            return (*this);
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

        vector<float> get_last_direction()
        {
            if (path_list.empty())
            {
                return (vector<float>(0, 0));
            }
            return (path_list.front()->get_last_direction());
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
