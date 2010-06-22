/* boost random/mersenne_twister.hpp header file
 *
 * Copyright Jens Maurer 2000-2001
 * Copyright Steven Watanabe 2010
 * Distributed under the Boost Software License, Version 1.0. (See
 * accompanying file LICENSE_1_0.txt or copy at
 * http://www.boost.org/LICENSE_1_0.txt)
 *
 * See http://www.boost.org for most recent version including documentation.
 *
 * $Id$
 *
 * Revision history
 *  2001-02-18  moved to individual header files
 */

#ifndef BOOST_RANDOM_MERSENNE_TWISTER_HPP
#define BOOST_RANDOM_MERSENNE_TWISTER_HPP

#include <iosfwd>
#include <stdexcept>
#include <boost/config.hpp>
#include <boost/cstdint.hpp>
#include <boost/random/detail/config.hpp>
#include <boost/random/detail/ptr_helper.hpp>
#include <boost/random/detail/seed.hpp>

namespace boost {
namespace random {

/**
 * Instantiations of class template mersenne_twister_engine model a
 * \pseudo_random_number_generator. It uses the algorithm described in
 *
 *  @blockquote
 *  "Mersenne Twister: A 623-dimensionally equidistributed uniform
 *  pseudo-random number generator", Makoto Matsumoto and Takuji Nishimura,
 *  ACM Transactions on Modeling and Computer Simulation: Special Issue on
 *  Uniform Random Number Generation, Vol. 8, No. 1, January 1998, pp. 3-30. 
 *  @endblockquote
 *
 * @xmlnote
 * The boost variant has been implemented from scratch and does not
 * derive from or use mt19937.c provided on the above WWW site. However, it
 * was verified that both produce identical output.
 * @endxmlnote
 *
 * The seeding from an integer was changed in April 2005 to address a
 * <a href="http://www.math.sci.hiroshima-u.ac.jp/~m-mat/MT/MT2002/emt19937ar.html">weakness</a>.
 * 
 * The quality of the generator crucially depends on the choice of the
 * parameters.  User code should employ one of the sensibly parameterized
 * generators such as \mt19937 instead.
 *
 * The generator requires considerable amounts of memory for the storage of
 * its state array. For example, \mt11213b requires about 1408 bytes and
 * \mt19937 requires about 2496 bytes.
 */
template<class UIntType,
         std::size_t w, std::size_t n, std::size_t m, std::size_t r,
         UIntType a, std::size_t u, UIntType d, std::size_t s,
         UIntType b, std::size_t t,
         UIntType c, std::size_t l, UIntType f>
class mersenne_twister_engine
{
public:
    typedef UIntType result_type;
    BOOST_STATIC_CONSTANT(std::size_t, word_size = w);
    BOOST_STATIC_CONSTANT(std::size_t, state_size = n);
    BOOST_STATIC_CONSTANT(std::size_t, shift_size = m);
    BOOST_STATIC_CONSTANT(std::size_t, mask_bits = r);
    BOOST_STATIC_CONSTANT(UIntType, xor_mask = a);
    BOOST_STATIC_CONSTANT(std::size_t, tempering_u = u);
    BOOST_STATIC_CONSTANT(UIntType, tempering_d = d);
    BOOST_STATIC_CONSTANT(std::size_t, tempering_s = s);
    BOOST_STATIC_CONSTANT(UIntType, tempering_b = b);
    BOOST_STATIC_CONSTANT(std::size_t, tempering_t = t);
    BOOST_STATIC_CONSTANT(UIntType, tempering_c = c);
    BOOST_STATIC_CONSTANT(std::size_t, tempering_l = l);
    BOOST_STATIC_CONSTANT(UIntType, initialization_multiplier = f);
    BOOST_STATIC_CONSTANT(UIntType, default_seed = 5489u);
  
    // backwards compatibility
    BOOST_STATIC_CONSTANT(UIntType, parameter_a = a);
    BOOST_STATIC_CONSTANT(std::size_t, output_u = u);
    BOOST_STATIC_CONSTANT(std::size_t, output_s = s);
    BOOST_STATIC_CONSTANT(UIntType, output_b = b);
    BOOST_STATIC_CONSTANT(std::size_t, output_t = t);
    BOOST_STATIC_CONSTANT(UIntType, output_c = c);
    BOOST_STATIC_CONSTANT(std::size_t, output_l = l);
    
    // old Boost.Random concept requirements
    BOOST_STATIC_CONSTANT(bool, has_fixed_range = false);


    /**
     * Constructs a @c mersenne_twister_engine and calls @c seed().
     */
    mersenne_twister_engine() { seed(); }

    /**
     * Constructs a @c mersenne_twister_engine and calls @c seed(value).
     */
    BOOST_RANDOM_DETAIL_ARITHMETIC_CONSTRUCTOR(mersenne_twister_engine, UIntType, value)
    { seed(value); }
    template<class It> mersenne_twister_engine(It& first, It last)
    { seed(first,last); }

