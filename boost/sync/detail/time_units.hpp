/*
 *          Copyright Andrey Semashev 2013.
 * Distributed under the Boost Software License, Version 1.0.
 *    (See accompanying file LICENSE_1_0.txt or copy at
 *          http://www.boost.org/LICENSE_1_0.txt)
 */
/*!
 * \file   time_units.hpp
 *
 * \brief  This header is the Boost.Sync library implementation, see the library documentation
 *         at http://www.boost.org/doc/libs/release/libs/sync/doc/html/index.html.
 */

#ifndef BOOST_SYNC_DETAIL_TIME_UNITS_HPP_INCLUDED_
#define BOOST_SYNC_DETAIL_TIME_UNITS_HPP_INCLUDED_

#include <time.h>
#include <boost/cstdint.hpp>
#include <boost/sync/detail/config.hpp>

#if defined(BOOST_SYNC_DETAIL_PLATFORM_WINAPI)
#include <boost/detail/winapi/time.hpp>
#endif

#include <boost/sync/detail/header.hpp>

#ifdef BOOST_HAS_PRAGMA_ONCE
#pragma once
#endif

namespace boost {

namespace sync {

namespace detail {

#if defined(BOOST_SYNC_DETAIL_PLATFORM_PTHREAD)

class duration
{
public:
    typedef int64_t native_type;
    // The native duration is in nanoseconds
    static BOOST_CONSTEXPR_OR_CONST uint64_t subsecond_fraction = 1000000000u;

private:
    native_type m_value;

public:
    duration() : m_value(0) {}
    explicit duration(native_type value) : m_value(value) {}

    native_type get() const { return m_value; }

    duration& operator+= (duration const& that)
    {
        m_value += that.m_value;
        return *this;
    }
    duration& operator-= (duration const& that)
    {
        m_value -= that.m_value;
        return *this;
    }
    duration operator- () const
    {
        return duration(-m_value);
    }

    friend duration operator+ (duration left, duration const& right)
    {
        left += right;
        return left;
    }
    friend duration operator- (duration left, duration const& right)
    {
        left -= right;
        return left;
    }
};

class time_point
{
public:
    typedef struct ::timespec native_type;
    // The native subsecond precision is nanoseconds
    static BOOST_CONSTEXPR_OR_CONST uint64_t subsecond_fraction = duration::subsecond_fraction;

private:
    native_type m_value;

public:
    time_point() : m_value() {}
    explicit time_point(time_t t, unsigned int subsecond = 0)
    {
        m_value.tv_sec = t;
        m_value.tv_nsec = subsecond;
    }

    native_type const& get() const { return m_value; }

    static time_point now()
    {
#if defined(BOOST_HAS_CLOCK_GETTIME)
        time_point t;
        ::clock_gettime(CLOCK_REALTIME, &t.m_value);
        return t;
#else
        return time_point(::time(0));
#endif
    }

    time_point& operator+= (duration const& dur)
    {
        int64_t nsec = static_cast< int64_t >(m_value.tv_nsec) + dur.get();
        int64_t tv_nsec = nsec % duration::subsecond_fraction;
        if (tv_nsec < 0)
        {
            tv_nsec += subsecond_fraction;
            --m_value.tv_sec;
        }
        m_value.tv_nsec = tv_nsec;
        m_value.tv_sec += nsec / duration::subsecond_fraction;

        return *this;
    }
    time_point& operator-= (duration const& dur)
    {
        return operator+= (-dur);
    }

    friend time_point operator+ (time_point left, duration const& right)
    {
        left += right;
        return left;
    }
    friend time_point operator- (time_point left, duration const& right)
    {
        left -= right;
        return left;
    }

    friend duration operator- (time_point const& left, time_point const& right)
    {
        int64_t seconds = static_cast< int64_t >(left.m_value.tv_sec) - static_cast< int64_t >(right.m_value.tv_sec);
        int64_t nseconds = static_cast< int64_t >(left.m_value.tv_nsec) - static_cast< int64_t >(right.m_value.tv_nsec);
        return duration(seconds * duration::subsecond_fraction + nseconds);
    }
};

#elif defined(BOOST_SYNC_DETAIL_PLATFORM_WINAPI)

class duration
{
public:
    typedef int64_t native_type;
    // The native duration is in milliseconds
    static BOOST_CONSTEXPR_OR_CONST uint64_t subsecond_fraction = 1000u;

private:
    native_type m_value;

public:
    duration() : m_value(0) {}
    explicit duration(native_type value) : m_value(value) {}

    native_type get() const { return m_value; }

    duration& operator+= (duration const& that)
    {
        m_value += that.m_value;
        return *this;
    }
    duration& operator-= (duration const& that)
    {
        m_value -= that.m_value;
        return *this;
    }
    duration operator- () const
    {
        return duration(-m_value);
    }

    friend duration operator+ (duration left, duration const& right)
    {
        left += right;
        return left;
    }
    friend duration operator- (duration left, duration const& right)
    {
        left -= right;
        return left;
    }
};

class time_point
{
public:
    typedef uint64_t native_type;
    // The native subsecond precision is milliseconds
    static BOOST_CONSTEXPR_OR_CONST uint64_t subsecond_fraction = duration::subsecond_fraction;

private:
    native_type m_value;

public:
    time_point() : m_value(0) {}
    explicit time_point(time_t t, unsigned int subsecond = 0) : m_value(static_cast< uint64_t >(t) * subsecond_fraction + subsecond)
    {
    }

    native_type const& get() const { return m_value; }

    static time_point now()
    {
        union
        {
            uint64_t as_uint64;
            boost::detail::winapi::FILETIME_ as_filetime;
        }
        caster;
        boost::detail::winapi::GetSystemTimeAsFileTime(&caster.as_filetime);

        // Compensate the difference between 1970-Jan-01 & 1601-Jan-01
        // in 100-nanosecond intervals
        caster.as_uint64 -= 116444736000000000ull; // (27111902 << 32) + 3577643008

        // Convert to milliseconds
        caster.as_uint64 /= 10000u;

        time_point res;
        res.m_value = caster.as_uint64;
        return res;
    }

    time_point& operator+= (duration const& dur)
    {
        m_value += dur.get();
        return *this;
    }
    time_point& operator-= (duration const& dur)
    {
        m_value -= dur.get();
        return *this;
    }

    friend time_point operator+ (time_point left, duration const& right)
    {
        left += right;
        return left;
    }
    friend time_point operator- (time_point left, duration const& right)
    {
        left -= right;
        return left;
    }

    friend duration operator- (time_point const& left, time_point const& right)
    {
        return duration(static_cast< duration::native_type >(left.m_value - right.m_value));
    }
};

#endif

} // namespace detail

} // namespace sync

} // namespace boost

#include <boost/sync/detail/footer.hpp>

#endif // BOOST_SYNC_DETAIL_TIME_UNITS_HPP_INCLUDED_
