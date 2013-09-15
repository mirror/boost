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

#ifdef BOOST_HAS_PRAGMA_ONCE
#pragma once
#endif

// BOOST_SYNC_USE_PTHREAD and BOOST_SYNC_USE_WINAPI_VERSION are user-configurable macros
#if defined(BOOST_WINDOWS) && !defined(BOOST_SYNC_USE_WINAPI_VERSION)
#if defined(_WIN32_WINNT)
#define BOOST_SYNC_USE_WINAPI_VERSION _WIN32_WINNT
#else
// By default use Windows 2000 API: _WIN32_WINNT_WIN2K
#define BOOST_SYNC_USE_WINAPI_VERSION 0x0500
#endif

#endif
#if defined(BOOST_SYNC_USE_PTHREAD)
#define BOOST_SYNC_DETAIL_PLATFORM_PTHREAD
#elif defined(BOOST_SYNC_USE_WINAPI_VERSION)
#define BOOST_SYNC_DETAIL_PLATFORM_WINAPI
#else
#define BOOST_SYNC_DETAIL_PLATFORM_PTHREAD
#endif

#if ! defined BOOST_SYNC_DONT_USE_CHRONO \
  && ! defined BOOST_SYNC_USES_CHRONO
#define BOOST_SYNC_USES_CHRONO
#endif

#define BOOST_SYNC_USES_CHRONO

#endif // BOOST_SYNC_DETAIL_CONFIG_HPP_INCLUDED_