    /**
     * Constructs a mersenne_twister_engine and calls @c seed(gen).
     *
     * @xmlnote
     * The copy constructor will always be preferred over
     * the templated constructor.
     * @endxmlnote
     */
    BOOST_RANDOM_DETAIL_SEED_SEQ_CONSTRUCTOR(mersenne_twister_engine, SeedSeq, seq)
    { seed(seq); }

    // compiler-generated copy ctor and assignment operator are fine

    /** Calls @c seed(default_seed). */
    void seed() { seed(default_seed); }

    /**
     * Sets the state x(0) to v mod 2w. Then, iteratively,
     * sets x(i) to
     * (i + f * (x(i-1) xor (x(i-1) rshift w-2))) mod 2<sup>w</sup>
     * for i = 1 .. n-1. x(n) is the first value to be returned by operator().
     */
    BOOST_RANDOM_DETAIL_ARITHMETIC_SEED(mersenne_twister_engine, UIntType, value)
    {
        // New seeding algorithm from 
        // http://www.math.sci.hiroshima-u.ac.jp/~m-mat/MT/MT2002/emt19937ar.html
        // In the previous versions, MSBs of the seed affected only MSBs of the
        // state x[].
        const UIntType mask = (max)();
        x[0] = value & mask;
        for (i = 1; i < n; i++) {
            // See Knuth "The Art of Computer Programming" Vol. 2, 3rd ed., page 106
            x[i] = (f * (x[i-1] ^ (x[i-1] >> (w-2))) + i) & mask;
        }
    }
    
    /**
     * Seeds a mersenne_twister_engine using values produced by seq.generate().
     */
    BOOST_RANDOM_DETAIL_SEED_SEQ_SEED(mersenne_twister_engine, SeeqSeq, seq)
    {
        boost::uint_least32_t storage[((w+31)/32) * n];
        seq.generate(&storage[0], &storage[0] + ((w+31)/32) * n);
        for(std::size_t j = 0; j < n; j++) {
            UIntType val = 0;
            for(std::size_t k = 0; k < (w+31)/32; ++k) {
                val += storage[(w+31)/32*j + k] << 32*k;
            }
            x[j] = val;
        }
        i = n;

        // fix up the state if it's all zeroes.
        if((x[0] & (~static_cast<UIntType>(0) << r)) == 0) {
            for(std::size_t j = 1; i < n; ++j) {
                if(x[j] != 0) return;
            }
            x[0] = static_cast<UIntType>(1) << (w-1);
        }
    }

    /** Sets the state of the generator using values from an iterator range. */
    template<class It>
    void seed(It& first, It last)
    {
        std::size_t j;
        for(j = 0; j < n && first != last; ++j, ++first)
            x[j] = *first;
        i = n;
        if(first == last && j < n)
            throw std::invalid_argument("mersenne_twister_engine::seed");
    }
  
    /** Returns the smallest value that the generator can produce. */
    static result_type min BOOST_PREVENT_MACRO_SUBSTITUTION ()
    { return 0; }
    /** Returns the largest value that the generator can produce. */
    static result_type max BOOST_PREVENT_MACRO_SUBSTITUTION ()
    {
        // avoid "left shift count >= width of type" warning
        result_type res = 0;
        for(std::size_t j = 0; j < w; ++j)
            res |= (static_cast<result_type>(1) << j);
        return res;
    }
    
    /** Produces the next value of the generator. */
    result_type operator()();

    /** Fills a range with random values */
    template<class Iter>
    void generate(Iter first, Iter last)
    {
        for(; first != last; ++first) {
            *first = (*this)();
        }
    }

#ifndef BOOST_NO_LONG_LONG
    /**
     * Advances the state of the generator by @c z steps.  Equivalent to
     *
     * @code
     * for(unsigned long long i = 0; i < z; ++i) {
     *     gen();
     * }
     * @endcode
     */
    void discard(boost::ulong_long_type z)
    {
        for(boost::ulong_long_type j = 0; j < z; ++j) {
            (*this)();
        }
    }
#endif

#ifndef BOOST_RANDOM_NO_STREAM_OPERATORS
    /** Writes a mersenne_twister_engine to a @c std::ostream */
    template<class CharT, class Traits>
    friend std::basic_ostream<CharT,Traits>&
    operator<<(std::basic_ostream<CharT,Traits>& os,
               const mersenne_twister_engine& mt)
    {
        for(std::size_t j = 0; j < mt.state_size; ++j)
            os << mt.compute(j) << " ";
        return os;
    }
    
