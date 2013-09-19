/*
 *          Copyright Andrey Semashev 2013.
 * Distributed under the Boost Software License, Version 1.0.
 *    (See accompanying file LICENSE_1_0.txt or copy at
 *          http://www.boost.org/LICENSE_1_0.txt)
 */
/*!
 * \file   support/date_time.hpp
 *
 * \brief  This header enables support for Boost.DateTime time units.
 */

#ifndef BOOST_SYNC_SUPPORT_DATE_TIME_HPP_INCLUDED_
#define BOOST_SYNC_SUPPORT_DATE_TIME_HPP_INCLUDED_

#include <ctime>
#include <boost/cstdint.hpp>
#include <boost/date_time/posix_time/posix_time_types.hpp>
#include <boost/sync/detail/config.hpp>
#include <boost/sync/detail/time_traits.hpp>
#include <boost/sync/detail/time_units.hpp>
#include <boost/sync/detail/header.hpp>

#ifdef BOOST_HAS_PRAGMA_ONCE
#pragma once
#endif

namespace boost {

namespace sync {

namespace detail {

template< typename T >
struct time_traits< T, typename T::_is_boost_date_time_duration >
{
    typedef time_duration_tag tag;

    static BOOST_CONSTEXPR_OR_CONST bool is_specialized = true;

    static duration to_sync_unit(T const& dur)
    {
        typedef typename T::traits_type traits_type;
        enum
        {
            conversion_ratio = traits_type::ticks_per_second >= duration::subsecond_fraction ?
                traits_type::ticks_per_second / duration::subsecond_fraction :
                duration::subsecond_fraction / traits_type::ticks_per_second
        };
        return duration(traits_type::ticks_per_second >= duration::subsecond_fraction ? dur.ticks() / conversion_ratio : dur.ticks() * conversion_ratio);
    }
};

template< typename T >
struct time_traits< T, typename T::_is_boost_date_time_time_point >
{
    typedef time_point_tag tag;

    static BOOST_CONSTEXPR_OR_CONST bool is_specialized = true;

    static time_point to_sync_unit(T const& point)
    {
        typedef typename T::date_type date_type;
        typedef typename T::time_duration_type time_duration_type;
        time_duration_type dur = point - T(date_type(1970, 1, 1));

        std::time_t seconds = dur.total_seconds();
        uint64_t fractional_seconds = dur.fractional_seconds();

        typedef typename time_duration_type::traits_type traits_type;
        enum
        {
            conversion_ratio = traits_type::ticks_per_second >= time_point::subsecond_fraction ?
                traits_type::ticks_per_second / time_point::subsecond_fraction :
                time_point::subsecond_fraction / traits_type::ticks_per_second
        };
        return time_point(seconds, traits_type::ticks_per_second >= time_point::subsecond_fraction ? fractional_seconds / conversion_ratio : fractional_seconds * conversion_ratio);
    }
};

} // namespace detail

} // namespace sync

} // namespace boost

#include <boost/sync/detail/footer.hpp>

#endif // BOOST_SYNC_SUPPORT_DATE_TIME_HPP_INCLUDED_
