// (C) Copyright David Abrahams 2000. Permission to copy, use,
// modify, sell and distribute this software is granted provided this
// copyright notice appears in all copies. This software is provided
// "as is" without express or implied warranty, and with no claim as
// to its suitability for any purpose.
//
// (C) Copyright Jeremy Siek 2000. Permission to copy, use, modify,
// sell and distribute this software is granted provided this
// copyright notice appears in all copies. This software is provided
// "as is" without express or implied warranty, and with no claim as
// to its suitability for any purpose.

#ifndef BOOST_INTEGER_RANGE_HPP_
#define BOOST_INTEGER_RANGE_HPP_

#include <boost/config.hpp>

#if 1
// Still evaluating whether VC++ can handle this.
#define BOOST_USE_ITERATOR_ADAPTORS
#endif

#ifdef BOOST_USE_ITERATOR_ADAPTORS
#include <boost/pending/iterator_adaptors.hpp>
#else
#include <boost/pending/detail/int_iterator.hpp>
#endif

namespace boost {

//=============================================================================
// Counting Iterator and Integer Range Class

#ifdef BOOST_USE_ITERATOR_ADAPTORS
template <class IntegerType>
struct counting_iterator_policies : public default_iterator_policies
{
    IntegerType
    dereference(type<IntegerType>, const IntegerType& i) const
        { return i; }
};
template <class IntegerType>
struct counting_iterator_traits {
    typedef IntegerType value_type;
    typedef IntegerType reference;
    typedef value_type* pointer;
    typedef std::ptrdiff_t difference_type;
    typedef std::random_access_iterator_tag iterator_category;
};
#endif

template <class IntegerType>
struct integer_range {
#ifdef BOOST_USE_ITERATOR_ADAPTORS
    typedef iterator_adaptor<IntegerType,
      counting_iterator_policies<IntegerType>,
      counting_iterator_traits<IntegerType> > iterator;
#else
    typedef int_iterator<IntegerType> iterator;
#endif

    typedef iterator const_iterator;
    typedef IntegerType value_type;
    typedef std::ptrdiff_t difference_type;
    typedef IntegerType reference;
    typedef IntegerType const_reference;
    typedef const IntegerType* pointer;
    typedef const IntegerType* const_pointer;
    typedef IntegerType size_type;

    integer_range(IntegerType start, IntegerType finish)
        : m_start(start), m_finish(finish) { }

    iterator begin() const { return iterator(m_start); }
    iterator end() const { return iterator(m_finish); }
    size_type size() const { return m_finish - m_start; }
    bool empty() const { return m_finish == m_start; }
    void swap(integer_range& x) {
        std::swap(m_start, x.m_start);
        std::swap(m_finish, x.m_finish);
    }
protected:
    IntegerType m_start, m_finish;
};

template <class IntegerType>
inline integer_range<IntegerType>
make_integer_range(IntegerType first, IntegerType last)
{
  return integer_range<IntegerType>(first, last);
}

} // namespace boost

#ifdef BOOST_USE_ITERATOR_ADAPTORS
#undef BOOST_USE_ITERATOR_ADAPTORS
#endif

#endif // BOOST_INTEGER_RANGE_HPP_
