//  Demonstrate and test boost/operators.hpp on std::iterators  -------------//

//  (C) Copyright Jeremy Siek 1999. Permission to copy, use, modify,
//  sell and distribute this software is granted provided this
//  copyright notice appears in all copies. This software is provided
//  "as is" without express or implied warranty, and with no claim as
//  to its suitability for any purpose.

//  See http://www.boost.org for most recent version including documentation.

//  Revision History
//  06 Feb 01 Removed now-defaulted template arguments where possible
//            Updated names to correspond to new generator naming convention.
//            Added a trivial test for make_transform_iterator().
//            Gave traits for const iterators a mutable value_type, per std.
//            Resurrected my original tests for indirect iterators.
//            (David Abrahams)
//  04 Feb 01 Fix for compilers without standard iterator_traits
//            (David Abrahams)
//  13 Jun 00 Added const version of the iterator tests (Jeremy Siek)
//  12 Dec 99 Initial version with iterator operators (Jeremy Siek)

#include <boost/config.hpp>
#include <iostream>

#include <algorithm>
#include <functional>
#include <boost/iterator_adaptors.hpp>
#include <boost/pending/iterator_tests.hpp>
#include <boost/pending/integer_range.hpp>
#include <stdlib.h>
#include <vector>
#include <deque>
#include <set>

struct my_iterator_tag : public std::random_access_iterator_tag { };


using boost::dummyT;

struct my_iter_traits {
  typedef dummyT value_type;
  typedef dummyT* pointer;
  typedef dummyT& reference;
  typedef my_iterator_tag iterator_category;
  typedef std::ptrdiff_t difference_type;
};

struct my_const_iter_traits {
  typedef dummyT value_type;
  typedef const dummyT* pointer;
  typedef const dummyT& reference;
  typedef my_iterator_tag iterator_category;
  typedef std::ptrdiff_t difference_type;
};

typedef boost::iterator_adaptor_pair_generator
  <dummyT*, const dummyT*, 
   my_iter_traits, my_const_iter_traits> My;

struct mult_functor {
  typedef int result_type;
  typedef int argument_type;
  // Functors used with transform_iterator must be
  // DefaultConstructible, as the transform_iterator must be
  // DefaultConstructible to satisfy the requirements for
  // TrivialIterator.
  mult_functor() { }
  mult_functor(int aa) : a(aa) { }
  int operator()(int b) const { return a * b; }
  int a;
};

template <class Pair>
struct select1st_ 
  : public std::unary_function<Pair, typename Pair::first_type>
{
  const typename Pair::first_type& operator()(const Pair& x) const {
    return x.first;
  }
  typename Pair::first_type& operator()(Pair& x) const {
    return x.first;
  }
};

struct one_or_four {
  bool operator()(dummyT x) const {
    return x.foo() == 1 || x.foo() == 4;
  }
};

typedef std::vector<int> storage;
typedef std::deque<int*> pointer_deque;
typedef std::set<storage::iterator> iterator_set;

void indirect_deque_tests(const storage& store, pointer_deque& ptr_deque)
{
}

void more_indirect_iterator_tests()
{
// For some reason all heck breaks loose in the compiler under these conditions.
#if !defined(BOOST_MSVC) || !defined(__STL_DEBUG)
    storage store(1000);
    std::generate(store.begin(), store.end(), rand);
    
    pointer_deque ptr_deque;
    iterator_set iter_set;

    for (storage::iterator p = store.begin(); p != store.end(); ++p)
    {
        ptr_deque.push_back(&*p);
        iter_set.insert(p);
    }

    typedef boost::indirect_iterator_pair_generator<
        pointer_deque::iterator,
        const int*
#ifdef BOOST_NO_STD_ITERATOR_TRAITS
        , boost::iterator<std::random_access_iterator_tag,int,std::ptrdiff_t,const int*,const int&>
        , int*
        , boost::iterator<std::random_access_iterator_tag,int>
#endif
        > indirect_deque;

    indirect_deque::iterator db(ptr_deque.begin());
    indirect_deque::iterator de(ptr_deque.end());
    assert(static_cast<std::size_t>(de - db) == store.size());
    assert(db + store.size() == de);
    indirect_deque::const_iterator dci(db);
    assert(db == dci);
    assert(dci == db);
    assert(dci != de);
    assert(dci < de);
    assert(dci <= de);
    assert(de >= dci);
    assert(de > dci);
    dci = de;
    assert(dci == de);

    boost::random_access_iterator_test(db + 1, store.size() - 1, boost::next(store.begin()));
    
    *db = 999;
    assert(store.front() == 999);

    typedef boost::indirect_iterator_pair_generator<
        iterator_set::iterator,
        storage::const_iterator
# ifdef BOOST_NO_STD_ITERATOR_TRAITS
        , boost::iterator<std::random_access_iterator_tag,int,std::ptrdiff_t,const int*,const int&>
        , storage::iterator
        , boost::iterator<std::random_access_iterator_tag,int>
# endif
        > indirect_set;
    indirect_set::iterator sb(iter_set.begin());
    indirect_set::iterator se(iter_set.end());
    indirect_set::const_iterator sci(iter_set.begin());
    assert(sci == sb);
    assert(sci != se);
    sci = se;
    assert(sci == se);
    
    *boost::prior(se) = 888;
    assert(store.back() == 888);
    assert(std::equal(sb, se, store.begin()));

    boost::bidirectional_iterator_test(boost::next(sb), store[1], store[2]);
    assert(std::equal(db, de, store.begin()));
#endif    
}

