/* boost random/subtract_with_carry.hpp header file
 *
 * Copyright Jens Maurer 2002
 * Distributed under the Boost Software License, Version 1.0. (See
 * accompanying file LICENSE_1_0.txt or copy at
 * http://www.boost.org/LICENSE_1_0.txt)
 *
 * See http://www.boost.org for most recent version including documentation.
 *
 * $Id$
 *
 * Revision history
 *  2002-03-02  created
 */

#ifndef BOOST_RANDOM_SUBTRACT_WITH_CARRY_HPP
#define BOOST_RANDOM_SUBTRACT_WITH_CARRY_HPP

#include <boost/config/no_tr1/cmath.hpp>         // std::pow
#include <iostream>
#include <algorithm>     // std::equal
#include <stdexcept>
#include <boost/config.hpp>
#include <boost/limits.hpp>
#include <boost/cstdint.hpp>
#include <boost/static_assert.hpp>
#include <boost/integer/static_log2.hpp>
#include <boost/detail/workaround.hpp>
#include <boost/random/detail/config.hpp>
#include <boost/random/detail/seed.hpp>
#include <boost/random/detail/operators.hpp>
#include <boost/random/linear_congruential.hpp>


namespace boost {
namespace random {

/**
 * Instantiations of @c subtract_with_carry_engine model a
 * \pseudo_random_number_generator.  The algorithm is
 * described in
 *
 *  @blockquote
 *  "A New Class of Random Number Generators", George
 *  Marsaglia and Arif Zaman, Annals of Applied Probability,
 *  Volume 1, Number 3 (1991), 462-480.
 *  @endblockquote
 */
template<class IntType, std::size_t w, std::size_t s, std::size_t r>
class subtract_with_carry_engine
{
public:
    typedef IntType result_type;
    BOOST_STATIC_CONSTANT(std::size_t, word_size = w);
    BOOST_STATIC_CONSTANT(std::size_t, long_lag = r);
    BOOST_STATIC_CONSTANT(std::size_t, short_lag = s);
    BOOST_STATIC_CONSTANT(uint32_t, default_seed = 19780503u);

    // Required by the old Boost.Random concepts
    BOOST_STATIC_CONSTANT(bool, has_fixed_range = false);
    // Backwards compatibility
    BOOST_STATIC_CONSTANT(result_type, modulus = (result_type(1) << w));
    
    BOOST_STATIC_ASSERT(std::numeric_limits<result_type>::is_integer);

    /**
     * Constructs a new @c subtract_with_carry_engine and seeds
     * it with the default seed.
     */
    subtract_with_carry_engine() { seed(); }
    /**
     * Constructs a new @c subtract_with_carry_engine and seeds
     * it with @c value.
     */
    BOOST_RANDOM_DETAIL_ARITHMETIC_CONSTRUCTOR(subtract_with_carry_engine,
                                               uint32_t, value)
    { seed(value); }
    /**
     * Constructs a new @c subtract_with_carry_engine and seeds
     * it with values produced by @c seq.generate().
     */
    BOOST_RANDOM_DETAIL_SEED_SEQ_CONSTRUCTOR(subtract_with_carry_engine,
                                             SeedSeq, seq)
    { seed(seq); }
    /**
     * Constructs a new @c subtract_with_carry_engine and seeds
     * it with values from a range.  first is updated to point
     * one past the last value consumed.  If there are not
     * enough elements in the range to fill the entire state of
     * the generator, throws @c std::invalid_argument.
     */
    template<class It> subtract_with_carry_engine(It& first, It last)
    { seed(first,last); }

    // compiler-generated copy ctor and assignment operator are fine

    /** Seeds the generator with the default seed. */
    void seed() { seed(default_seed); }
    BOOST_RANDOM_DETAIL_ARITHMETIC_SEED(subtract_with_carry_engine,
                                        uint32_t, value)
    {
        linear_congruential_engine<int32_t,40014,0,2147483563> intgen(value);
        seed(intgen);
    }

