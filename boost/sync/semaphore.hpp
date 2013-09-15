// semaphore.hpp
//
// Copyright (C) 2013 Tim Blechmann
//
// Distributed under the Boost Software License, Version 1.0. (See
// accompanying file LICENSE_1_0.txt or copy at
// http://www.boost.org/LICENSE_1_0.txt)

#ifndef BOOST_SYNC_SEMAPHORE_HPP
#define BOOST_SYNC_SEMAPHORE_HPP

#include <boost/sync/detail/config.hpp>

#ifdef BOOST_HAS_PRAGMA_ONCE
#pragma once
#endif

#include <boost/sync/detail/header.hpp>


#if defined(BOOST_THREAD_PLATFORM_WIN32)
#include <boost/sync/semaphore/semaphore_win32.hpp>

#elif defined(BOOST_THREAD_POSIX_SEMAPHORES)
#include <boost/sync/semaphore/semaphore_posix.hpp>

#elif defined(BOOST_THREAD_DISPATCH_SEMAPHORES)
#include <boost/sync/semaphore/semaphore_dispatch.hpp>

#else

#include <boost/sync/semaphore/semaphore_emulation.hpp>

#endif

#include <boost/sync/detail/footer.hpp>

#endif // BOOST_THREAD_SEMAPHORE_HPP
