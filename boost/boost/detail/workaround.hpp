// Copyright David Abrahams 2002. Permission to copy, use,
// modify, sell and distribute this software is granted provided this
// copyright notice appears in all copies. This software is provided
// "as is" without express or implied warranty, and with no claim as
// to its suitability for any purpose.
#ifndef WORKAROUND_DWA2002126_HPP
# define WORKAROUND_DWA2002126_HPP

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
// value. The above expands to:
//
//     (BOOST_MSVC) != 0 && (BOOST_MSVC) <= 1200
//
// When used for workarounds on the latest known version of a
// compiler, the following convention should be observed:
//
//     #if BOOST_WORKAROUND(BOOST_MSVC, |0x1301)
//
// The version number in this case corresponds to the last version in
// which the workaround was known to have been required.  It only has
// value as a comment, since the outcome of the test is always 1
// unless BOOST_STRICT_CONFIG is defined.

# ifndef BOOST_STRICT_CONFIG
#  define BOOST_WORKAROUND(symbol, test) ((symbol) != 0 && ((symbol) test))
# else
#  define BOOST_WORKAROUND(symbol, test) 0
# endif 

#endif // WORKAROUND_DWA2002126_HPP
