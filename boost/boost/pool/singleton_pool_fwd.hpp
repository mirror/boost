// Copyright (C) 2000, 2001 Stephen Cleary (shammah@voyager.net)
//
// This file can be redistributed and/or modified under the terms found
//  in "copyright.html"
// This software and its documentation is provided "as is" without express or
//  implied warranty, and with no claim as to its suitability for any purpose.
//
// See http://www.boost.org for updates, documentation, and revision history.

#ifndef BOOST_SINGLETON_POOL_FWD_HPP
#define BOOST_SINGLETON_POOL_FWD_HPP

// boost::details::pool::default_mutex
#include <boost/pool/detail/mutex.hpp>
// boost::default_user_allocator_new_delete fwd
#include <boost/pool/pool_fwd.hpp>

namespace boost {

template <typename Tag, unsigned RequestedSize,
    typename UserAllocator = default_user_allocator_new_delete,
    typename Mutex = details::pool::default_mutex,
    unsigned NextSize = 32>
struct singleton_pool;

} // namespace boost

#endif
