// (C) Copyright David Abrahams 2001. Permission to copy, use, modify, sell and
// distribute this software is granted provided this copyright notice appears in
// all copies. This software is provided "as is" without express or implied
// warranty, and with no claim as to its suitability for any purpose.
//
//  See http://www.boost.org for most recent version including documentation.
//
// Revision History
// 28 Jan 2001  Removed not_an_iterator detritus (David Abrahams)
// 24 Jan 2001  Initial revision (David Abrahams)

#include <boost/counting_iterator.hpp>
#include <boost/detail/iterator.hpp>
#include <climits>
#include <iterator>
#include <stdlib.h>
#include <boost/utility.hpp>
#include <vector>
#include <list>
#include <cassert>
#ifndef BOOST_NO_LIMITS
# include <limits>
#endif
#ifndef BOOST_NO_SLIST
# include <slist>
#endif

template <class T> struct is_numeric
{
    enum { value = 
#ifndef BOOST_NO_LIMITS_COMPILE_TIME_CONSTANTS
        std::numeric_limits<T>::is_specialized
#else
        // Causes warnings with GCC, but how else can I detect numeric types at
        // compile-time?
        (boost::is_convertible<int,T>::value &&
         boost::is_convertible<T,int>::value)
#endif
    };
};

// Special tests for RandomAccess CountingIterators.
template <class CountingIterator>
void category_test(
    CountingIterator start,
    CountingIterator finish,
    std::random_access_iterator_tag)
{
    typedef typename
        boost::detail::iterator_traits<CountingIterator>::difference_type
        difference_type;
    difference_type distance = boost::detail::distance(start, finish);

    // Pick a random position internal to the range
    difference_type offset = (unsigned)rand() % distance;
    assert(offset >= 0);
    CountingIterator internal = start;
    std::advance(internal, offset);

    // Try some binary searches on the range to show that it's ordered
    assert(std::binary_search(start, finish, *internal));
    CountingIterator x,y;
    boost::tie(x,y) = std::equal_range(start, finish, *internal);
    assert(boost::detail::distance(x, y) == 1);

    // Show that values outside the range can't be found
    assert(!std::binary_search(start, boost::prior(finish), *finish));
}

// Otherwise, we'll have to skip those.
template <class CountingIterator>
void category_test(CountingIterator, CountingIterator, std::forward_iterator_tag)
{
}

template <class CountingIterator>
void test_aux(CountingIterator start, CountingIterator finish)
{
    typedef typename CountingIterator::iterator_category category;
    typedef typename CountingIterator::value_type value_type;

    // If it's a RandomAccessIterator we can do a few delicate tests
    category_test(start, finish, category());
    
    // Okay, brute force...
    for (CountingIterator p = start; p != finish && boost::next(p) != finish; ++p)
    {
        assert(boost::next(*p) == *boost::next(p));
    }

    // prove that a reference can be formed to these values
    typedef typename CountingIterator::value_type value;
    const value* q = &*start;
    (void)q; // suppress unused variable warning
}

template <class Incrementable>
void test(Incrementable start, Incrementable finish)
{
    test_aux(boost::counting_iterator(start), boost::counting_iterator(finish));
}

template <class Integer>
void test_integer(Integer* = 0) // default arg works around MSVC bug
{
    Integer start = 0;
    Integer finish = 120;
    test(start, finish);
}

template <class Container>
void test_container(Container* = 0)  // default arg works around MSVC bug
{
    Container c(1 + (unsigned)rand() % 1673);
    
    const typename Container::iterator start = c.begin();
    
    // back off by 1 to leave room for dereferenceable value at the end
    typename Container::iterator finish = start;
    std::advance(finish, c.size() - 1);
    
    test(start, finish);
    
    test(static_cast<typename Container::const_iterator>(start),
         static_cast<typename Container::const_iterator>(finish));
}

int main()
{
    // Test the built-in integer types.
    test_integer<char>();
    test_integer<unsigned char>();
    test_integer<signed char>();
    test_integer<wchar_t>();
    test_integer<short>();
    test_integer<unsigned short>();
    test_integer<int>();
    test_integer<unsigned int>();
    test_integer<long>();
    test_integer<unsigned long>();
#if defined(ULLONG_MAX) || defined(ULONG_LONG_MAX)
    test_integer<long long>();
    test_integer<unsigned long long>();
#endif
    // Some tests on container iterators, to prove we handle a few different categories
    test_container<std::vector<int> >();
    test_container<std::list<int> >();
#ifndef BOOST_NO_SLIST
    test_container<BOOST_STD_EXTENSION_NAMESPACE::slist<int> >();
#endif
    // Also prove that we can handle raw pointers.
    int array[2000];
    test(boost::counting_iterator(array), boost::counting_iterator(array+2000-1));
    return 0;
}
