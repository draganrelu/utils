#pragma once

#include "Supplier.h"

#include <mutex>

template <typename T>
class MemoizedSupplier : public Supplier<T>
{
public:
    MemoizedSupplier(const std::function<T(void)>& function)
        : Supplier<T>(function),
          m_initialCall(true)
    {

    }

    virtual T get() override
    {
        std::lock_guard<std::mutex> lock(m_mutex);
        if (m_initialCall) {
            m_initialCall = false;
            m_memoizedResult = Supplier<T>::get();
        }
        return m_memoizedResult;
    }

protected:
    std::mutex m_mutex;
    T m_memoizedResult;
    bool m_initialCall;
};