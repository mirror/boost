//  (C) Copyright Boost.org 2001. Permission to copy, use, modify, sell and
//  distribute this software is granted provided this copyright notice appears
//  in all copies. This software is provided "as is" without express or implied
//  warranty, and with no claim as to its suitability for any purpose.

//  See http://www.boost.org for most recent version.

//  Intel compiler setup:

#include "boost/config/compiler/common_edg.hpp"

#ifdef __ICL
#  define BOOST_COMPILER "Intel C++ version " BOOST_STRINGIZE(__ICL)
#  define BOOST_INTEL_CXX_VERSION __ICL
#else
#  define BOOST_COMPILER "Intel C++ version " BOOST_STRINGIZE(__ICC)
#  define BOOST_INTEL_CXX_VERSION __ICC
#endif

#if (BOOST_INTEL_CXX_VERSION <= 600) || !defined(BOOST_STRICT_CONFIG)

#  if defined(_MSC_VER)
      // Intel C++ 5.0.1 uses EDG 2.45, but fails to activate Koenig lookup
      // in the frontend even in "strict" mode.  (reported by Kirk Klobe)
      // Intel C++ 6.0 (currently in Beta test) doesn't have any front-end
      // changes at all.  (reported by Kirk Klobe)
#     ifndef BOOST_NO_ARGUMENT_DEPENDENT_LOOKUP
#        define BOOST_NO_ARGUMENT_DEPENDENT_LOOKUP
#     endif
#     define BOOST_NO_EXPLICIT_FUNCTION_TEMPLATE_ARGUMENTS
#     define BOOST_NO_SWPRINTF
#     define BOOST_NO_INCLASS_MEMBER_INITIALIZATION
#  endif

#endif

#ifdef _MSC_VER
#  ifndef _NATIVE_WCHAR_T_DEFINED
#     define BOOST_NO_INTRINSIC_WCHAR_T
#  endif
#  define BOOST_NO_SWPRINTF
#endif


//
// versions check:
// we don't support Intel prior to version 5.0:
#if BOOST_INTEL_CXX_VERSION < 500
#  error "Compiler not supported or configured - please reconfigure"
#endif
//
// last known and checked version is 500:
#if (BOOST_INTEL_CXX_VERSION > 500)
#  if defined(BOOST_ASSERT_CONFIG)
#     error "Unknown compiler version - please run the configure tests and report the results"
#  elif defined(_MSC_VER)
#     warning "Unknown compiler version - please run the configure tests and report the results"
#  endif
#endif


