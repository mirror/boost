// Copyright Thomas Witt 2003. Permission to copy, use,
// modify, sell and distribute this software is granted provided this
// copyright notice appears in all copies. This software is provided
// "as is" without express or implied warranty, and with no claim as
// to its suitability for any purpose.

#include <boost/iterator/reverse_iterator.hpp>
#include <boost/iterator/new_iterator_tests.hpp>
#include <algorithm>
#include <deque>

using boost::dummyT;

// Test reverse iterator
int main()
{
  dummyT array[] = { dummyT(0), dummyT(1), dummyT(2), 
                     dummyT(3), dummyT(4), dummyT(5) };
  const int N = sizeof(array)/sizeof(dummyT);

  // Test reverse_iterator_generator
  {
    dummyT reversed[N];
    std::copy(array, array + N, reversed);
    std::reverse(reversed, reversed + N);
    
    typedef boost::reverse_iterator<dummyT*> reverse_iterator;
    
    reverse_iterator i(reversed + N);
    boost::random_access_iterator_test(i, N, array);

    boost::random_access_iterator_test(boost::make_reverse_iterator(reversed + N), N, array);

    typedef boost::reverse_iterator<const dummyT*> const_reverse_iterator;
    
    const_reverse_iterator j(reversed + N);
    boost::random_access_iterator_test(j, N, array);

    const dummyT* const_reversed = reversed;
    
    boost::random_access_iterator_test(boost::make_reverse_iterator(const_reversed + N), N, array);
    
    boost::const_nonconst_iterator_test(i, ++j);
  }

  // Test reverse_iterator_generator again, with traits fully deducible on all platforms
  {
    std::deque<dummyT> reversed_container;
    std::reverse_copy(array, array + N, std::back_inserter(reversed_container));
    const std::deque<dummyT>::iterator reversed = reversed_container.begin();


    typedef boost::reverse_iterator<
        std::deque<dummyT>::iterator> reverse_iterator;
    typedef boost::reverse_iterator<
        std::deque<dummyT>::const_iterator> const_reverse_iterator;

    // MSVC/STLport gives an INTERNAL COMPILER ERROR when any computation
    // (e.g. "reversed + N") is used in the constructor below.
    const std::deque<dummyT>::iterator finish = reversed_container.end();
    reverse_iterator i(finish);
    
    boost::random_access_iterator_test(i, N, array);
    boost::random_access_iterator_test(boost::make_reverse_iterator(reversed + N), N, array);

    const_reverse_iterator j = reverse_iterator(finish);
    boost::random_access_iterator_test(j, N, array);

    const std::deque<dummyT>::const_iterator const_reversed = reversed;
    boost::random_access_iterator_test(boost::make_reverse_iterator(const_reversed + N), N, array);
    
    // Many compilers' builtin deque iterators don't interoperate well, though
    // STLport fixes that problem.
#if defined(__SGI_STL_PORT)                                                             \
    || !BOOST_WORKAROUND(__GNUC__, <= 2)                                                \
    && !(BOOST_WORKAROUND(__GNUC__, == 3) && BOOST_WORKAROUND(__GNUC_MINOR__, <= 1))    \
    && !BOOST_WORKAROUND(__BORLANDC__, BOOST_TESTED_AT(0x551))                          \
    && !BOOST_WORKAROUND(__LIBCOMO_VERSION__, BOOST_TESTED_AT(29))                      \
    && !BOOST_WORKAROUND(BOOST_DINKUMWARE_STDLIB, <= 1)
    
    boost::const_nonconst_iterator_test(i, ++j);
    
#endif
  }
  return 0;
}
