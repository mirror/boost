#ifndef BOOST_SERIALIZATION_FORCE_INCLUDE_HPP
#define BOOST_SERIALIZATION_FORCE_INCLUDE_HPP

// MS compatible compilers support #pragma once
#if defined(_MSC_VER) && (_MSC_VER >= 1020)
# pragma once
#endif

/////////1/////////2/////////3/////////4/////////5/////////6/////////7/////////8
// force_include.hpp:

// (C) Copyright 2002 Robert Ramey - http://www.rrsd.com . 
// Use, modification and distribution is subject to the Boost Software
// License, Version 1.0. (See accompanying file LICENSE_1_0.txt or copy at
// http://www.boost.org/LICENSE_1_0.txt)

//  See http://www.boost.org for updates, documentation, and revision history.

// implementation of class export functionality.  This is an alternative to
// "forward declaration" method to provoke instantiation of derived classes
// that are to be serialized through pointers.

#include <boost/config.hpp>

// the following help macro is to guarentee that certain coded
// is not removed by over-eager linker optimiser.  In certain cases
// we create static objects must be created but are actually never
// referenced - creation has a side-effect such as global registration
// which is important to us. We make an effort to refer these objects
// so that a smart linker won't remove them as being unreferenced.
// In microsoft compilers, inlining the code that does the referring
// means the code gets lost and the static object is not included
// in the library and hence never registered.  This manifests itself
// in an ungraceful crash at runtime when (and only when) built in
// release mode.

// Intel compiler
#if defined(__INTEL_COMPILER)
//   Intel C++ 7.0+ on Windows
#    if (__INTEL_COMPILER >= 700)
#       if defined(_WIN32)
#           define BOOST_FORCE_INCLUDE(f) __declspec(dllexport) f
#       else
#           define BOOST_FORCE_INCLUDE(f) f __attribute__ ((used))
#       endif
#    endif
// MSVC
#elif defined(BOOST_MSVC)
#    define BOOST_FORCE_INCLUDE(f) __declspec(dllexport) f 
// Code Warrior - question does this work for non-windows platforms?
#elif defined(__MWERKS__) 
#    define BOOST_FORCE_INCLUDE(f) __declspec(dllexport) f
#elif defined(__GCC__)
#    define BOOST_FORCE_INCLUDE(f) f __attribute__ ((used))
#endif

#ifndef BOOST_FORCE_INCLUDE
#    define BOOST_FORCE_INCLUDE(x) x
#endif

#endif // BOOST_SERIALIZATION_FORCE_INCLUDE_HPP