    /** Seeds the generator with values produced by @c seq.generate(). */
    BOOST_RANDOM_DETAIL_SEED_SEQ_SEED(subtract_with_carry, SeedSeq, seq)
    {
        uint32_t storage[((w+31)/32) * long_lag];
        seq.generate(&storage[0], &storage[0] + ((w+31)/32) * long_lag);
        for(std::size_t j = 0; j < long_lag; j++) {
            IntType val = 0;
            for(std::size_t k = 0; k < (w+31)/32; ++k) {
                result_type inc =
                    static_cast<result_type>(storage[(w+31)/32*j + k]);
                val += inc << 32*k;
            }
            x[j] = val % modulus;
        }
        carry = (x[long_lag-1] == 0);
        k = 0;
    }

    /**
     * Seeds the generator with values from a range.  Updates @c first to
     * point one past the last consumed value.  If the range does not
     * contain enough elements to fill the entire state of the generator,
     * throws @c std::invalid_argument.
     */
    template<class It>
    void seed(It& first, It last)
    {
        unsigned int j;
        for(j = 0; j < long_lag && first != last; ++j, ++first)
            x[j] = *first % modulus;
        if(first == last && j < long_lag)
            throw std::invalid_argument("subtract_with_carry::seed");
        carry = (x[long_lag-1] == 0);
        k = 0;
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

    /** Returns the next value of the generator. */
    result_type operator()()
    {
        std::size_t short_index =
            (k < short_lag)?
                (k + long_lag - short_lag) :
                (k - short_lag);
        IntType delta;
        if (x[short_index] >= x[k] + carry) {
            // x(n) >= 0
            delta =  x[short_index] - (x[k] + carry);
            carry = 0;
        } else {
            // x(n) < 0
            delta = modulus - x[k] - carry + x[short_index];
            carry = 1;
        }
        x[k] = delta;
        ++k;
        if(k >= long_lag)
            k = 0;
        return delta;
    }

#ifndef BOOST_NO_LONG_LONG
    /** Advances the state of the generator by @c z. */
    void discard(boost::ulong_long_type z)
    {
        for(boost::ulong_long_type j = 0; j < z; ++j) {
            (*this)();
        }
    }
#endif

    /** Fills a range with random values. */
    template<class It>
    void generate(It first, It last)
    {
        for(; first != last; ++first) {
            *first = (*this)();
        }
    }
 
    /** Writes a @c subtract_with_carry_engine to a @c std::ostream. */
    BOOST_RANDOM_DETAIL_OSTREAM_OPERATOR(os, subtract_with_carry_engine, f)
    {
        for(unsigned int j = 0; j < f.long_lag; ++j)
            os << f.compute(j) << " ";
        os << f.carry << " ";
        return os;
    }

    /** Reads a @c subtract_with_carry_engine from a @c std::istream. */
    BOOST_RANDOM_DETAIL_ISTREAM_OPERATOR(is, subtract_with_carry_engine, f)
    {
        for(unsigned int j = 0; j < f.long_lag; ++j)
            is >> f.x[j] >> std::ws;
        is >> f.carry;
        f.k = 0;
        return is;
    }

    /**
     * Returns true if the two generators will produce identical
     * sequences of values.
     */
    BOOST_RANDOM_DETAIL_EQUALITY_OPERATOR(subtract_with_carry_engine, x, y)
    {
        for(unsigned int j = 0; j < r; ++j)
            if(x.compute(j) != y.compute(j))
                return false;
        return true;
    }

    /**
     * Returns true if the two generators will produce different
     * sequences of values.
     */
    BOOST_RANDOM_DETAIL_INEQUALITY_OPERATOR(subtract_with_carry_engine)

private:
    /// \cond
    // returns x(i-r+index), where index is in 0..r-1
    IntType compute(unsigned int index) const
    {
        return x[(k+index) % long_lag];
    }
    /// \endcond

    // state representation; next output (state) is x(i)
    //   x[0]  ... x[k] x[k+1] ... x[long_lag-1]     represents
    //  x(i-k) ... x(i) x(i+1) ... x(i-k+long_lag-1)
    // speed: base: 20-25 nsec
    // ranlux_4: 230 nsec, ranlux_7: 430 nsec, ranlux_14: 810 nsec
    // This state representation makes operator== and save/restore more
    // difficult, because we've already computed "too much" and thus
    // have to undo some steps to get at x(i-r) etc.

    // state representation: next output (state) is x(i)
    //   x[0]  ... x[k] x[k+1]          ... x[long_lag-1]     represents
    //  x(i-k) ... x(i) x(i-long_lag+1) ... x(i-k-1)
    // speed: base 28 nsec
    // ranlux_4: 370 nsec, ranlux_7: 688 nsec, ranlux_14: 1343 nsec
    IntType x[long_lag];
    std::size_t k;
    IntType carry;
};

#ifndef BOOST_NO_INCLASS_MEMBER_INITIALIZATION
//  A definition is required even for integral static constants
template<class IntType, std::size_t w, std::size_t s, std::size_t r>
const bool subtract_with_carry_engine<IntType, w, s, r>::has_fixed_range;
template<class IntType, std::size_t w, std::size_t s, std::size_t r>
const IntType subtract_with_carry_engine<IntType, w, s, r>::modulus;
template<class IntType, std::size_t w, std::size_t s, std::size_t r>
const std::size_t subtract_with_carry_engine<IntType, w, s, r>::word_size;
template<class IntType, std::size_t w, std::size_t s, std::size_t r>
const std::size_t subtract_with_carry_engine<IntType, w, s, r>::long_lag;
template<class IntType, std::size_t w, std::size_t s, std::size_t r>
const std::size_t subtract_with_carry_engine<IntType, w, s, r>::short_lag;
template<class IntType, std::size_t w, std::size_t s, std::size_t r>
const uint32_t subtract_with_carry_engine<IntType, w, s, r>::default_seed;
#endif


// use a floating-point representation to produce values in [0..1)
/** @copydoc boost::random::subtract_with_carry_engine */
template<class RealType, std::size_t w, std::size_t s, std::size_t r>
class subtract_with_carry_01_engine
{
public:
    typedef RealType result_type;
    BOOST_STATIC_CONSTANT(bool, has_fixed_range = false);
    BOOST_STATIC_CONSTANT(std::size_t, word_size = w);
    BOOST_STATIC_CONSTANT(std::size_t, long_lag = r);
    BOOST_STATIC_CONSTANT(std::size_t, short_lag = s);
    BOOST_STATIC_CONSTANT(uint32_t, default_seed = 19780503u);