    /** Reads a mersenne_twister_engine from a @c std::istream */
    template<class CharT, class Traits>
    friend std::basic_istream<CharT,Traits>&
    operator>>(std::basic_istream<CharT,Traits>& is, mersenne_twister_engine& mt)
    {
        for(std::size_t j = 0; j < mt.state_size; ++j)
            is >> mt.x[j] >> std::ws;
        // MSVC (up to 7.1) and Borland (up to 5.64) don't handle the template
        // value parameter "n" available from the class template scope, so use
        // the static constant with the same value
        mt.i = mt.state_size;
        return is;
    }
#endif

    /**
     * Returns true if the two generators are in the same state,
     * and will thus produce identical sequences.
     */
    friend bool operator==(const mersenne_twister_engine& x, const mersenne_twister_engine& y)
    {
        for(std::size_t j = 0; j < state_size; ++j)
            if(x.compute(j) != y.compute(j))
                return false;
        return true;
    }
    
    /**
     * Returns true if the two generators are in different states.
     */
    friend bool operator!=(const mersenne_twister_engine& x, const mersenne_twister_engine& y)
    { return !(x == y); }

private:
    /// \cond hide_private_members
    // returns x(i-n+index), where index is in 0..n-1
    UIntType compute(unsigned int index) const
    {
        // equivalent to (i-n+index) % 2n, but doesn't produce negative numbers
        return x[ (i + n + index) % (2*n) ];
    }
    void twist(int block);
    /// \endcond

    // state representation: next output is o(x(i))
    //   x[0]  ... x[k] x[k+1] ... x[n-1]     x[n]     ... x[2*n-1]   represents
    //  x(i-k) ... x(i) x(i+1) ... x(i-k+n-1) x(i-k-n) ... x[i(i-k-1)]
    // The goal is to always have x(i-n) ... x(i-1) available for
    // operator== and save/restore.

