//  (C) Copyright Daniel James 2005.
//  Use, modification and distribution are subject to the
//  Boost Software License, Version 1.0. (See accompanying file
//  LICENSE_1_0.txt or copy at http://www.boost.org/LICENSE_1_0.txt)

#if !defined(BOOST_FUNCTIONAL_DETAIL_FLOAT_FUNCTIONS_HPP)
#define BOOST_FUNCTIONAL_DETAIL_FLOAT_FUNCTIONS_HPP

#if defined(_MSC_VER) && (_MSC_VER >= 1020)
# pragma once
#endif

// The C++ standard requires that the C float functions are overloarded
// for float, double and long double in the std namespace, but some of the older
// library implementations don't support this. On some that don't, the C99
// float functions (frexpf, frexpl, etc.) are available.

// This is just based on the compilers I've got access to, but it should
// do something sensible on most compilers.

#if defined(__SGI_STL_PORT) || defined(_STLPORT_VERSION)
#  if defined(BOOST_MSVC) && BOOST_MSVC <= 1200
#    define BOOST_HASH_USE_C99_FLOAT_FUNCS
#  else
#    define BOOST_HASH_USE_OVERLOAD_FLOAT_FUNCS
#  endif
#elif defined(_RWSTD_VER) && defined(__BORLANDC__)
#  define BOOST_HASH_USE_C99_FLOAT_FUNCS
#  define BOOST_HASH_C99_NO_FLOAT_FUNCS
#elif defined(__GLIBCPP__) || defined(__GLIBCXX__)
#  define BOOST_HASH_USE_OVERLOAD_FLOAT_FUNCS
#elif defined(__STL_CONFIG_H)
// This might just be for gcc-2.95
// And cygwin might not have the C99 functions
#  define BOOST_HASH_USE_C99_FLOAT_FUNCS
#elif (defined(_YVALS) && !defined(__IBMCPP__)) || defined(_CPPLIB_VER)
// Overloaded float functions were probably introduced at an earlier version.
#  if defined(_CPPLIB_VER) && (_CPPLIB_VER >= 402)
#    define BOOST_HASH_USE_OVERLOAD_FLOAT_FUNCS
#  else
#    define BOOST_HASH_USE_C99_FLOAT_FUNCS
#  endif
#elif defined(__DMC__)
#  define BOOST_HASH_USE_C99_FLOAT_FUNCS
#else
#  define BOOST_HASH_USE_OVERLOAD_FLOAT_FUNCS
#endif

namespace boost
{
    namespace hash_detail
    {

        inline float call_ldexp(float v, int exp)
        {
            using namespace std;
#if defined(BOOST_HASH_USE_OVERLOAD_FLOAT_FUNCS) || \
    defined(BOOST_HASH_C99_NO_FLOAT_FUNCS)
            return ldexp(v, exp);
#else
            return ldexpf(v, exp);
#endif
        }

        inline double call_ldexp(double v, int exp)
        {
            using namespace std;
            return ldexp(v, exp);
        }

        inline long double call_ldexp(long double v, int exp)
        {
            using namespace std;
#if defined(BOOST_HASH_USE_OVERLOAD_FLOAT_FUNCS)
            return ldexp(v, exp);
#else
            return ldexpl(v, exp);
#endif
        }

        inline float call_frexp(float v, int* exp)
        {
            using namespace std;
#if defined(BOOST_HASH_USE_OVERLOAD_FLOAT_FUNCS) || \
    defined(BOOST_HASH_C99_NO_FLOAT_FUNCS)
            return frexp(v, exp);
#else
            return frexpf(v, exp);
#endif
        }

        inline double call_frexp(double v, int* exp)
        {
            using namespace std;
            return frexp(v, exp);
        }

        inline long double call_frexp(long double v, int* exp)
        {
            using namespace std;
#if defined(BOOST_HASH_USE_OVERLOAD_FLOAT_FUNCS)
            return frexp(v, exp);
#else
            return frexpl(v, exp);
#endif
        }
    }
}

#if defined(BOOST_HASH_USE_C99_FLOAT_FUNCS)
#undef BOOST_HASH_USE_C99_FLOAT_FUNCS
#endif

#if defined(BOOST_HASH_USE_OVERLOAD_FLOAT_FUNCS)
#undef BOOST_HASH_USE_OVERLOAD_FLOAT_FUNCS
#endif

#if defined(BOOST_HASH_C99_NO_FLOAT_FUNCS)
#undef BOOST_HASH_C99_NO_FLOAT_FUNCS
#endif

#endif