    BOOST_STATIC_ASSERT(!std::numeric_limits<result_type>::is_integer);

    /** Creates a new subtract_with_carry_01_engine using the default seed. */
    subtract_with_carry_01_engine() { init_modulus(); seed(); }
    /** Creates a new subtract_with_carry_01_engine and seeds it with value. */
    BOOST_RANDOM_DETAIL_ARITHMETIC_CONSTRUCTOR(subtract_with_carry_01_engine,
                                               uint32_t, value)
    { init_modulus(); seed(value); }
    /**
     * Creates a new subtract_with_carry_01_engine and seeds with with values
     * produced by seq.generate().
     */
    BOOST_RANDOM_DETAIL_SEED_SEQ_CONSTRUCTOR(subtract_with_carry_01_engine,
                                             SeedSeq, seq)
    { init_modulus(); seed(seq); }
    /**
     * Creates a new subtract_with_carry_01_engine and seeds it with values
     * from a range.  Advances first to point one past the last consumed
     * value.  If the range does not contain enough elements to fill the
     * entire state, throws @c std::invalid_argument.
     */
    template<class It> subtract_with_carry_01_engine(It& first, It last)
    { init_modulus(); seed(first,last); }

private:
    /// \cond
    void init_modulus()
    {
#ifndef BOOST_NO_STDC_NAMESPACE
        // allow for Koenig lookup
        using std::pow;
#endif
        _modulus = pow(RealType(2), RealType(word_size));
    }
    /// \endcond

public:
    // compiler-generated copy ctor and assignment operator are fine

    /** Seeds the generator with the default seed. */
    void seed() { seed(default_seed); }

    /** Seeds the generator with @c value. */
    BOOST_RANDOM_DETAIL_ARITHMETIC_SEED(subtract_with_carry_01_engine,
                                        uint32_t, value)
    {
        random::linear_congruential<int32_t, 40014, 0, 2147483563, 0> gen(value);
        seed(gen);
    }

