// Copyright (C) 2000, 2001 Stephen Cleary (shammah@voyager.net)
//
// This file can be redistributed and/or modified under the terms found
//  in "copyright.html"
// This software and its documentation is provided "as is" without express or
//  implied warranty, and with no claim as to its suitability for any purpose.
//
// See http://www.boost.org for updates, documentation, and revision history.

#ifndef BOOST_POOL_ALLOC_FWD_HPP
#define BOOST_POOL_ALLOC_FWD_HPP

// boost::details::pool::default_mutex
#include <boost/pool/detail/mutex.hpp>
// boost::default_user_allocator_new_delete fwd
#include <boost/pool/pool_fwd.hpp>

namespace boost {

struct pool_allocator_tag;

template <typename T,
    typename UserAllocator = default_user_allocator_new_delete,
    typename Mutex = details::pool::default_mutex,
    unsigned NextSize = 32>
class pool_allocator;

struct fast_pool_allocator_tag;

template <typename T,
    typename UserAllocator = default_user_allocator_new_delete,
    typename Mutex = details::pool::default_mutex,
    unsigned NextSize = 32>
class fast_pool_allocator;

} // namespace boost

#endif
