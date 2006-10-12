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
#define BOOST_DETAIL_LCAST_ASSERT(cond) BOOST_ASSERT(cond)
#else
#include <boost/static_assert.hpp>
#define BOOST_DETAIL_LCAST_ASSERT(cond) BOOST_STATIC_ASSERT(cond)
// Remember, static_cast is evaluated even inside dead branches.
#endif
#if BOOST_WORKAROUND(BOOST_MSVC, < 1300)
# include <boost/type_traits/is_same.hpp>
# include <boost/mpl/bool.hpp>
#endif 

namespace boost { namespace detail {

#ifdef _MSC_VER
#pragma warning (push)
// conditional expression is constant
#pragma warning (disable : 4127)
#endif

template<class T>
inline std::streamsize lcast_get_precision()
{
    typedef std::numeric_limits<T> limits;

    bool const is_floating = limits::is_specialized && !limits::is_exact;
    if(is_floating)
    { // Includes all built-in floating-point types, float, double ...
      // and UDT types for which digits (significand bits) is defined (not zero)

        bool const is_specialized_binary = is_floating &&
            limits::radix == 2 && limits::digits > 0;
        bool const is_specialized_decimal = is_floating &&
            limits::radix == 10 && limits::digits10 > 0;
        std::streamsize const precision_maxarg =
            integer_traits<std::streamsize>::const_max;
        if(is_specialized_binary)
        { // Floating-point types with
          // limist::digits defined by the specialization.

            unsigned long const digits = limits::digits;
            unsigned long const precision = 2UL + digits * 30103UL / 100000UL;
            // unsigned long is selected because it is at least 32-bits
            // and thus ULONG_MAX / 30103UL is big enough for all types.
            BOOST_DETAIL_LCAST_ASSERT(!is_specialized_binary ||
                    digits < ULONG_MAX / 30103UL &&
                    precision > limits::digits10 + 0UL &&
                    precision <= precision_maxarg + 0UL
                );
            return precision;
        }
        else if(is_specialized_decimal)
        {   // Decimal Floating-point type, most likely a User Defined Type
            // rather than a real floating-point hardware type.
            unsigned int const precision = limits::digits10 + 1U;
            BOOST_DETAIL_LCAST_ASSERT(!is_specialized_decimal ||
                    precision <= precision_maxarg + 0UL
                );
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
}

template<class T>
inline void lcast_set_precision(std::ios_base& stream
#if BOOST_WORKAROUND(BOOST_MSVC, < 1300)
                                , short = 0
#endif 
)
{
    stream.precision(lcast_get_precision<T>());
}

template<class Source, class Target>
inline void lcast_set_precision(std::ios_base& stream
#if BOOST_WORKAROUND(BOOST_MSVC, < 1300)
                                , long = 0
#endif 
)
{
    std::streamsize const s = lcast_get_precision<Source>();
    std::streamsize const t = lcast_get_precision<Target>();
    stream.precision(s > t ? s : t);
}

#ifdef _MSC_VER
#pragma warning (pop)
#endif

}}

#undef BOOST_DETAIL_LCAST_ASSERT

#endif //  BOOST_DETAIL_LCAST_PRECISION_HPP_INCLUDED

