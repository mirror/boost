/* boost random/detail/seed.hpp header file
 *
 * Copyright Steven Watanabe 2009
 * Distributed under the Boost Software License, Version 1.0. (See
 * accompanying file LICENSE_1_0.txt or copy at
 * http://www.boost.org/LICENSE_1_0.txt)
 *
 * See http://www.boost.org for most recent version including documentation.
 *
 * $Id$
 */

#ifndef BOOST_RANDOM_DETAIL_SEED_IMPL_HPP
#define BOOST_RANDOM_DETAIL_SEED_IMPL_HPP

#include <boost/cstdint.hpp>
#include <boost/integer/integer_mask.hpp>
#include <boost/integer/static_log2.hpp>
#include <boost/type_traits/is_signed.hpp>
#include <boost/type_traits/make_unsigned.hpp>
#include <boost/random/detail/const_mod.hpp>
#include <boost/random/detail/signed_unsigned_tools.hpp>

namespace boost {
namespace random {
namespace detail {

template<class Engine, int Bits, class Iter>
void generate_from_real(Engine& eng, Iter begin, Iter end)
{
    typedef typename Engine::result_type RealType;
    int remaining_bits = 0;
    boost::uint32_t saved_bits;
    RealType mult32 = 4294967296.0; // 2^32
    for(; begin != end; ++begin) {
        RealType val = eng();
        int available_bits = Bits;
        if(available_bits < 32 - remaining_bits) {
            saved_bits |= boost::uint32_t(val * mult32) >> remaining_bits;
            remaining_bits += available_bits;
        } else {
            if(remaining_bits != 0) {
                val *= boost::uint32_t(1) << (32 - remaining_bits);
                boost::uint32_t extra_bits = boost::uint32_t(val);
                val -= extra_bits;
                *begin++ = saved_bits | extra_bits;
                if(begin == end) break;
                available_bits -= 32 - remaining_bits;
                remaining_bits = 0;
            }
            for(; available_bits >= 32; available_bits -= 32) {
                val *= mult32;
                boost::uint32_t word = boost::uint32_t(val);
                val -= word;
                *begin++ = word;
                if(begin == end) break;
            }
            remaining_bits = available_bits;
            saved_bits = boost::uint32_t(val * mult32);
        }
    }
}

template<class Engine, class Iter>
void generate_from_int(Engine& eng, Iter begin, Iter end)
{
    typedef typename Engine::result_type IntType;
    typedef typename boost::make_unsigned<IntType>::type unsigned_type;
    int remaining_bits = 0;
    boost::uint32_t saved_bits;
    unsigned_type range = boost::random::detail::subtract<IntType>()((eng.max)(), (eng.min)());
    int bits = 0;
    unsigned_type mask = 0;
    for(; bits < std::numeric_limits<unsigned_type>::digits; ++bits)
    {
        unsigned_type test = mask | (unsigned_type(1) << bits);
        if(test <= range) {
            mask = test;
        } else {
            break;
        }
    }
    for(; begin != end; ++begin) {
        unsigned_type val;
        do {
            val = boost::random::detail::subtract<IntType>()(eng(), (eng.min)());
        } while(val > mask);
        int available_bits = bits;
        if(available_bits < 32 - remaining_bits) {
            saved_bits |= boost::uint32_t(val) << remaining_bits;
            remaining_bits += bits;
        } else {
            if(remaining_bits != 0) {
                boost::uint32_t extra_bits = boost::uint32_t(val) & ((boost::uint32_t(1) << (32 - remaining_bits)) - 1);
                val >>= 32 - remaining_bits;
                *begin++ = saved_bits | (extra_bits << remaining_bits);
                if(begin == end) break;
                available_bits -= 32 - remaining_bits;
                remaining_bits = 0;
            }
            for(; available_bits >= 32; available_bits -= 32) {
                boost::uint32_t word = boost::uint32_t(val);
                val >>= 32;
                *begin++ = word;
                if(begin == end) break;
            }
            remaining_bits = available_bits;
            saved_bits = static_cast<boost::uint32_t>(val);
        }
    }
}

template<class IntType, IntType m, class SeedSeq>
IntType seed_one_int(SeedSeq& seq)
{
    static const int log = ::boost::static_log2<m>::value;
    static const int k =
        (log + ((~(static_cast<IntType>(1) << log) & m)? 32 : 31)) / 32;
    boost::uint_least32_t array[log / 32 + 4];
    seq.generate(&array[0], &array[0] + k + 3);
    IntType s = 0;
    for(int j = 0; j < k; ++j) {
        IntType digit = IntType(array[j+3]) % m;
        IntType mult = IntType(1) << 32*j;
        s = const_mod<IntType, m>::mult_add(mult, digit, s);
    }
    return s;
}

// TODO: work in-place whenever possible
template<int w, std::size_t n, class SeedSeq, class UIntType>
void seed_array_int_impl(SeedSeq& seq, UIntType (&x)[n])
{
    boost::uint_least32_t storage[((w+31)/32) * n];
    seq.generate(&storage[0], &storage[0] + ((w+31)/32) * n);
    for(std::size_t j = 0; j < n; j++) {
        UIntType val = 0;
        for(std::size_t k = 0; k < (w+31)/32; ++k) {
            val += static_cast<UIntType>(storage[(w+31)/32*j + k]) << 32*k;
        }
        x[j] = val & ::boost::low_bits_mask_t<w>::sig_bits;
    }
}

template<int w, std::size_t n, class SeedSeq, class IntType>
inline void seed_array_int_impl(SeedSeq& seq, IntType (&x)[n], boost::mpl::true_)
{
    typedef typename boost::make_unsigned<IntType>::type unsigned_array[n];
    seed_array_int_impl<w>(seq, reinterpret_cast<unsigned_array&>(x));
}

template<int w, std::size_t n, class SeedSeq, class IntType>
inline void seed_array_int_impl(SeedSeq& seq, IntType (&x)[n], boost::mpl::false_)
{
    seed_array_int_impl<w>(seq, x);
}

template<int w, std::size_t n, class SeedSeq, class IntType>
inline void seed_array_int(SeedSeq& seq, IntType (&x)[n])
{
    seed_array_int_impl<w>(seq, x, boost::is_signed<IntType>());
}

}
}
}

#endif
