// Copyright (C) 2000 Stephen Cleary (shammah@voyager.net)
//
// This file can be redistributed and/or modified under the terms found
//  in "copyright.html"
// This software and its documentation is provided "as is" without express or
//  implied warranty, and with no claim as to its suitability for any purpose.
//
// See http://www.boost.org for updates, documentation, and revision history.

#ifndef BOOST_POOL_POSTULATE_HPP
#define BOOST_POOL_POSTULATE_HPP

// Join: merge tokens *after* macro substitution
#define BOOST_POOL_JOIN_HELPER(x, y) x ## y
#define BOOST_POOL_JOIN(x, y) BOOST_POOL_JOIN_HELPER(x, y)

// Postulate: compile-time assertion
namespace boost {
namespace details {
namespace pool {

// BOOST_POOL_POSTULATE_FAILED cannot be instantiated if its template parameter is
//  false.  This is what the compiler will try to do if a postulate fails.
template <bool>
struct BOOST_POOL_POSTULATE_FAILED;
template <>
struct BOOST_POOL_POSTULATE_FAILED<true> { };

// POSTULATE_helper is just a helper class used to force the implicit
//  instantiation of BOOST_POOL_POSTULATE_FAILED.
template <int>
struct POSTULATE_helper { };

} // namespace pool
} // namespace details
} // namespace boost

// The postulate will try to typedef a type (*_helper) that will force
//  the implicit instantiation (through sizeof) of *_FAILED.  If the
//  postulate is false, an error message of the form 'Undefined structure
//  boost::details::pool::BOOST_POOL_POSTULATE_FAILED<0>' will result.

// Postulate uses the identifier 'BOOST_POOL_POSTULATE_on_line_' merged with the
//  current line number to generate a unique identifier.  For this reason,
//  only one postulate is allowed per line.

#define BOOST_POOL_POSTULATE(cond) \
    typedef ::boost::details::pool::POSTULATE_helper \
        <sizeof(::boost::details::pool::BOOST_POOL_POSTULATE_FAILED<(cond)>)> \
        BOOST_POOL_JOIN(BOOST_POOL_POSTULATE_on_line_, __LINE__)

#endif
