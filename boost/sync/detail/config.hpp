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


#ifdef BOOST_HAS_UNISTD_H
#include <unistd.h>

#if (_POSIX_SEMAPHORES - 0) >= 200112L
#define BOOST_SYNC_POSIX_SEMAPHORES
#endif

#endif // BOOST_HAS_UNISTD_H

#if defined(__APPLE__)
#include <Availability.h>

// OSX
#ifdef __MAC_OS_X_VERSION_MIN_REQUIRED

#if __MAC_OS_X_VERSION_MIN_REQUIRED >= __MAC_10_6
#define BOOST_SYNC_DISPATCH_SEMAPHORES
#endif

#endif // __MAC_OS_X_VERSION_MIN_REQUIRED

// iOS
#ifdef __IPHONE_OS_VERSION_MIN_REQUIRED

// untested!
#if __IPHONE_OS_VERSION_MIN_REQUIRED >= __IPHONE_4_0
#define BOOST_SYNC_DISPATCH_SEMAPHORES
#endif

#endif // __IPHONE_OS_VERSION_MIN_REQUIRED

#endif // __APPLE__


#if ! defined BOOST_SYNC_DONT_USE_CHRONO \
  && ! defined BOOST_SYNC_USES_CHRONO
#define BOOST_SYNC_USES_CHRONO
#endif

#define BOOST_SYNC_USES_CHRONO



#endif // BOOST_SYNC_DETAIL_CONFIG_HPP_INCLUDED_