    /** Seeds the generator with values produced by @c seq.generate(). */
    BOOST_RANDOM_DETAIL_SEED_SEQ_SEED(subtract_with_carry_01_engine,
                                      SeedSeq, seq)
    {
        uint32_t array[(w+31)/32 * long_lag];

        seq.generate(&array[0], &array[0] + sizeof(array)/sizeof(array[0]));

        uint32_t* start = &array[0];
        seed(start, &array[0] + sizeof(array)/sizeof(array[0]));
    }

    /**
     * Seeds the generator with values from a range.  Updates first to
     * point one past the last consumed element.  If there are not
     * enough elements in the range to fill the entire state, throws
     * @c std::invalid_argument.
     */
    template<class It>
    void seed(It& first, It last)
    {
#ifndef BOOST_NO_STDC_NAMESPACE
        // allow for Koenig lookup
        using std::fmod;
        using std::pow;
#endif
        uint32_t mask = ~((~0u) << (w%32));   // now lowest (w%32) bits set
        RealType two32 = pow(RealType(2), 32);
        std::size_t j;
        for(j = 0; j < long_lag && first != last; ++j) {
            x[j] = RealType(0);
            for(std::size_t i = 0; i < w/32 && first != last; ++i, ++first)
                x[j] += *first / pow(two32,RealType(i+1));
            if(first != last && mask != 0) {
                x[j] += fmod((*first & mask) / _modulus, RealType(1));
                ++first;
            }
        }
        if(first == last && j < long_lag)
            throw std::invalid_argument("subtract_with_carry_01::seed");
        carry = (x[long_lag-1] ? 0 : 1 / _modulus);
        k = 0;
    }

    /** Returns the smallest value that the generator can produce. */
    static result_type min BOOST_PREVENT_MACRO_SUBSTITUTION ()
    { return result_type(0); }
    /** Returns the largest value that the generator can produce. */
    static result_type max BOOST_PREVENT_MACRO_SUBSTITUTION ()
    { return result_type(1); }

    /** Returns the next value of the generator. */
    result_type operator()()
    {
        std::size_t short_index =
            (k < short_lag) ?
                (k + long_lag - short_lag) :
                (k - short_lag);
        RealType delta = x[short_index] - x[k] - carry;
        if(delta < 0) {
            delta += RealType(1);
            carry = RealType(1)/_modulus;
        } else {
            carry = 0;
        }
        x[k] = delta;
        ++k;
        if(k >= long_lag)
            k = 0;
        return delta;
    }

#ifndef BOOST_NO_LONG_LONG
    /** Advances the state of the generator by @c z. */
    void discard(boost::ulong_long_type z)
    {
        for(boost::ulong_long_type j = 0; j < z; ++j) {
            (*this)();
        }
    }
#endif

    /** Fills a range with random values. */
    template<class Iter>
    void generate(Iter first, Iter last)
    {
        for(; first != last; ++first) {
            *first = (*this)();
        }
    }

    /** Writes a subtract_with_carry_01_engine to a @c std::ostream. */
    BOOST_RANDOM_DETAIL_OSTREAM_OPERATOR(os, subtract_with_carry_01_engine, f)
    {
        std::ios_base::fmtflags oldflags =
            os.flags(os.dec | os.fixed | os.left); 
        for(unsigned int j = 0; j < f.long_lag; ++j)
            os << (f.compute(j) * f._modulus) << " ";
        os << (f.carry * f._modulus);
        os.flags(oldflags);
        return os;
    }
    
    /** Reads a subtract_with_carry_01_engine from a @c std::istream. */
    BOOST_RANDOM_DETAIL_ISTREAM_OPERATOR(is, subtract_with_carry_01_engine, f)
    {
        RealType value;
        for(unsigned int j = 0; j < long_lag; ++j) {
            is >> value >> std::ws;
            f.x[j] = value / f._modulus;
        }
        is >> value;
        f.carry = value / f._modulus;
        f.k = 0;
        return is;
    }

    /** Returns true if the two generators will produce identical sequences. */
    BOOST_RANDOM_DETAIL_EQUALITY_OPERATOR(subtract_with_carry_01_engine, x, y)
    {
        for(unsigned int j = 0; j < r; ++j)
            if(x.compute(j) != y.compute(j))
                return false;
        return true;
    }

