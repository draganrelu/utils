#pragma once

#include "Duration.h"

class Timer
{
public:
    Timer(const Duration& duration)
        : m_duration(duration),
          m_start(Duration::ofSeconds(0)),
          m_started(false)
    {

    }

    virtual void start()
    {
        m_start = Duration::now();
        m_started = true;
    }

    virtual void reset()
    {
        start();
    }

    virtual bool expired()
    {
        Duration now = Duration::now();
        return now - m_start >= m_duration;
    }

protected:
    Duration m_duration;
    Duration m_start;
    bool m_started;
};