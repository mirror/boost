//  Demonstrate and test boost/operators.hpp on std::iterators  --------------//

//  (C) Copyright Jeremy Siek 1999. Permission to copy, use, modify,
//  sell and distribute this software is granted provided this
//  copyright notice appears in all copies. This software is provided
//  "as is" without express or implied warranty, and with no claim as
//  to its suitability for any purpose.

//  See http://www.boost.org for most recent version including documentation.

//  Revision History
//  12 Dec 99 Initial version with iterator operators (Jeremy Siek)

#include <string>
#include <iostream>
using namespace std;

#include <boost/operators.hpp>
using namespace boost;


template <class T, class R, class P>
struct test_iter
  : public boost::random_access_iterator_helper<
     test_iter<T,R,P>, T, std::ptrdiff_t, P, R>
{
  typedef test_iter self;
  typedef R Reference;
  typedef std::ptrdiff_t Distance;

public:
  test_iter(T* i) : _i(i) { }
  test_iter(const self& x) : _i(x._i) { }
  self& operator=(const self& x) { _i = x._i; return *this; }
  Reference operator*() const { return *_i; }
  self& operator++() { ++_i; return *this; }
  self& operator--() { --_i; return *this; }
  self& operator+=(Distance n) { _i += n; return *this; }
  self& operator-=(Distance n) { _i -= n; return *this; }
  bool operator==(const self& x) const { return _i == x._i; }
  bool operator<(const self& x) const { return _i < x._i; }
  friend Distance operator-(const self& x, const self& y) {
    return x._i - y._i; 
  }
protected:
  T* _i;
};


int
main()
{
  string array[] = { "apple", "orange", "pear", "peach", "grape", "plum"  };
  {
    test_iter<string,string&,string*> i = array, 
      ie = array + sizeof(array)/sizeof(string);

    // Tests for all of the operators added by random_access_iterator_helper

    // test i++
    while (i != ie)
      cout << *i++ << " ";
    cout << endl;
    i = array;

    // test i--
    while (ie != i) {
      ie--;
      cout << *ie << " ";
    }
    cout << endl;
    ie = array + sizeof(array)/sizeof(string);

    // test i->m
    while (i != ie) {
      cout << i->size() << " ";
      ++i;
    }
    cout << endl;
    i = array;

    // test i + n
    while (i < ie) {
      cout << *i << " ";
      i = i + 2;
    }
    cout << endl;
    i = array;

    // test n + i
    while (i < ie) {
      cout << *i << " ";
      i = ptrdiff_t(2) + i;
    }
    cout << endl;
    i = array;

    // test i - n
    while (ie > i) {
      ie = ie - 2;
      cout << *ie << " ";
    }
    cout << endl;
    ie = array + sizeof(array)/sizeof(string);

    // test i[n]
    for (std::size_t j = 0; j < sizeof(array)/sizeof(string); ++j)
      cout << i[j] << " ";
    cout << endl;
  }
  {
    test_iter<string, const string&, const string*> i = array, 
      ie = array + sizeof(array)/sizeof(string);

    // Tests for all of the operators added by random_access_iterator_helper

    // test i++
    while (i != ie)
      cout << *i++ << " ";
    cout << endl;
    i = array;

    // test i--
    while (ie != i) {
      ie--;
      cout << *ie << " ";
    }
    cout << endl;
    ie = array + sizeof(array)/sizeof(string);

    // test i->m
    while (i != ie) {
      cout << i->size() << " ";
      ++i;
    }
    cout << endl;
    i = array;

    // test i + n
    while (i < ie) {
      cout << *i << " ";
      i = i + 2;
    }
    cout << endl;
    i = array;

    // test n + i
    while (i < ie) {
      cout << *i << " ";
      i = ptrdiff_t(2) + i;
    }
    cout << endl;
    i = array;

    // test i - n
    while (ie > i) {
      ie = ie - 2;
      cout << *ie << " ";
    }
    cout << endl;
    ie = array + sizeof(array)/sizeof(string);

    // test i[n]
    for (std::size_t j = 0; j < sizeof(array)/sizeof(string); ++j)
      cout << i[j] << " ";
    cout << endl;
  }
  return 0;
}
