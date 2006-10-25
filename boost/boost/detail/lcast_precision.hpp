// Copyright Alexander Nasonov & Paul A. Bristow 2006.

// Use, modification and distribution are subject to the
// Boost Software License, Version 1.0.
// (See accompanying file LICENSE_1_0.txt
// or copy at http://www.boost.org/LICENSE_1_0.txt)

#ifndef BOOST_DETAIL_LCAST_PRECISION_HPP_INCLUDED
#define BOOST_DETAIL_LCAST_PRECISION_HPP_INCLUDED

#include <climits>
#include <ios>
#include <limits>

#include <boost/config.hpp>
#include <boost/integer_traits.hpp>

#ifdef BOOST_NO_LIMITS_COMPILE_TIME_CONSTANTS
#include <boost/assert.hpp>
#else
#include <boost/static_assert.hpp>
#endif

namespace boost { namespace detail {

#ifndef BOOST_NO_LIMITS_COMPILE_TIME_CONSTANTS
// Calculate an argument to pass to std::ios_base::precision from
// lexical_cast. See alternative implementation for broken standard
// libraries in lcast_get_precision below. Keep them in sync, please.
template<class T>
struct lcast_precision
{
    typedef std::numeric_limits<T> limits;

    BOOST_STATIC_CONSTANT(bool, use_default_precision =
            !limits::is_specialized || limits::is_exact
        );

    BOOST_STATIC_CONSTANT(bool, is_specialized_bin =
            !use_default_precision &&
            limits::radix == 2 && limits::digits > 0
        );

    BOOST_STATIC_CONSTANT(bool, is_specialized_dec =
            !use_default_precision &&
            limits::radix == 10 && limits::digits10 > 0
        );

    BOOST_STATIC_CONSTANT(std::streamsize, streamsize_max =
            boost::integer_traits<std::streamsize>::const_max
        );

    BOOST_STATIC_CONSTANT(unsigned int, precision_dec = limits::digits10 + 1U);

    BOOST_STATIC_ASSERT(!is_specialized_dec ||
            precision_dec <= streamsize_max + 0UL
        );

    BOOST_STATIC_CONSTANT(unsigned long, precision_bin =
            2UL + limits::digits * 30103UL / 100000UL
        );

    BOOST_STATIC_ASSERT(!is_specialized_bin ||
            limits::digits + 0UL < ULONG_MAX / 30103UL &&
            precision_bin > limits::digits10 + 0UL &&
            precision_bin <= streamsize_max + 0UL
        );

    BOOST_STATIC_CONSTANT(std::streamsize, value =
            is_specialized_bin ? precision_bin
                               : is_specialized_dec ? precision_dec : 6
        );
};
#endif

template<class T>
inline std::streamsize lcast_get_precision()
{
#if !defined(BOOST_NO_LIMITS_COMPILE_TIME_CONSTANTS)
    return lcast_precision<T>::value;
#else // Follow lcast_precision algorithm at run-time:

    typedef std::numeric_limits<T> limits;

    bool const use_default_precision =
        !limits::is_specialized || limits::is_exact;

    if(!use_default_precision)
    { // Includes all built-in floating-point types, float, double ...
      // and UDT types for which digits (significand bits) is defined (not zero)

        bool const is_specialized_bin =
            limits::radix == 2 && limits::digits > 0;
        bool const is_specialized_dec =
            limits::radix == 10 && limits::digits10 > 0;
        std::streamsize const streamsize_max =
            (boost::integer_traits<std::streamsize>::max)();

        if(is_specialized_bin)
        { // Floating-point types with
          // limits::digits defined by the specialization.

            unsigned long const digits = limits::digits;
            unsigned long const precision = 2UL + digits * 30103UL / 100000UL;
            // unsigned long is selected because it is at least 32-bits
            // and thus ULONG_MAX / 30103UL is big enough for all types.
            BOOST_ASSERT(
                    digits < ULONG_MAX / 30103UL &&
                    precision > limits::digits10 + 0UL &&
                    precision <= streamsize_max + 0UL
                );
            return precision;
        }
        else if(is_specialized_dec)
        {   // Decimal Floating-point type, most likely a User Defined Type
            // rather than a real floating-point hardware type.
            unsigned int const precision = limits::digits10 + 1U;
            BOOST_ASSERT(precision <= streamsize_max + 0UL);
            return precision;
        }
    }

    // Integral type (for which precision has no effect)
    // or type T for which limits is NOT specialized,
    // so assume stream precision remains the default 6 decimal digits.
    // Warning: if your User-defined Floating-point type T is NOT specialized,
    // then you may lose accuracy by only using 6 decimal digits.
    // To avoid this, you need to specialize T with either
    // radix == 2 and digits == the number of significand bits,
    // OR
    // radix = 10 and digits10 == the number of decimal digits.

    return 6;
#endif
}

template<class T>
inline void lcast_set_precision(std::ios_base& stream, T* = 0)
{
    stream.precision(lcast_get_precision<T>());
}

template<class Source, class Target>
inline void lcast_set_precision(std::ios_base& stream, Source* = 0, Target* = 0)
{
    std::streamsize const s = lcast_get_precision<Source>();
    std::streamsize const t = lcast_get_precision<Target>();
    stream.precision(s > t ? s : t);
}

}}

#endif //  BOOST_DETAIL_LCAST_PRECISION_HPP_INCLUDED