    UIntType x[2*n]; 
    std::size_t i;
};

#ifndef BOOST_NO_INCLASS_MEMBER_INITIALIZATION
//  A definition is required even for integral static constants
#define BOOST_RANDOM_MT_DEFINE_CONSTANT(type, name)                         \
template<class UIntType, std::size_t w, std::size_t n, std::size_t m,       \
    std::size_t r, UIntType a, std::size_t u, UIntType d, std::size_t s,    \
    UIntType b, std::size_t t, UIntType c, std::size_t l, UIntType f>       \
const type mersenne_twister_engine<UIntType,w,n,m,r,a,u,d,s,b,t,c,l,f>::name
BOOST_RANDOM_MT_DEFINE_CONSTANT(std::size_t, word_size);
BOOST_RANDOM_MT_DEFINE_CONSTANT(std::size_t, state_size);
BOOST_RANDOM_MT_DEFINE_CONSTANT(std::size_t, shift_size);
BOOST_RANDOM_MT_DEFINE_CONSTANT(std::size_t, mask_bits);
BOOST_RANDOM_MT_DEFINE_CONSTANT(UIntType, xor_mask);
BOOST_RANDOM_MT_DEFINE_CONSTANT(std::size_t, tempering_u);
BOOST_RANDOM_MT_DEFINE_CONSTANT(UIntType, tempering_d);
BOOST_RANDOM_MT_DEFINE_CONSTANT(std::size_t, tempering_s);
BOOST_RANDOM_MT_DEFINE_CONSTANT(UIntType, tempering_b);
BOOST_RANDOM_MT_DEFINE_CONSTANT(std::size_t, tempering_t);
BOOST_RANDOM_MT_DEFINE_CONSTANT(UIntType, tempering_c);
BOOST_RANDOM_MT_DEFINE_CONSTANT(std::size_t, tempering_l);
BOOST_RANDOM_MT_DEFINE_CONSTANT(UIntType, initialization_multiplier);
BOOST_RANDOM_MT_DEFINE_CONSTANT(UIntType, default_seed);
BOOST_RANDOM_MT_DEFINE_CONSTANT(UIntType, parameter_a);
BOOST_RANDOM_MT_DEFINE_CONSTANT(std::size_t, output_u );
BOOST_RANDOM_MT_DEFINE_CONSTANT(std::size_t, output_s);
BOOST_RANDOM_MT_DEFINE_CONSTANT(UIntType, output_b);
BOOST_RANDOM_MT_DEFINE_CONSTANT(std::size_t, output_t);
BOOST_RANDOM_MT_DEFINE_CONSTANT(UIntType, output_c);
BOOST_RANDOM_MT_DEFINE_CONSTANT(std::size_t, output_l);
BOOST_RANDOM_MT_DEFINE_CONSTANT(bool, has_fixed_range);
#undef BOOST_RANDOM_MT_DEFINE_CONSTANT
#endif

/// \cond hide_private_members
template<class UIntType,
         std::size_t w, std::size_t n, std::size_t m, std::size_t r,
         UIntType a, std::size_t u, UIntType d, std::size_t s,
         UIntType b, std::size_t t,
         UIntType c, std::size_t l, UIntType f>
void
mersenne_twister_engine<UIntType,w,n,m,r,a,u,d,s,b,t,c,l,f>::twist(int block)
{
    const UIntType upper_mask = (~static_cast<UIntType>(0)) << r;
    const UIntType lower_mask = ~upper_mask;

    if(block == 0) {
        for(std::size_t j = n; j < 2*n; j++) {
            UIntType y = (x[j-n] & upper_mask) | (x[j-(n-1)] & lower_mask);
            x[j] = x[j-(n-m)] ^ (y >> 1) ^ (y&1 ? a : 0);
        }
    } else if (block == 1) {
        // split loop to avoid costly modulo operations
        {  // extra scope for MSVC brokenness w.r.t. for scope
            for(std::size_t j = 0; j < n-m; j++) {
                UIntType y = (x[j+n] & upper_mask) | (x[j+n+1] & lower_mask);
                x[j] = x[j+n+m] ^ (y >> 1) ^ (y&1 ? a : 0);
            }
        }
    
        for(std::size_t j = n-m; j < n-1; j++) {
            UIntType y = (x[j+n] & upper_mask) | (x[j+n+1] & lower_mask);
            x[j] = x[j-(n-m)] ^ (y >> 1) ^ (y&1 ? a : 0);
        }
        // last iteration
        UIntType y = (x[2*n-1] & upper_mask) | (x[0] & lower_mask);
        x[n-1] = x[m-1] ^ (y >> 1) ^ (y&1 ? a : 0);
        i = 0;
    }
}
/// \endcond

template<class UIntType,
         std::size_t w, std::size_t n, std::size_t m, std::size_t r,
         UIntType a, std::size_t u, UIntType d, std::size_t s,
         UIntType b, std::size_t t,
         UIntType c, std::size_t l, UIntType f>
inline typename mersenne_twister_engine<UIntType,w,n,m,r,a,u,d,s,b,t,c,l,f>::result_type
mersenne_twister_engine<UIntType,w,n,m,r,a,u,d,s,b,t,c,l,f>::operator()()
{
    if(i == n)
        twist(0);
    else if(i >= 2*n)
        twist(1);
    // Step 4
    UIntType z = x[i];
    ++i;
    z ^= ((z >> u) & d);
    z ^= ((z << s) & b);
    z ^= ((z << t) & c);
    z ^= (z >> l);
    return z;
}

/**
 * The specializations \mt11213b and \mt19937 are from
 *
 *  @blockquote
 *  "Mersenne Twister: A 623-dimensionally equidistributed
 *  uniform pseudo-random number generator", Makoto Matsumoto
 *  and Takuji Nishimura, ACM Transactions on Modeling and
 *  Computer Simulation: Special Issue on Uniform Random Number
 *  Generation, Vol. 8, No. 1, January 1998, pp. 3-30. 
 *  @endblockquote
 */
typedef random::mersenne_twister_engine<uint_fast32_t,32,351,175,19,0xccab8ee7,
    11,0xffffffff,7,0x31b6ab00,15,0xffe50000,17,1812433253> mt11213b;

/**
 * The specializations \mt11213b and \mt19937 are from
 *
 *  @blockquote
 *  "Mersenne Twister: A 623-dimensionally equidistributed
 *  uniform pseudo-random number generator", Makoto Matsumoto
 *  and Takuji Nishimura, ACM Transactions on Modeling and
 *  Computer Simulation: Special Issue on Uniform Random Number
 *  Generation, Vol. 8, No. 1, January 1998, pp. 3-30. 
 *  @endblockquote
 */
typedef random::mersenne_twister_engine<uint_fast32_t,32,624,397,31,0x9908b0df,
    11,0xffffffff,7,0x9d2c5680,15,0xefc60000,18,1812433253> mt19937;

#if !defined(BOOST_NO_INT64_T) && !defined(BOOST_NO_INTEGRAL_INT64_T)
typedef random::mersenne_twister_engine<uint_fast64_t,64,312,156,31,
    UINT64_C(0xb5026f5aa96619e9),29,UINT64_C(0x5555555555555555),17,
    UINT64_C(0x71d67fffeda60000),37,UINT64_C(0xfff7eee000000000),43,
    UINT64_C(6364136223846793005)> mt19937_64;
#endif

} // namespace random

using random::mt11213b;
using random::mt19937;
using random::mt19937_64;

} // namespace boost

BOOST_RANDOM_PTR_HELPER_SPEC(boost::mt11213b)
BOOST_RANDOM_PTR_HELPER_SPEC(boost::mt19937)
BOOST_RANDOM_PTR_HELPER_SPEC(boost::mt19937_64)

#endif // BOOST_RANDOM_MERSENNE_TWISTER_HPP
