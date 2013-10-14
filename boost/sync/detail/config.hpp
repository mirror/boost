/*
 * Distributed under the Boost Software License, Version 1.0.
 *    (See accompanying file LICENSE_1_0.txt or copy at
 *          http://www.boost.org/LICENSE_1_0.txt)
 *
 * (C) Copyright 2013 Andrey Semashev
 */
/*!
 * \file   config.hpp
 *
 * \brief  This header is the Boost.Sync library implementation, see the library documentation
 *         at http://www.boost.org/doc/libs/release/libs/sync/doc/html/index.html. In this file
 *         internal configuration macros are defined.
 */

#ifndef BOOST_SYNC_DETAIL_CONFIG_HPP_INCLUDED_
#define BOOST_SYNC_DETAIL_CONFIG_HPP_INCLUDED_

#include <boost/config.hpp>

#if defined(BOOST_WINDOWS)
#include <boost/detail/winapi/config.hpp>
#endif

#ifdef BOOST_HAS_PRAGMA_ONCE
#pragma once
#endif

// BOOST_SYNC_USE_PTHREAD and BOOST_SYNC_USE_WINAPI_VERSION are user-configurable macros
#if defined(BOOST_WINDOWS) && !defined(BOOST_SYNC_USE_WINAPI_VERSION)
#define BOOST_SYNC_USE_WINAPI_VERSION BOOST_USE_WINAPI_VERSION
#endif

#if defined(BOOST_SYNC_USE_WINAPI_VERSION) && !defined(BOOST_SYNC_USE_PTHREAD)
#define BOOST_SYNC_DETAIL_PLATFORM_WINAPI
#else
#define BOOST_SYNC_DETAIL_PLATFORM_PTHREAD
#endif

#if defined(BOOST_SYNC_DETAIL_PLATFORM_PTHREAD)
#define BOOST_SYNC_DETAIL_ABI_NAMESPACE posix
#elif defined(BOOST_SYNC_DETAIL_PLATFORM_WINAPI)
#if BOOST_SYNC_USE_WINAPI_VERSION >= BOOST_WINAPI_VERSION_WIN6
#define BOOST_SYNC_DETAIL_ABI_NAMESPACE winnt6
#else
#define BOOST_SYNC_DETAIL_ABI_NAMESPACE winnt5
#endif
#else
#error Boost.Sync: Internal configuration error: unknown base threading API
#endif

#if !defined(BOOST_NO_CXX11_INLINE_NAMESPACES)
#define BOOST_SYNC_DETAIL_OPEN_ABI_NAMESPACE inline namespace BOOST_SYNC_DETAIL_ABI_NAMESPACE
#else
#define BOOST_SYNC_DETAIL_OPEN_ABI_NAMESPACE namespace BOOST_SYNC_DETAIL_ABI_NAMESPACE
namespace boost {
namespace sync {

// Emulate inline namespace with a using directive
BOOST_SYNC_DETAIL_OPEN_ABI_NAMESPACE {}

using namespace BOOST_SYNC_DETAIL_ABI_NAMESPACE
#if defined(__GNUC__) && (__GNUC__ >= 4 || (__GNUC__ == 3 && __GNUC_MINOR__ >= 4)) && !defined(__clang__)
__attribute__((__strong__))
#endif
;

}
}
#endif // !defined(BOOST_NO_CXX11_INLINE_NAMESPACES)

#if ! defined BOOST_SYNC_DONT_USE_CHRONO \
  && ! defined BOOST_SYNC_USES_CHRONO
#define BOOST_SYNC_USES_CHRONO
#endif

#define BOOST_SYNC_USES_CHRONO

#endif // BOOST_SYNC_DETAIL_CONFIG_HPP_INCLUDED_
