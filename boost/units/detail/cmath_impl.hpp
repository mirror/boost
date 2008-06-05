// Boost.Units - A C++ library for zero-overhead dimensional analysis and 
// unit/quantity manipulation and conversion
//
// Copyright (C) 2003-2008 Matthias Christian Schabel
// Copyright (C) 2008 Steven Watanabe
//
// Distributed under the Boost Software License, Version 1.0. (See
// accompanying file LICENSE_1_0.txt or copy at
// http://www.boost.org/LICENSE_1_0.txt)

#ifndef BOOST_UNITS_CMATH_IMPL_HPP 
#define BOOST_UNITS_CMATH_IMPL_HPP

#include <boost/version.hpp>

#if (BOOST_VERSION <= 103500)
    #include <boost/units/detail/cmath_gnu_impl_boost_1_35.hpp>
    #include <boost/units/detail/cmath_mwcw_impl_boost_1_35.hpp>
    #include <boost/units/detail/cmath_msvc_impl_boost_1_35.hpp>
#else
    #include <boost/units/detail/cmath_gnu_impl.hpp>
    #include <boost/units/detail/cmath_mwcw_impl.hpp>
    #include <boost/units/detail/cmath_msvc_impl.hpp>
#endif // (BOOST_VERSION <= 103500)

#endif // BOOST_UNITS_CMATH_IMPL_HPP
