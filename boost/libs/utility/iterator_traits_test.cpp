//  (C) Copyright David Abrahams 2001. Permission to copy, use, modify,
//  sell and distribute this software is granted provided this
//  copyright notice appears in all copies. This software is provided
//  "as is" without express or implied warranty, and with no claim as
//  to its suitability for any purpose.

//  See http://www.boost.org for most recent version including documentation.

//  Revision History
//  19 Jan 2001 Initial version with iterator operators (David Abrahams)

#include <boost/detail/iterator.hpp>
#include <boost/type_traits.hpp>
#include <boost/operators.hpp>
#include <boost/static_assert.hpp>
#include <iterator>
#include <vector>
#include <list>
#include <cassert>
#include <iostream>

struct my_iterator
    : public boost::forward_iterator_helper<my_iterator, const char, long>
{
    my_iterator(const char* p) : m_p(p) {}
    
    bool operator==(const my_iterator& rhs) const
        { return this->m_p == rhs.m_p; }

    my_iterator& operator++() { ++this->m_p; return *this; }
    const char operator*() { return *m_p; }
 private:
    const char* m_p;
};

// Test difference_type and iterator_category

// istream_iterator (forward_iterator_tag, ptrdiff_t)
BOOST_STATIC_ASSERT((
    boost::is_same<
      boost::detail::iterator_traits<std::istream_iterator<int> >::iterator_category,
      std::input_iterator_tag
    >::value));

BOOST_STATIC_ASSERT((
    boost::is_same<
      boost::detail::iterator_traits<std::istream_iterator<int> >::difference_type,
      std::ptrdiff_t
    >::value));

// ostream_iterator (output_iterator_tag, void)
BOOST_STATIC_ASSERT((
    boost::is_same<
      boost::detail::iterator_traits<std::ostream_iterator<int> >::iterator_category,
      std::output_iterator_tag
    >::value));

BOOST_STATIC_ASSERT((
    boost::is_same<
      boost::detail::iterator_traits<std::ostream_iterator<int> >::difference_type,
      void
    >::value));

// list<int>::iterator (bidirectional_iterator_tag, ptrdiff_t)
BOOST_STATIC_ASSERT((
    boost::is_same<
      boost::detail::iterator_traits<std::list<int>::iterator>::iterator_category,
      std::bidirectional_iterator_tag
    >::value));
                    
BOOST_STATIC_ASSERT((
    boost::is_same<
      boost::detail::iterator_traits<std::list<int>::iterator>::difference_type,
      std::ptrdiff_t
    >::value));

// vector<int>::iterator (random_access_iterator_tag, ptrdiff_t)
BOOST_STATIC_ASSERT((
    boost::is_same<
      boost::detail::iterator_traits<std::vector<int>::iterator>::iterator_category,
      std::random_access_iterator_tag
    >::value));
                    
BOOST_STATIC_ASSERT((
    boost::is_same<
      boost::detail::iterator_traits<std::vector<int>::iterator>::difference_type,
      std::ptrdiff_t
    >::value));
                    
// int* (random_access_iterator_tag, ptrdiff_t)
BOOST_STATIC_ASSERT((
    boost::is_same<
      boost::detail::iterator_traits<int*>::iterator_category,
      std::random_access_iterator_tag
    >::value));
                    
BOOST_STATIC_ASSERT((
    boost::is_same<
      boost::detail::iterator_traits<int*>::difference_type,
    std::ptrdiff_t
    >::value));
                    
// my_iterator (forward_iterator_tag, long)
BOOST_STATIC_ASSERT((
    boost::is_same<
      boost::detail::iterator_traits<my_iterator>::iterator_category,
      std::forward_iterator_tag
    >::value));
                    
BOOST_STATIC_ASSERT((
    boost::is_same<
      boost::detail::iterator_traits<my_iterator>::difference_type,
      long
    >::value));
                    
int main()
{
    char chars[100];
    int ints[100];
    
    for (std::ptrdiff_t length = 3; length < 100; length += length / 3)
    {
        std::list<int> l(length);
        assert(boost::detail::distance(l.begin(), l.end()) == length);
        
        std::vector<int> v(length);
        assert(boost::detail::distance(v.begin(), v.end()) == length);

        assert(boost::detail::distance(&ints[0], ints + length) == length);
        assert(boost::detail::distance(my_iterator(chars), my_iterator(chars + length)) == length);
    }
    return 0;
}
