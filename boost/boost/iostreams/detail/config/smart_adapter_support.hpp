// (C) Copyright Jonathan Turkanis 2004.
// Distributed under the Boost Software License, Version 1.0. (See accompanying
// file LICENSE_1_0.txt or copy at http://www.boost.org/LICENSE_1_0.txt.)

// See http://www.boost.org/libs/iostreams for documentation.

// Adapted from http://www.boost.org/more/separate_compilation.html, by
// John Maddock.

#ifndef BOOST_IOSTREAMS_DETAIL_CONFIG_SMART_ADAPTER_SUPPORT_HPP_INCLUDED
#define BOOST_IOSTREAMS_DETAIL_CONFIG_SMART_ADAPTER_SUPPORT_HPP_INCLUDED

#if defined(_MSC_VER) && (_MSC_VER >= 1020)
# pragma once
#endif              

#include <boost/config.hpp>
#include <boost/detail/workaround.hpp>

#ifndef BOOST_IOSTREAMS_NO_FULL_SMART_ADAPTER_SUPPORT
# if BOOST_WORKAROUND(__BORLANDC__, < 0x600)
#  define BOOST_IOSTREAMS_NO_FULL_SMART_ADAPTER_SUPPORT
# endif
#endif

#endif // #ifndef BOOST_IOSTREAMS_DETAIL_CONFIG_SMART_ADAPTER_SUPPORT_HPP_INCLUDED
