#pragma once

#include "MemoizedSupplier.h"
#include "MemoizedSupplierWithExpiration.h"

#include <mutex>
#include <memory>

class Suppliers
{
public:
    template <typename T>
    static std::unique_ptr<Supplier<T>> memoized(const std::function<T(void)>& function)
    {
        return std::unique_ptr<Supplier<T>>(new MemoizedSupplier<T>(function));
    }

    template <typename T>
    static std::unique_ptr<Supplier<T>> memoizedWithExpiration(
        const Duration& expiryDuration,
        const std::function<T(void)>& function)
    {
        return std::unique_ptr<Supplier<T>>(
            new MemoizedSupplierWithExpiration<T>(expiryDuration, function));
    }
};