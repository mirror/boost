// Copyright David Abrahams 2002. Permission to copy, use,
// modify, sell and distribute this software is granted provided this
// copyright notice appears in all copies. This software is provided
// "as is" without express or implied warranty, and with no claim as
// to its suitability for any purpose.
#ifndef WORKAROUND_DWA2002126_HPP
# define WORKAROUND_DWA2002126_HPP

# include <boost/config.hpp>

// Compiler/library version workaround macro
//
// Usage:
//
//     #if BOOST_WORKAROUND(BOOST_MSVC, <= 1200)
//        ... // workaround code here
//     #endif
//
// When BOOST_STRICT_CONFIG is defined, expands to 0. Otherwise, the
// first argument must be undefined or expand to a numeric
// value. The above expands to the moral equivalent of:
//
//     defined(BOOST_MSVC) && BOOST_MSVC <= 1200
//

# ifndef BOOST_STRICT_CONFIG
#  include <boost/preprocessor/cat.hpp>
#  define BOOST_NUMERIC_DEFINED_SUFFIX 1
#  define BOOST_WORKAROUND(symbol, test) (BOOST_PP_CAT(symbol,BOOST_NUMERIC_DEFINED_SUFFIX) && symbol test)
# else
#  define BOOST_WORKAROUND(symbol, test) 0
# endif 

#endif // WORKAROUND_DWA2002126_HPP