int
main()
{
  dummyT array[] = { dummyT(0), dummyT(1), dummyT(2), 
                     dummyT(3), dummyT(4), dummyT(5) };
  const int N = sizeof(array)/sizeof(dummyT);

  // sanity check, if this doesn't pass the test is buggy
  boost::random_access_iterator_test(array,N,array);

  // Check that the policy concept checks and the default policy
  // implementation match up.
  boost::function_requires< 
     boost::RandomAccessIteratorPoliciesConcept<
       boost::default_iterator_policies, int*,
       boost::iterator<std::random_access_iterator_tag, int, std::ptrdiff_t,
                      int*, int&>
      > >();

  // Test the iterator_adaptor_pair_generator
  {
    My::iterator i = array;
    boost::random_access_iterator_test(i, N, array);
    
    My::const_iterator j = array;
    boost::random_access_iterator_test(j, N, array);
    boost::const_nonconst_iterator_test(i, ++j);
  }
  // Test transform_iterator
  {
    int x[N], y[N];
    for (int k = 0; k < N; ++k)
      x[k] = k;
    std::copy(x, x + N, y);

    for (int k2 = 0; k2 < N; ++k2)
      x[k2] = x[k2] * 2;

    boost::transform_iterator_generator<mult_functor, int*>::type
      i(y, mult_functor(2));
    boost::input_iterator_test(i, x[0], x[1]);
    boost::input_iterator_test(boost::make_transform_iterator(&y[0], mult_functor(2)), x[0], x[1]);
  }
  
  // Test indirect_iterator_pair_generator
  {
    dummyT* ptr[N];
    for (int k = 0; k < N; ++k)
      ptr[k] = array + k;
    
    typedef boost::indirect_iterator_pair_generator<dummyT**, const dummyT*
#ifdef BOOST_NO_STD_ITERATOR_TRAITS
        , boost::iterator<std::random_access_iterator_tag,dummyT,std::ptrdiff_t,const dummyT*,const dummyT&>
        , dummyT*
        , boost::iterator<std::random_access_iterator_tag,dummyT>
#endif
      > Indirect;
    Indirect::iterator i = ptr;
    boost::random_access_iterator_test(i, N, array);

    Indirect::const_iterator j = ptr;
    boost::random_access_iterator_test(j, N, array);

    boost::const_nonconst_iterator_test(i, ++j);


    more_indirect_iterator_tests();
  }
  
  // Test projection_iterator_pair_generator
  {    
    typedef std::pair<dummyT,dummyT> Pair;
    Pair pair_array[N];
    for (int k = 0; k < N; ++k)
      pair_array[k].first = array[k];

    typedef boost::projection_iterator_pair_generator<select1st_<Pair>,
      Pair*, const Pair*
      > Projection;
    
    Projection::iterator i = pair_array;
    boost::random_access_iterator_test(i, N, array);

    Projection::const_iterator j = pair_array;
    boost::random_access_iterator_test(j, N, array);

    boost::const_nonconst_iterator_test(i, ++j);
  }
  // Test reverse_iterator_pair_generator
  {
    dummyT reversed[N];
    std::copy(array, array + N, reversed);
    std::reverse(reversed, reversed + N);
    
    typedef boost::reverse_iterator_pair_generator<dummyT*, const dummyT*,
      boost::iterator<std::random_access_iterator_tag,dummyT>,
      boost::iterator<std::random_access_iterator_tag,const dummyT>
      > Reverse;
    Reverse::iterator i = reversed + N;
    boost::random_access_iterator_test(i, N, array);

    Reverse::const_iterator j = reversed + N;
    boost::random_access_iterator_test(j, N, array);

    boost::const_nonconst_iterator_test(i, ++j);    
  }

  // Test integer_range's iterators
  {
    int int_array[] = { 0, 1, 2, 3, 4, 5 };
    boost::integer_range<int> r(0, 5);
    boost::random_access_iterator_test(r.begin(), r.size(), int_array);
  }

  // Test filter iterator
  {
    typedef boost::filter_iterator_generator<one_or_four, dummyT*,
      boost::iterator<std::forward_iterator_tag, dummyT, std::ptrdiff_t,
      dummyT*, dummyT&> >::type FilterIter;
    FilterIter i(array);
    boost::forward_iterator_test(i, dummyT(1), dummyT(4));
  }
  std::cout << "test successful " << std::endl;
  return 0;
}
