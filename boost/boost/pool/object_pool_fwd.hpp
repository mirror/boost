// Copyright (C) 2000, 2001 Stephen Cleary (shammah@voyager.net)
//
// This file can be redistributed and/or modified under the terms found
//  in "copyright.html"
// This software and its documentation is provided "as is" without express or
//  implied warranty, and with no claim as to its suitability for any purpose.
//
// See http://www.boost.org for updates, documentation, and revision history.

#ifndef BOOST_OBJECT_POOL_FWD_HPP
#define BOOST_OBJECT_POOL_FWD_HPP

// boost::default_user_allocator_new_delete fwd
#include <boost/pool/pool_fwd.hpp>

namespace boost {

template <typename T, typename UserAllocator = default_user_allocator_new_delete>
class object_pool;

} // namespace boost

#endif
