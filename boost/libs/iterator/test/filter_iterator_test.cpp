// Copyright David Abrahams 2003. Permission to copy, use,
// modify, sell and distribute this software is granted provided this
// copyright notice appears in all copies. This software is provided
// "as is" without express or implied warranty, and with no claim as
// to its suitability for any purpose.

#include <boost/iterator/filter_iterator.hpp>
#include <boost/iterator/reverse_iterator.hpp>
#include <boost/iterator/new_iterator_tests.hpp>
#include <boost/type_traits/broken_compiler_spec.hpp>

#include <deque>
#include <iostream>

using boost::dummyT;
BOOST_TT_BROKEN_COMPILER_SPEC(boost::dummyT)
    
struct one_or_four
{
    bool operator()(dummyT x) const
    {
        return x.foo() == 1 || x.foo() == 4;
    }
};

template <class T> struct undefined;

// Test filter iterator
int main()
{
    dummyT array[] = { dummyT(0), dummyT(1), dummyT(2), 
                       dummyT(3), dummyT(4), dummyT(5) };
    const int N = sizeof(array)/sizeof(dummyT);

    typedef boost::filter_iterator<one_or_four, dummyT*> filter_iter;

    boost::bidirectional_readable_iterator_test(
        filter_iter(one_or_four(), array, array+N)
        , dummyT(1), dummyT(4));

    BOOST_STATIC_ASSERT((
        !boost::detail::is_tag<
         boost::random_access_traversal_tag
       , boost::traversal_category<filter_iter>::type
      >::value
    ));
    
    //# endif
    
    // On compilers not supporting partial specialization, we can do more type
    // deduction with deque iterators than with pointers... unless the library
    // is broken ;-(
    std::deque<dummyT> array2;
    std::copy(array+0, array+N, std::back_inserter(array2));
    boost::bidirectional_readable_iterator_test(
        boost::make_filter_iterator(one_or_four(), array2.begin(), array2.end()),
        dummyT(1), dummyT(4));

    boost::bidirectional_readable_iterator_test(
        boost::make_filter_iterator(one_or_four(), array2.begin(), array2.end()),
        dummyT(1), dummyT(4));

    boost::bidirectional_readable_iterator_test(
        boost::make_filter_iterator(
              one_or_four()
            , boost::make_reverse_iterator(array2.end())
            , boost::make_reverse_iterator(array2.begin())
            ),
        dummyT(4), dummyT(1));
    
    boost::bidirectional_readable_iterator_test(
        filter_iter(array+0, array+N),
        dummyT(1), dummyT(4));

    boost::bidirectional_readable_iterator_test(
        filter_iter(one_or_four(), array, array + N),
        dummyT(1), dummyT(4));

  std::cout << "test successful " << std::endl;
  return 0;
}
