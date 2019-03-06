#pragma once

#include <exception>
#include <chrono>

class DurationSubstractionException : public std::exception
{

};

class Duration
{
public:
    static Duration now()
    {
        auto now = std::chrono::high_resolution_clock::now();
        return Duration(now.time_since_epoch().count());
    }

    static Duration ofSeconds(unsigned long long seconds)
    {
        return Duration(seconds * SECONDS_TO_NANOS);
    }

    static Duration ofMillis(unsigned long long millis)
    {
        return Duration(millis * MILLIS_TO_NANOS);
    }
    
    static Duration ofMicros(unsigned long long micros)
    {
        return Duration(micros * MICROS_TO_NANOS);
    }

    static Duration ofNanos(unsigned long long nanos)
    {
        return Duration(nanos);
    }

    static Duration ofMinutes(unsigned long long minutes)
    {
        return Duration(minutes * MINUTES_TO_NANOS);
    }

    static Duration ofHours(unsigned long long hours)
    {
        return Duration(hours * HOURS_TO_NANOS);
    }

    static Duration ofDays(unsigned long long days)
    {
        return Duration(days * DAYS_TO_NANOS);
    }

    unsigned long long days() const
    {
        return m_nanos / DAYS_TO_NANOS;
    }

    unsigned long long hours() const
    {
        return m_nanos / HOURS_TO_NANOS;
    }

    unsigned long long minutes() const
    {
        return m_nanos / MINUTES_TO_NANOS;
    }

    unsigned long long seconds() const
    {
        return m_nanos / SECONDS_TO_NANOS;
    }

    unsigned long long millis() const
    {
        return m_nanos / MILLIS_TO_NANOS;
    }

    unsigned long long micros() const
    {
        return m_nanos / MICROS_TO_NANOS;
    }

    unsigned long long nanos() const
    {
        return m_nanos;
    }

    Duration operator-(const Duration& other)
    {
        if (m_nanos < other.m_nanos) {
            throw new DurationSubstractionException();
        }

        return Duration(m_nanos - other.m_nanos);
    }

    bool operator>=(const Duration& other)
    {
        return m_nanos >= other.m_nanos;
    }

    bool operator>(const Duration& other)
    {
        return m_nanos > other.m_nanos;
    }

    bool operator==(const Duration& other)
    {
        return m_nanos == other.m_nanos;
    }

    bool operator<(const Duration& other)
    {
        return m_nanos < other.m_nanos;
    }
    
    bool operator<=(const Duration& other)
    {
        return m_nanos <= other.m_nanos;
    }

protected:
    Duration(unsigned long long nanos)
        : m_nanos(nanos)
    {

    }

private:
    static const unsigned long long MICROS_TO_NANOS = 1000;
    static const unsigned long long MILLIS_TO_MICROS = 1000;
    static const unsigned long long SECONDS_TO_MILLIS = 1000;
    static const unsigned long long MINUTES_TO_SECONDS = 60;
    static const unsigned long long HOURS_TO_MINUTES = 60;
    static const unsigned long long DAYS_TO_HOURS = 24;

    static const unsigned long long MILLIS_TO_NANOS = MILLIS_TO_MICROS * MICROS_TO_NANOS;
    static const unsigned long long SECONDS_TO_NANOS = SECONDS_TO_MILLIS * MILLIS_TO_NANOS;
    static const unsigned long long MINUTES_TO_NANOS = MINUTES_TO_SECONDS * SECONDS_TO_NANOS;
    static const unsigned long long HOURS_TO_NANOS = HOURS_TO_MINUTES * MINUTES_TO_NANOS;
    static const unsigned long long DAYS_TO_NANOS = DAYS_TO_HOURS * HOURS_TO_NANOS;

    unsigned long long m_nanos;
};