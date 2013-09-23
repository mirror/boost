// atomic.hpp: pull in std::atomic or boost::atomic
//
// Copyright (C) 2013 Tim Blechmann
//
// Distributed under the Boost Software License, Version 1.0. (See
// accompanying file LICENSE_1_0.txt or copy at
// http://www.boost.org/LICENSE_1_0.txt)

#ifndef BOOST_SYNC_DETAIL_ATOMIC_HPP
#define BOOST_SYNC_DETAIL_ATOMIC_HPP

#if !defined(BOOST_SYNC_USE_STD_ATOMIC)

#if BOOST_CLANG
#if __has_include( <atomic> )
#define BOOST_SYNC_USE_STD_ATOMIC
#endif
#endif

#if defined(BOOST_MSVC) && (BOOST_MSVC >= 1700)
#define BOOST_SYNC_USE_STD_ATOMIC
#endif

#if BOOST_GCC
#if (BOOST_GCC >= 40800) && (__cplusplus >= 201103L)
#define BOOST_SYNC_USE_STD_ATOMIC
#endif
#endif

#endif // !defined(BOOST_SYNC_USE_STD_ATOMIC)

#ifdef BOOST_SYNC_USE_STD_ATOMIC
#include <atomic>
#else
#include <boost/atomic.hpp>
#endif

#include <boost/sync/detail/config.hpp>
#include <boost/sync/detail/header.hpp>

#ifdef BOOST_HAS_PRAGMA_ONCE
#pragma once
#endif

namespace boost  {
namespace sync   {
namespace detail {

#ifdef BOOST_SYNC_USE_STD_ATOMIC

using std::atomic;
using std::atomic_int;
using std::atomic_bool;

using std::memory_order_acquire;
using std::memory_order_acq_rel;
using std::memory_order_release;
using std::memory_order_consume;
using std::memory_order_relaxed;
using std::memory_order_seq_cst;

using std::atomic_thread_fence;

#else

using boost::atomic;
using boost::atomic_int;
using boost::atomic_bool;

using boost::memory_order_acquire;
using boost::memory_order_release;
using boost::memory_order_acq_rel;
using boost::memory_order_consume;
using boost::memory_order_relaxed;
using boost::memory_order_seq_cst;

using boost::atomic_thread_fence;

#endif

}
}
}

#undef BOOST_SYNC_USE_STD_ATOMIC

#include <boost/sync/detail/footer.hpp>

#endif // BOOST_SYNC_DETAIL_ATOMIC_HPP
