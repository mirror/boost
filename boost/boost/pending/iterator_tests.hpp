#ifndef BOOST_ITERATOR_TESTS_HPP
#define BOOST_ITERATOR_TESTS_HPP

// This is meant to be the beginnings of a comprehensive, generic
// test suite for STL concepts such as iterators and containers.

#include <iterator>
#include <assert.h>

namespace boost {

  // use this for the value type
struct dummyT { 
  dummyT() { }
  dummyT(int x) : m_x(x) { }
  int foo() const { return m_x; } 
  bool operator==(const dummyT& d) const { return m_x == d.m_x; }
  int m_x;
};


// Tests whether type Iterator satisfies the requirements for a
// TrivialIterator. 
// Preconditions: i != j, *i == val
template <class Iterator, class T>
void trivial_iterator_test(const Iterator i, const Iterator j, T val)
{
  Iterator k;
  assert(i == i);
  assert(j == j);
  assert(i != j);
#ifdef BOOST_NO_STD_ITERATOR_TRAITS
  T v = *i;
#else
  typename std::iterator_traits<Iterator>::value_type v = *i;
#endif
  assert(v == val);
#if 0
  // hmm, this will give a warning for transform_iterator...  perhaps
  // this should be separated out into a stand-alone test since there
  // are several situations where it can't be used, like for
  // integer_range::iterator.
  assert(v == i->foo());
#endif
  k = i;
  assert(k == k);
  assert(k == i);
  assert(k != j);
  assert(*k == val);
}


// Preconditions: i != j
template <class Iterator, class T>
void mutable_trivial_iterator_test(const Iterator i, const Iterator j, T val)
{
  *i = val;
  trivial_iterator_test(i, j, val);
}


// Preconditions: *i == v1, *++i == v2
template <class Iterator, class T>
void input_iterator_test(Iterator i, T v1, T v2) 
{
  Iterator i1 = i, i2 = i;

  assert(i == i1++);
  assert(i != ++i2);

  trivial_iterator_test(i, i1, v1);
  trivial_iterator_test(i, i2, v1);

  ++i;
  assert(i == i1);
  assert(i == i2);
  ++i1;
  ++i2;

  trivial_iterator_test(i, i1, v2);
  trivial_iterator_test(i, i2, v2);
}

// how to test output iterator?

template <class Iterator, class T>
void forward_iterator_test(Iterator i, T v1, T v2) 
{
  input_iterator_test(i, v1, v2);
}

// Preconditions: *i == v1, *++i == v2
template <class Iterator, class T>
void bidirectional_iterator_test(Iterator i, T v1, T v2)
{
  input_iterator_test(i, v1, v2);
  ++i;

  Iterator i1 = i, i2 = i;

  assert(i == i1--);
  assert(i != --i2);

  trivial_iterator_test(i, i1, v2);
  trivial_iterator_test(i, i2, v2);

  --i;
  assert(i == i1);
  assert(i == i2);
  --i1;
  --i2;

  trivial_iterator_test(i, i1, v1);
  trivial_iterator_test(i, i2, v1);
}

// mutable_bidirectional_iterator_test

// Preconditions: [i,i+N) is a valid range
template <class Iterator, class TrueVals>
void random_access_iterator_test(Iterator i, int N, TrueVals vals)
{
  bidirectional_iterator_test(i, vals[0], vals[1]);
  const Iterator j = i;
  int c;

  for (c = 0; c < N-1; ++c) {
    assert(i == j + c);
    assert(*i == vals[c]);
    assert(*i == j[c]);
    assert(*i == *(j + c));
    assert(*i == *(c + j));
    ++i;
    assert(i > j);
    assert(i >= j);
    assert(j <= i);
    assert(j < i);
  }

  Iterator k = j + N - 1;
  for (c = 0; c < N-1; ++c) {
    assert(i == k - c);
    assert(*i == vals[N - 1 - c]);
    assert(*i == j[N - 1 - c]);
    Iterator q = k - c; 
    assert(*i == *q);
    assert(i > j);
    assert(i >= j);
    assert(j <= i);
    assert(j < i);
    --i;
  }
}

// Precondition: i != j
template <class Iterator, class ConstIterator>
void const_nonconst_iterator_test(Iterator i, ConstIterator j)
{
  assert(i != j);
  assert(j != i);

  ConstIterator k(i);
  assert(k == i);
  assert(i == k);

  k = i;
  assert(k == i);
  assert(i == k);
}

} // namespace boost

#endif // BOOST_ITERATOR_TESTS_HPP
