/*
** EPITECH PROJECT, 2023
** B-CPP-500-NAN-5-1-bsrtype-alexandre.franquet
** File description:
** test
*/

#ifndef TEST_HPP_
#define TEST_HPP_

#include <optional>
#include <vector>
#include <memory>
#include <iostream>

template <typename Component, class Allocator = std::allocator<std::optional<Component>>>
class sparse_array
{
public:
    using value_type = std::optional<Component>; // optional component type
    using reference_type = value_type &;
    using const_reference_type = value_type const &;
    using container_t = std::vector<value_type, Allocator>; // optionally add your allocator template here.
    using size_type = typename container_t ::size_type;
    using iterator = typename container_t ::iterator;
    using const_iterator = typename container_t ::const_iterator;

public:
    sparse_array() = default;
                       // You can add more constructors .
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

    reference_type insert_at(size_type pos, Component const &other) // TODO: use allocator traits and remove component if not empty
    {
        if (_data.size() <= pos) {
            _data.resize(pos + 1);
        } else {
            if (_data[pos].has_value()) {
                _data[pos].reset();
            }
        }
        _data[pos] = other;
        return (_data[pos]);
    }

    reference_type insert_at(size_type pos, Component &&other) // TODO: use allocator traits
    {
        if (_data.size() <= pos) {
            _data.resize(pos + 1);
        } else {
            if (_data[pos].has_value()) {
                _data[pos].reset();
            }
        }
        _data[pos] = std::move(other);
        return (_data[pos]);
    }

    template <class... Params>
    reference_type emplace_at(size_type pos, Params &&...other) // TODO: Axel, check this
    {
        _data.emplace(_data.begin() + pos, std::forward<Params>(other)...);
        return (_data[pos]);
    }

    void erase(size_type pos) // TODO: use allocator traits
    {
        if (_data.size() <= pos)
            return;
        _data[pos].reset();
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

#endif /* !TEST_HPP_ */
