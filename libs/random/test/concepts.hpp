/* concepts.hpp
 *
 * Copyright Steven Watanabe 2011
 * Distributed under the Boost Software License, Version 1.0. (See
 * accompanying file LICENSE_1_0.txt or copy at
 * http://www.boost.org/LICENSE_1_0.txt)
 *
 * $Id$
 *
 */

#include <boost/concept_check.hpp>
#include <boost/concept_archetype.hpp>
#include <boost/concept/requires.hpp>
#include <boost/mpl/assert.hpp>
#include <boost/type_traits/is_arithmetic.hpp>
#include <boost/cstdint.hpp>
#include <boost/static_assert.hpp>
#include <istream>
#include <ostream>

#ifndef BOOST_RANDOM_TEST_CONCEPTS_HPP
#define BOOST_RANDOM_TEST_CONCEPTS_HPP

namespace boost {
namespace random {
namespace test {

template<class Base = null_archetype<> >
struct seed_seq_archetype : Base
{
    template<class Iter>
    BOOST_CONCEPT_REQUIRES(
        ((Mutable_RandomAccessIterator<Iter>))
        ((UnsignedInteger<typename Mutable_RandomAccessIterator<Iter>::value_type>)),
    (void))
    generate(Iter, Iter);
};

template<class SSeq>
struct SeedSeq
{
public:
    BOOST_CONCEPT_USAGE(SeedSeq)
    {
        q.generate(rb, re);
    }
private:
    SSeq q;
    mutable_random_access_iterator_archetype<boost::uint32_t> rb, re;
};

template<class T>
struct Streamable
{
public:
    BOOST_CONCEPT_USAGE(Streamable)
    {
        os << x;
        is >> v;
        wos << x;
        wis >> v;
    }
private:
    const T x;
    T v;

    std::istream is;
    std::ostream os;
    std::wistream wis;
    std::wostream wos;
};

template <class E>
struct RandomNumberEngine :
    DefaultConstructible<E>,
    CopyConstructible<E>,
    Assignable<E>,
    EqualityComparable<E>,
    Streamable<E>
{
 public:
    typedef typename E::result_type result_type;

    // relaxed from the standard
    BOOST_MPL_ASSERT((boost::is_arithmetic<result_type>));

    // backwards compatibility check
    BOOST_STATIC_ASSERT(!E::has_fixed_range);

    // a generator can be used to seed another generator (extension)
    BOOST_CONCEPT_ASSERT((SeedSeq<E>));

    BOOST_CONCEPT_USAGE(RandomNumberEngine)
    {
        same_type(e(), result_type());
        same_type(E::min(), result_type());
        same_type(E::max(), result_type());

        E();
        E(s);
        E(q);

        e.seed();
        e.seed(s);
        e.seed(q);

        e.discard(z);

        // extension
        E(sb, se);
        e.seed(sb, se);
    }
    
 private:
    E e;
    E v;
    const E x;
    seed_seq_archetype<> q;
    result_type s;
    unsigned long long z;
    
    input_iterator_archetype<boost::uint32_t> sb, se;

    // Type deduction will fail unless the arguments have the same type.
    template <typename T>
    void same_type(T const&, T const&) {}
};

}
}
}

#endif
