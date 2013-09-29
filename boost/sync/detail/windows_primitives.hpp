/*
 * Distributed under the Boost Software License, Version 1.0.
 *    (See accompanying file LICENSE_1_0.txt or copy at
 *          http://www.boost.org/LICENSE_1_0.txt)
 *
 * (C) Copyright 2005-2007 Anthony Williams
 * (C) Copyright 2007 David Deakins
 * (C) Copyright 2013 Andrey Semashev
 */
/*!
 * \file   windows_primitives.hpp
 *
 * \brief  This header is the Boost.Sync library implementation, see the library documentation
 *         at http://www.boost.org/doc/libs/release/libs/sync/doc/html/index.html.
 */

#ifndef BOOST_SYNC_DETAIL_WINDOWS_PRIMITIVES_HPP_INCLUDED_
#define BOOST_SYNC_DETAIL_WINDOWS_PRIMITIVES_HPP_INCLUDED_

#include <cstddef>
#include <boost/detail/winapi/synchronization.hpp>
#include <boost/sync/detail/config.hpp>
#include <boost/sync/detail/header.hpp>

#ifdef BOOST_HAS_PRAGMA_ONCE
#pragma once
#endif

namespace boost  {

namespace sync   {

namespace detail {

namespace windows {

BOOST_FORCEINLINE boost::detail::winapi::HANDLE_ create_anonymous_event(bool manual_reset, bool initial_state)
{
#if !defined(BOOST_NO_ANSI_APIS)
    return boost::detail::winapi::CreateEventA(NULL, manual_reset, initial_state, NULL);
#else
    return boost::detail::winapi::CreateEventW(NULL, manual_reset, initial_state, NULL);
#endif
}

BOOST_FORCEINLINE boost::detail::winapi::HANDLE_ create_anonymous_semaphore(long initial_count, long max_count)
{
#if !defined(BOOST_NO_ANSI_APIS)
    return CreateSemaphoreA(NULL, initial_count, max_count, NULL);
#else
    return CreateSemaphoreW(NULL, initial_count, max_count, NULL);
#endif
}

} // namespace windows

} // namespace detail

} // namespace sync

} // namespace boost

#include <boost/sync/detail/footer.hpp>

#endif // BOOST_SYNC_DETAIL_WINDOWS_PRIMITIVES_HPP_INCLUDED_
