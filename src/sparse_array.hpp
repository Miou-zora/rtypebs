/*
** EPITECH PROJECT, 2023
** B-CPP-500-NAN-5-1-bsrtype-alexandre.franquet
** File description:
** test
*/

#pragma once

#include <vector>
#include <memory>
#include <iostream>
#include <optional>
#include <stdexcept>

template <typename Component, typename Allocator = std::allocator<std::optional<Component>>>
class sparse_array
{
public:
    using value_type = std::optional<Component>;
    using reference_type = value_type &;
    using const_reference_type = value_type const &;
    using container_t = std::vector<value_type, Allocator>;
    using size_type = typename container_t ::size_type;
    using iterator = typename container_t ::iterator;
    using const_iterator = typename container_t ::const_iterator;

public:
    sparse_array() = default;

    sparse_array(sparse_array const &other)
    {
        _data = other._data;
    }

    sparse_array(sparse_array &&other) noexcept
    {
        _data = std::move(other._data);
    }

    ~sparse_array() = default;

    sparse_array &operator=(sparse_array const &other)
    {
        _data = other._data;
    }

    sparse_array &operator=(sparse_array &&other) noexcept
    {
        _data = std::move(other._data);
    }

    reference_type operator[](size_t idx)
    {
        return (_data[idx]);
    }

    const_reference_type operator[](size_t idx) const
    {
        return (_data[idx]);
    }

    iterator begin()
    {
        return (_data.begin());
    }

    const_iterator begin() const
    {
        return (_data.begin());
    }

    const_iterator cbegin() const
    {
        return (_data.cbegin());
    }

    iterator end()
    {
        return (_data.end());
    }

    const_iterator end() const
    {
        return (_data.end());
    }

    const_iterator cend() const
    {
        return (_data.cend());
    }

    size_type size() const
    {
        return (_data.size());
    }

    reference_type insert_at(size_type pos, Component const &other)
    {
        Allocator alloc = _data.get_allocator();

        if (_data.size() <= pos) {
            _data.resize(pos + 1);
        }
        std::allocator_traits<Allocator>::destroy(alloc, std::addressof(_data[pos]));
        _data[pos] = other;
        return (_data[pos]);
    }

    reference_type insert_at(size_type pos, Component &&other)
    {
        Allocator alloc = _data.get_allocator();

        if (_data.size() <= pos) {
            _data.resize(pos + 1);
        }
        std::allocator_traits<Allocator>::destroy(alloc, std::addressof(_data[pos]));
        _data[pos] = std::move(other);
        return (_data[pos]);
    }

    template <class... Params>
    reference_type emplace_at(size_type pos, Params &&...other)
    {
        Allocator alloc = _data.get_allocator();

        if (_data.size() <= pos) {
            _data.resize(pos + 1);
        }
        std::allocator_traits<Allocator>::destroy(alloc, std::addressof(_data[pos]));
        std::allocator_traits<Allocator>::construct(alloc, std::addressof(_data[pos]), std::forward<Params>(other)...);
        return (_data[pos]);
    }

    void erase(size_type pos)
    {
        Allocator alloc = _data.get_allocator();

        if (_data.size() <= pos)
            throw std::out_of_range("sparse_array::erase");
        std::allocator_traits<Allocator>::destroy(alloc, std::addressof(_data[pos]));
        _data[pos] = std::nullopt;
    }

    size_type get_index(value_type const &other) const
    {
        if (!other.has_value())
            return (_data.size());
        for (size_type i = 0; i < _data.size(); i++) {
            if (std::addressof(_data[i]) == std::addressof(other)) {
                return (i);
            }
        }
        return (_data.size());
    }

private:
    container_t _data;
};