    /** Returns true if the two generators will produce different sequences. */
    BOOST_RANDOM_DETAIL_INEQUALITY_OPERATOR(subtract_with_carry_01_engine)

private:
    /// \cond
    RealType compute(unsigned int index) const
    {
        return x[(k+index) % long_lag];
    }
    /// \endcond
    std::size_t k;
    RealType carry;
    RealType x[long_lag];
    RealType _modulus;
};

#ifndef BOOST_NO_INCLASS_MEMBER_INITIALIZATION
//  A definition is required even for integral static constants
template<class RealType, std::size_t w, std::size_t s, std::size_t r>
const bool subtract_with_carry_01_engine<RealType, w, s, r>::has_fixed_range;
template<class RealType, std::size_t w, std::size_t s, std::size_t r>
const std::size_t subtract_with_carry_01_engine<RealType, w, s, r>::word_size;
template<class RealType, std::size_t w, std::size_t s, std::size_t r>
const std::size_t subtract_with_carry_01_engine<RealType, w, s, r>::long_lag;
template<class RealType, std::size_t w, std::size_t s, std::size_t r>
const std::size_t subtract_with_carry_01_engine<RealType, w, s, r>::short_lag;
template<class RealType, std::size_t w, std::size_t s, std::size_t r>
const uint32_t subtract_with_carry_01_engine<RealType, w, s, r>::default_seed;
#endif


/// \cond

template<class IntType, IntType m, unsigned s, unsigned r, IntType v>
class subtract_with_carry :
    public subtract_with_carry_engine<IntType,
        boost::static_log2<m>::value, s, r>
{
    typedef subtract_with_carry_engine<IntType,
        boost::static_log2<m>::value, s, r> base_type;
public:
    subtract_with_carry() {}
    BOOST_RANDOM_DETAIL_GENERATOR_CONSTRUCTOR(subtract_with_carry, Gen, gen)
    { seed(gen); }
    BOOST_RANDOM_DETAIL_ARITHMETIC_CONSTRUCTOR(subtract_with_carry,
                                               uint32_t, val)
    { seed(val); }
    template<class It>
    subtract_with_carry(It& first, It last) : base_type(first, last) {}
    void seed() { base_type::seed(); }
    BOOST_RANDOM_DETAIL_GENERATOR_SEED(subtract_with_carry, Gen, gen)
    {
        detail::generator_seed_seq<Gen> seq(gen);
        base_type::seed(seq);
    }
    BOOST_RANDOM_DETAIL_ARITHMETIC_SEED(subtract_with_carry, uint32_t, val)
    { base_type::seed(val); }
    template<class It>
    void seed(It& first, It last) { base_type::seed(first, last); }
};

template<class RealType, int w, unsigned s, unsigned r, int v = 0>
class subtract_with_carry_01 :
    public subtract_with_carry_01_engine<RealType, w, s, r>
{
    typedef subtract_with_carry_01_engine<RealType, w, s, r> base_type;
public:
    subtract_with_carry_01() {}
    BOOST_RANDOM_DETAIL_GENERATOR_CONSTRUCTOR(subtract_with_carry_01, Gen, gen)
    { seed(gen); }
    BOOST_RANDOM_DETAIL_ARITHMETIC_CONSTRUCTOR(subtract_with_carry_01,
                                               uint32_t, val)
    { seed(val); }
    template<class It>
    subtract_with_carry_01(It& first, It last) : base_type(first, last) {}
    void seed() { base_type::seed(); }
    BOOST_RANDOM_DETAIL_GENERATOR_SEED(subtract_with_carry_01, Gen, gen)
    {
        detail::generator_seed_seq<Gen> seq(gen);
        base_type::seed(seq);
    }
    BOOST_RANDOM_DETAIL_ARITHMETIC_SEED(subtract_with_carry_01, uint32_t, val)
    { base_type::seed(val); }
    template<class It>
    void seed(It& first, It last) { base_type::seed(first, last); }
};

/// \endcond

} // namespace random
} // namespace boost

#endif // BOOST_RANDOM_SUBTRACT_WITH_CARRY_HPP
