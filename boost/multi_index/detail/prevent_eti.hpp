/* Copyright 2003-2008 Joaquin M Lopez Munoz.
 * Distributed under the Boost Software License, Version 1.0.
 * (See accompanying file LICENSE_1_0.txt or copy at
 * http://www.boost.org/LICENSE_1_0.txt)
 *
 * See http://www.boost.org/libs/multi_index for library home page.
 */

#ifndef BOOST_MULTI_INDEX_DETAIL_PREVENT_ETI_HPP
#define BOOST_MULTI_INDEX_DETAIL_PREVENT_ETI_HPP

#if defined(_MSC_VER)
#pragma once
#endif

#include <boost/config.hpp> /* keep it first to prevent nasty warns in MSVC */
#include <boost/detail/workaround.hpp>

namespace boost{

namespace multi_index{

namespace detail{

template<typename Type,typename Construct>
struct prevent_eti
{
  typedef Construct type;
};

} /* namespace multi_index::detail */

} /* namespace multi_index */

} /* namespace boost */

#endif
