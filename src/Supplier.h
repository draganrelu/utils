#pragma once

#include <functional>

template <typename T>
class Supplier
{
public:
    Supplier(const std::function<T(void)>& function)
        : m_function(function)
    {
    }

    Supplier(const Supplier<T>& other)
        : m_function(other.m_function)
    {

    }

    virtual T get()
    {
        return m_function();
    }

protected:
    std::function<T(void)> m_function;
};