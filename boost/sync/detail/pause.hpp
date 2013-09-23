/*
 * Distributed under the Boost Software License, Version 1.0.
 *    (See accompanying file LICENSE_1_0.txt or copy at
 *          http://www.boost.org/LICENSE_1_0.txt)
 *
 * (C) Copyright 2013 Tim Blechmann
 * (C) Copyright 2013 Andrey Semashev
 */

#ifndef BOOST_SYNC_DETAIL_PAUSE_HPP_INCLUDED_
#define BOOST_SYNC_DETAIL_PAUSE_HPP_INCLUDED_


#include <boost/config.hpp>

#ifdef __SSE2__
#include <xmmintrin.h>
#endif

namespace boost  {
namespace sync   {
namespace detail {

static BOOST_FORCEINLINE void pause()
{
#ifdef __SSE2__
    _mm_pause();

#elif defined(__GNUC__) && (defined(__i386__) || defined(__x86_64__))
    __asm__ __volatile__("pause;");

#elif (defined(__INTEL_COMPILER) || defined(_M_IX86))
    __asm { nop };

#endif
}



} // namespace detail
} // namespace sync
} // namespace boost

#endif // BOOST_SYNC_DETAIL_PAUSE_HPP_INCLUDED_
