#define CATCH_CONFIG_MAIN

#include "test.h"

TEST(Supplier, OneSupplier)
{
    int counter = 0;
    Supplier<int> supplier = Supplier<int>([&counter]() {
        return counter++;
    });

    EXPECT_EQ(supplier.get(), 0);
    EXPECT_EQ(supplier.get(), 1);
}

TEST(Supplier, TwoSuppliers)
{
    int counter = 0;
    Supplier<int> supplier1 = Supplier<int>([&counter]() {
        return counter++;
    });
    Supplier<int> supplier2 = Supplier<int>([&counter]() {
        return counter++;
    });

    EXPECT_EQ(supplier1.get(), 0);
    EXPECT_EQ(supplier2.get(), 1);
    EXPECT_EQ(supplier1.get(), 2);
    EXPECT_EQ(supplier2.get(), 3);
}

TEST(Supplier, DifferentTypes)
{
    std::string message;
    Supplier<std::string> supplier = Supplier<std::string>([&message]() {
        message += "a";
        return message;
    });

    EXPECT_EQ(supplier.get(), "a");
    EXPECT_EQ(supplier.get(), "aa");   

    std::vector<int> elements;
    Supplier<std::vector<int>> supplier2 = Supplier<std::vector<int>>([&elements]() {
        elements.push_back(5);
        return elements;
    });

    EXPECT_EQ(supplier2.get().size(), 1);
    EXPECT_EQ(supplier2.get().size(), 2);
}