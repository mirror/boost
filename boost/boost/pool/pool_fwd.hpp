// Copyright (C) 2000, 2001 Stephen Cleary (shammah@voyager.net)
//
// This file can be redistributed and/or modified under the terms found
//  in "copyright.html"
// This software and its documentation is provided "as is" without express or
//  implied warranty, and with no claim as to its suitability for any purpose.
//
// See http://www.boost.org for updates, documentation, and revision history.

#ifndef BOOST_POOL_FWD_HPP
#define BOOST_POOL_FWD_HPP

namespace boost {

struct default_user_allocator_new_delete;
struct default_user_allocator_malloc_free;

template <typename UserAllocator = default_user_allocator_new_delete>
class pool;

} // namespace boost

#endif
