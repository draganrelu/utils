#pragma once

#include "Supplier.h"
#include "Timer.h"

template <typename T>
class MemoizedSupplierWithExpiration : public Supplier<T>
{
public:
    MemoizedSupplierWithExpiration(
        const Duration& expiryDuration,
        const std::function<T(void)>& function)
        : Supplier<T>(function),
          m_expiryDuration(expiryDuration),
          m_timer(m_expiryDuration),
          m_initialCall(true)
    {

    }

    virtual T get() override
    {
        std::lock_guard<std::mutex> lock(m_mutex);

        if (m_initialCall) {
            m_initialCall = false;
            m_timer.start();
            m_memoizedResult = Supplier<T>::get();
        } else {
            if (m_timer.expired()) {
                m_timer.reset();
                m_memoizedResult = Supplier<T>::get();
            }
        }

        return m_memoizedResult;
    }

protected:
    Duration m_expiryDuration;
    Timer m_timer;
    std::mutex m_mutex;
    T m_memoizedResult;
    bool m_initialCall;
};