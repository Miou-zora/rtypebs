/*
** EPITECH PROJECT, 2023
** rtypebs [WSL : Ubuntu]
** File description:
** vector
*/

#pragma once

#include <cmath>
#include <iostream>

template <typename T>
class vector
{
public:
    vector(T _x, T _y) : x(_x), y(_y){};
    vector(const vector<T> &other) : x(other.x), y(other.y){};
    vector(void) : x(0), y(0) {};
    ~vector() = default;

    vector<T> operator+(const vector<T> &other) const
    {
        return (vector<T>(x + other.x, y + other.y));
    }

    vector<T> operator-(const vector<T> &other) const
    {
        return (vector<T>(x - other.x, y - other.y));
    }

    vector<T> operator*(const vector<T> &other) const
    {
        return (vector<T>(x * other.x, y * other.y));
    }

    vector<T> operator/(const vector<T> &other) const
    {
        return (vector<T>(x / other.x, y / other.y));
    }

    vector<T> operator*(const T &other) const
    {
        return (vector<T>(x * other, y * other));
    }

    vector<T> operator/(const T &other) const
    {
        return (vector<T>(x / other, y / other));
    }

    vector<T> &operator+=(const vector<T> &other)
    {
        x += other.x;
        y += other.y;
        return (*this);
    }

    vector<T> &operator-=(const vector<T> &other)
    {
        x -= other.x;
        y -= other.y;
        return (*this);
    }

    vector<T> &operator*=(const vector<T> &other)
    {
        x *= other.x;
        y *= other.y;
        return (*this);
    }

    vector<T> &operator/=(const vector<T> &other)
    {
        x /= other.x;
        y /= other.y;
        return (*this);
    }

    vector<T> &operator*=(const T &other)
    {
        x *= other;
        y *= other;
        return (*this);
    }

    vector<T> &operator/=(const T &other)
    {
        x /= other;
        y /= other;
        return (*this);
    }

    vector<T> &operator=(const vector<T> &other)
    {
        x = other.x;
        y = other.y;
        return (*this);
    }

    vector<T> &operator=(const T &other)
    {
        x = other;
        y = other;
        return (*this);
    }

    bool operator==(const vector<T> &other) const
    {
        return (x == other.x && y == other.y);
    }

    bool operator<(const vector<T> &other) const
    {
        return (get_length() < other.get_length());
    }

    bool operator<=(const vector<T> &other) const
    {
        return (get_length() <= other.get_length());
    }

    bool operator>(const vector<T> &other) const
    {
        return (get_length() > other.get_length());
    }

    bool operator>=(const vector<T> &other) const
    {
        return (get_length() >= other.get_length());
    }

    bool operator!=(const vector<T> &other) const
    {
        return (x != other.x || y != other.y);
    }

    T get_length() const
    {
        return (std::sqrt(std::pow(x, 2) + std::pow(y, 2)));
    }

    vector<T> normalized() const
    {
        return (vector<T>(x / get_length(), y / get_length()));
    }

    T distance(const vector<T> &other) const
    {
        return (std::sqrt(std::pow(x - other.x, 2) + std::pow(y - other.y, 2)));
    }

    static vector<T> getVector(const vector<T> &a, const vector<T> &b)
    {
        return (vector<T>(b.x - a.x, b.y - a.y));
    }

    T x;
    T y;
};

template <typename T>
vector<T> lerp(vector<T> a, vector<T> b, float f)
{
    return (a + f * (b - a));
}

template <typename T>
std::ostream &operator<<(std::ostream &os, const vector<T> &other)
{
    os << "x: " << other.x << " y: " << other.y;
    return (os);
}
template<typename T>
vector<T> operator/(const T &other, const vector<T> &vec)
{
    std::cout << vec << std::endl;
    return (vector<T>(other / vec.get_length(), other / vec.get_length()));
}

template<typename T>
vector<T> operator*(const T &other, const vector<T> &vec)
{
    return (vector<T>(other * vec.get_length(), other * vec.get_length()));
}

template<typename T>
vector<T> operator+(const T &other, const vector<T> &vec)
{
    return (vector<T>(other + vec.get_length(), other + vec.get_length()));
}

template<typename T>
vector<T> operator-(const T &other, const vector<T> &vec)
{
    return (vector<T>(other - vec.get_length(), other - vec.get_length()));
}

template<typename T>
vector<T> operator-(const vector<T> &vec)
{
    return (vector<T>(-vec.x, -vec.y));
}
