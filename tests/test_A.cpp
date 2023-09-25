#include <gtest/gtest.h>
#include "../src/A.hpp"

TEST(AAdditionTest, TestAddition)
{
    A obj;
    EXPECT_EQ(obj.addition(2, 3), 5); // Vous pouvez modifier les valeurs en conséquence
    EXPECT_EQ(obj.addition(0, 0), 0); // Autre cas de test
    // Ajoutez autant d'EXPECT_EQ que nécessaire pour tester différents cas.
}

int main(int argc, char** argv)
{
    ::testing::InitGoogleTest(&argc, argv);
    return RUN_ALL_TESTS();
}
