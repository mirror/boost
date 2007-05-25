// Boost.Bimap
//
// Copyright (c) 2006-2007 Matias Capeletto
//
// Distributed under the Boost Software License, Version 1.0.
// (See accompanying file LICENSE_1_0.txt or copy at
// http://www.boost.org/LICENSE_1_0.txt)

/// \file relation/standard_relation_fwd.hpp
/// \brief Defines the standard_pair_view class.

#ifndef BOOST_BIMAP_RELATION_STANDARD_RELATION_FWD_HPP
#define BOOST_BIMAP_RELATION_STANDARD_RELATION_FWD_HPP

#if defined(_MSC_VER) && (_MSC_VER>=1200)
#pragma once
#endif

#include <boost/config.hpp>

#include <boost/mpl/bool.hpp>

namespace boost {
namespace bimaps {
namespace relation {

template< class TA, class TB, bool force_mutable = false >
class standard_relation;

template< class TA, class TB >
class standard_relation_view;

template< class TA, class TB >
class const_standard_relation_view;

template< class FirstType, class SecondType, bool constant, class Layout >
class standard_pair_view;

//-----------------------------------------------------------------------------

#ifndef BOOST_BIMAP_DOXYGEN_WILL_NOT_PROCESS_THE_FOLLOWING_LINES

namespace support {

template< class Type >
struct is_standard_pair_view :
    ::boost::mpl::false_ {};

template< class FirstType, class SecondType, class Layout >
struct is_standard_pair_view<
    standard_pair_view<FirstType,SecondType,false,Layout> > :
    ::boost::mpl::true_ {};

template< class Type >
struct is_standard_relation_view :
    ::boost::mpl::false_ {};

template< class FirstType, class SecondType >
struct is_standard_relation_view<
    standard_relation_view<FirstType,SecondType> > :
    ::boost::mpl::true_ {};

} // namespace support

#endif // BOOST_BIMAP_DOXYGEN_WILL_NOT_PROCESS_THE_FOLLOWING_LINES

} // namespace relation
} // namespace bimaps
} // namespace boost

#endif // BOOST_BIMAP_RELATION_STANDARD_RELATION_FWD_HPP

