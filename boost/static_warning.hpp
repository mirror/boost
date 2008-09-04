#ifndef BOOST_STATIC_WARNING_HPP
#define BOOST_STATIC_WARNING_HPP

//  (C) Copyright Robert Ramey 2003. Jonathan Turkanis 2004.
// Use, modification and distribution is subject to the Boost Software
// License, Version 1.0. (See accompanying file LICENSE_1_0.txt or copy at
// MS compatible compilers support #pragma once
#if defined(_MSC_VER) && (_MSC_VER >= 1020)
# pragma once
#endif

#error "This header is deprecated. Please use: boost/serialization/static_warning.hpp"

#if defined(_MSC_VER) || defined(__BORLANDC__) || defined(__DMC__)
#  pragma message ("Warning: This header is deprecated. Please use: boost/serialization/static_warning.hpp")
#elif defined(__GNUC__) || defined(__HP_aCC) || defined(__SUNPRO_CC) || defined(__IBMCPP__)
#  warning "This header is deprecated. Please use: boost/serialization/static_warning.hpp"
#endif

#include <boost/serialization/static_warning.hpp>

#endif // BOOST_STATIC_WARNING_HPP
