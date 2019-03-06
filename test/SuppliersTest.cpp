#include "test.h"
#include "../src/Suppliers.h"

#include <thread>

TEST(Suppliers, MemoizedSupplier)
{
    int value = 0;
    std::unique_ptr<Supplier<int>> supplier = Suppliers::memoized<int>([&value]() {
        return ++value;
    });

    EXPECT_EQ(supplier->get(), 1);
    EXPECT_EQ(supplier->get(), 1);
}

TEST(Suppliers, MemoizedSupplierWithExpiration)
{
    int value = 0;
    std::unique_ptr<Supplier<int>> supplier = Suppliers::memoizedWithExpiration<int>(
        Duration::ofSeconds(1),
        [&value]() {
            return ++value;
        }
    );

    EXPECT_EQ(supplier->get(), 1);
    EXPECT_EQ(supplier->get(), 1);

    std::this_thread::sleep_for(std::chrono::milliseconds(1500));

    EXPECT_EQ(supplier->get(), 2);
    EXPECT_EQ(supplier->get(), 2);
}