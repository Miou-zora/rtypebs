/*
** EPITECH PROJECT, 2023
** rtypebs [WSL : Ubuntu]
** File description:
** test_sparse_array
*/

#include "sparse_array.hpp"

#include <gtest/gtest.h>

TEST(sparse_array, init)
{
    sparse_array<int> arr;
    EXPECT_EQ(arr.size(), 0);
}

TEST(sparse_array, insert_at)
{
    sparse_array<int> arr;

    // extends
    arr.insert_at(3, 42);
    EXPECT_EQ(arr.size(), 4);
    EXPECT_EQ(arr[0].has_value(), false);
    EXPECT_EQ(arr[1].has_value(), false);
    EXPECT_EQ(arr[2].has_value(), false);
    EXPECT_EQ(arr[3].value(), 42);

    // add value in empty place
    arr.insert_at(1, 21);
    EXPECT_EQ(arr.size(), 4);
    EXPECT_EQ(arr[0].has_value(), false);
    EXPECT_EQ(arr[1].value(), 21);
    EXPECT_EQ(arr[2].has_value(), false);
    EXPECT_EQ(arr[3].value(), 42);

    // modify value
    arr.insert_at(1, 84);
    EXPECT_EQ(arr.size(), 4);
    EXPECT_EQ(arr[0].has_value(), false);
    EXPECT_EQ(arr[1].value(), 84);
    EXPECT_EQ(arr[2].has_value(), false);
    EXPECT_EQ(arr[3].value(), 42);
}

TEST(sparse_array, emplace_at)
{
    class A
    {
    public:
        A(int _a, int _b) : a(_a), b(_b) {}
        int a;
        int b;
    };

    sparse_array<A> arr;

    // extends
    arr.emplace_at(3, std::in_place, 42, 21);
    EXPECT_EQ(arr.size(), 4);
    EXPECT_EQ(arr[0].has_value(), false);
    EXPECT_EQ(arr[1].has_value(), false);
    EXPECT_EQ(arr[2].has_value(), false);
    EXPECT_EQ(arr[3].value().a, 42);
    EXPECT_EQ(arr[3].value().b, 21);

    // add value in empty place
    arr.emplace_at(1, std::in_place, 21, 42);
    EXPECT_EQ(arr.size(), 4);
    EXPECT_EQ(arr[0].has_value(), false);
    EXPECT_EQ(arr[1].value().a, 21);
    EXPECT_EQ(arr[1].value().b, 42);
    EXPECT_EQ(arr[2].has_value(), false);
    EXPECT_EQ(arr[3].value().a, 42);
    EXPECT_EQ(arr[3].value().b, 21);

    // modify value
    arr.emplace_at(1, std::in_place, 84, 42);
    EXPECT_EQ(arr.size(), 4);
    EXPECT_EQ(arr[0].has_value(), false);
    EXPECT_EQ(arr[1].value().a, 84);
    EXPECT_EQ(arr[1].value().b, 42);
    EXPECT_EQ(arr[2].has_value(), false);
    EXPECT_EQ(arr[3].value().a, 42);
    EXPECT_EQ(arr[3].value().b, 21);

    // add value with move
    A value(1024, 2048);
    arr.emplace_at(0, std::move(value));
    EXPECT_EQ(arr.size(), 4);
    EXPECT_EQ(arr[0].value().a, 1024);
    EXPECT_EQ(arr[0].value().b, 2048);
    EXPECT_EQ(arr[1].value().a, 84);
    EXPECT_EQ(arr[1].value().b, 42);
    EXPECT_EQ(arr[2].has_value(), false);
    EXPECT_EQ(arr[3].value().a, 42);
    EXPECT_EQ(arr[3].value().b, 21);
}
