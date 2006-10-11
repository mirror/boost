
// Copyright 2005-2006 Daniel James.
// Distributed under the Boost Software License, Version 1.0. (See accompanying
// file LICENSE_1_0.txt or copy at http://www.boost.org/LICENSE_1_0.txt)

//  Based on Peter Dimov's proposal
//  http://www.open-std.org/JTC1/SC22/WG21/docs/papers/2005/n1756.pdf
//  issue 6.18. 

#if !defined(BOOST_FUNCTIONAL_DETAIL_HASH_FLOAT_HEADER)
#define BOOST_FUNCTIONAL_DETAIL_HASH_FLOAT_HEADER

#if defined(_MSC_VER) && (_MSC_VER >= 1020)
# pragma once
#endif

#include <boost/functional/detail/float_functions.hpp>
#include <boost/integer/static_log2.hpp>
#include <boost/limits.hpp>
#include <boost/assert.hpp>

// Don't use fpclassify or _fpclass for stlport.
#if !defined(__SGI_STL_PORT) && !defined(_STLPORT_VERSION)
#  if defined(__GLIBCPP__) || defined(__GLIBCXX__)
// GNU libstdc++ 3
#    if (defined(__USE_ISOC99) || defined(_GLIBCXX_USE_C99_MATH)) && \
        !(defined(macintosh) || defined(__APPLE__) || defined(__APPLE_CC__))
#      define BOOST_HASH_USE_FPCLASSIFY
#    endif
#  elif (defined(_YVALS) && !defined(__IBMCPP__)) || defined(_CPPLIB_VER)
// Dinkumware Library, on Visual C++ 
#    if defined(BOOST_MSVC)
#      define BOOST_HASH_USE_FPCLASS
#    endif
#  endif
#endif

// On OpenBSD, numeric_limits is not reliable for long doubles, but
// the macros defined in <float.h> are.

#if defined(__OpenBSD__)
#include <float.h>
#endif

namespace boost
{
    namespace hash_detail
    {
        template <class T>
        struct limits : std::numeric_limits<T> {};

#if defined(__OpenBSD__)
        template <>
        struct limits<long double>
             : std::numeric_limits<long double>
        {
            static long double epsilon() {
                return LDBL_EPSILON;
            }

            static long double (max)() {
                return LDBL_MAX;
            }

            static long double (min)() {
                return LDBL_MIN;
            }

            BOOST_STATIC_CONSTANT(int, digits = LDBL_MANT_DIG);
            BOOST_STATIC_CONSTANT(int, max_exponent = LDBL_MAX_EXP);
            BOOST_STATIC_CONSTANT(int, min_exponent = LDBL_MIN_EXP);
        };
#endif // __OpenBSD__

        inline void hash_float_combine(std::size_t& seed, std::size_t value)
        {
            seed ^= value + (seed<<6) + (seed>>2);
        }

        template <class T>
        inline std::size_t float_hash_impl(T v)
        {
            int exp = 0;

            // The result of frexp is always between 0.5 and 1, so its
            // top bit will always be 1. Subtract by 0.5 to remove that.
            if(v >= 0) {
                v = boost::hash_detail::call_frexp(v, &exp) - T(0.5);
            }
            else {
                v = -boost::hash_detail::call_frexp(v, &exp) - T(0.5);
                exp = ~exp;
            }

            // TODO: Of course, this doesn't pass when hashing infinity or NaN.
            //BOOST_ASSERT(0 <= v && v < 0.5);

            v = boost::hash_detail::call_ldexp(v,
                    limits<std::size_t>::digits + 1);
            std::size_t seed = static_cast<std::size_t>(v);
            v -= seed;

            // ceiling(digits(T) * log2(radix(T))/ digits(size_t)) - 1;
            std::size_t const length
                = (limits<T>::digits *
                        boost::static_log2<limits<T>::radix>::value - 1)
                / limits<std::size_t>::digits;

            for(std::size_t i = 0; i < length; ++i)
            {
                v = boost::hash_detail::call_ldexp(v, limits<std::size_t>::digits);
                std::size_t part = static_cast<std::size_t>(v);
                v -= part;
                hash_float_combine(seed, part);
            }

            hash_float_combine(seed, exp);

            return seed;
        }

        template <class T>
        inline std::size_t float_hash_value(T v)
        {
#if defined(BOOST_HASH_USE_FPCLASSIFY)
            using namespace std;
            switch (fpclassify(v)) {
            case FP_ZERO:
                return 0;
            case FP_INFINITE:
                return (std::size_t)(v > 0 ? -1 : -2);
            case FP_NAN:
                return (std::size_t)(-3);
            case FP_NORMAL:
            case FP_SUBNORMAL:
                return float_hash_impl(v);
            default:
                BOOST_ASSERT(0);
                return 0;
            }
#elif defined(BOOST_HASH_USE_FPCLASS)
            switch(_fpclass(v)) {
            case _FPCLASS_NZ:
            case _FPCLASS_PZ:
                return 0;
            case _FPCLASS_PINF:
                return (std::size_t)(-1);
            case _FPCLASS_NINF:
                return (std::size_t)(-2);
            case _FPCLASS_SNAN:
            case _FPCLASS_QNAN:
                return (std::size_t)(-3);
            case _FPCLASS_NN:
            case _FPCLASS_ND:
                return float_hash_impl(v);
            case _FPCLASS_PD:
            case _FPCLASS_PN:
                return float_hash_impl(v);
            default:
                BOOST_ASSERT(0);
                return 0;
            }
#else
            return v == 0 ? 0 : float_hash_impl(v);
#endif
        }
    }
}

#endif
