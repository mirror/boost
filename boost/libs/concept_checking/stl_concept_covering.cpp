// (C) Copyright Jeremy Siek 2000. Permission to copy, use, modify,
// sell and distribute this software is granted provided this
// copyright notice appears in all copies. This software is provided
// "as is" without express or implied warranty, and with no claim as
// to its suitability for any purpose.

#include <boost/pending/concept_checks.hpp>
#include <boost/pending/concept_archetypes.hpp>
#include <algorithm>

/*

  This file uses the archetype classes to verify whether the concept
  requirements documented for the STL algorithms actually *cover* the
  algorithms true requirements.

*/

int
main()
{
  using namespace boost;

  //===========================================================================
  // Non-mutating Algorithms
  {
    input_iterator_archetype< convertible_to_archetype< null_archetype > > in;
    unary_function_archetype< null_archetype, null_archetype> f;
    std::for_each(in, in, f);
  }
  {
    /*
      SGI STL Docs and the C++ standard (25.1.2) BOOST_FUNCTION_REQUIRESments for
      std::for_each() are broken. They should be specified as follows:

      template <class InputIterator, class LeftEqualityComparable>
      InputIterator find(InputIterator first, InputIterator last,
                         const LeftEqualityComparable& value)
      {
        BOOST_FUNCTION_REQUIRES(InputIterator, InputIterator);
        typedef typename std::iterator_traits<InputIterator>::value_type 
          value_type;
        BOOST_FUNCTION_REQUIRES(LeftEqualityComparable, value_type, LeftEqualityComparable);
        ...
      }
    */
    input_iterator_archetype< null_archetype > in;
    left_equality_comparable_archetype< null_archetype > value(dummy_cons);
    in = std::find(in, in, value);
  }
  {
    input_iterator_archetype< convertible_to_archetype< null_archetype > > in;
    unary_predicate_archetype< null_archetype > pred;
    in = std::find_if(in, in, pred);
  }
  {
    forward_iterator_archetype< equality_comparable_archetype<> > fo;
    fo = std::adjacent_find(fo, fo);
  }
  {
    forward_iterator_archetype< convertible_to_archetype< null_archetype > > fo;
    binary_predicate_archetype<null_archetype, null_archetype> pred;
    fo = std::adjacent_find(fo, fo, pred);
  }
  {
    /* SGI STL documentation is wrong. The value type of the
       input iterator does not need to be equality comparable.
    */
    input_iterator_archetype<null_archetype> in;
    typedef left_equality_comparable_archetype<null_archetype> Right;
    forward_iterator_archetype<Right> fo;
    in = std::find_first_of(in, in, fo, fo);
  }
  {
    typedef input_iterator_archetype<null_archetype> InIter;
    InIter in;
    BOOST_FUNCTION_REQUIRES(InIter, InputIteratorConcept);
    left_equality_comparable_archetype<null_archetype> value(dummy_cons);
    std::iterator_traits<InIter>::difference_type
      n = std::count(in, in, value);
    ignore_unused_variable_warning(n);
  }
  {
    typedef input_iterator_archetype<null_archetype> InIter;
    InIter in;
    left_equality_comparable_archetype<null_archetype> value(dummy_cons);
    unsigned long n;
    std::count(in, in, value, n);
  }
  {
    typedef input_iterator_archetype< convertible_to_archetype<null_archetype> > InIter;
    InIter in;
    unary_predicate_archetype<null_archetype> pred;
    std::iterator_traits<InIter>::difference_type
      n = std::count_if(in, in, pred);
    ignore_unused_variable_warning(n);
  }
  {
    input_iterator_archetype< convertible_to_archetype<null_archetype> > in;
    unary_predicate_archetype<null_archetype> pred;
    unsigned long n;
    std::count_if(in, in, pred, n);
  }
  {
    /*
      SGI STL Documentation wrong. EqualityComparable not needed.
     */
    typedef input_iterator_archetype<null_archetype> InIter1;
    InIter1 in1;
    typedef left_equality_comparable_archetype<null_archetype> Right;
    typedef input_iterator_archetype<Right> InIter2;
    InIter2 in2;
    std::pair<InIter1, InIter2> p = std::mismatch(in1, in1, in2);
    ignore_unused_variable_warning(p);
  }
  {
    typedef input_iterator_archetype< convertible_to_archetype<null_archetype> > InIter;
    InIter in1, in2;
    binary_predicate_archetype<null_archetype, null_archetype> pred;
    std::pair<InIter, InIter> p = std::mismatch(in1, in1, in2, pred);
    ignore_unused_variable_warning(p);
  }
  {
    // SGI STL docs: EqualityComparable not needed
    input_iterator_archetype<null_archetype> in1;
    typedef left_equality_comparable_archetype<null_archetype> Right;
    input_iterator_archetype<Right> in2;
    bool b = std::equal(in1, in1, in2);
    ignore_unused_variable_warning(b);
  }
  {
    input_iterator_archetype< convertible_to_archetype<null_archetype> > in1, in2;
    binary_predicate_archetype<null_archetype, null_archetype> pred;
    bool b = std::equal(in1, in1, in2, pred);
    ignore_unused_variable_warning(b);
  }
  {
    // SGI STL docs: EqualityComparable not needed
    forward_iterator_archetype<null_archetype> fo1;
    typedef left_equality_comparable_archetype<null_archetype> Right;
    forward_iterator_archetype<Right> fo2;
    fo1 = std::search(fo1, fo1, fo2, fo2);
  }
  {
    // SGI STL docs: LeftEqualityComparable missing
    // search() calls find()
    typedef convertible_to_archetype<null_archetype> Left;
    forward_iterator_archetype<Left> fo1;
    typedef convertible_to_archetype<null_archetype,
      left_equality_comparable_archetype<Left> > Right;
    forward_iterator_archetype<Right> fo2;
    binary_predicate_archetype<null_archetype, null_archetype> pred;
    fo1 = std::search(fo1, fo1, fo2, fo2, pred);
  }
  {
    // SGI STL docs: EqualityComparable not needed
    forward_iterator_archetype<null_archetype> fo;
    left_equality_comparable_archetype<null_archetype> value(dummy_cons);
    int n;
    fo = std::search_n(fo, fo, n, value);
  }
  {
    // SGI STL docs: EqualityComparable not needed
    forward_iterator_archetype< convertible_to_archetype<null_archetype> > fo;
    convertible_to_archetype<null_archetype> value(dummy_cons);
    binary_predicate_archetype<null_archetype, null_archetype> pred;
    int n;
    fo = std::search_n(fo, fo, n, value, pred);
  }
  {
    forward_iterator_archetype<null_archetype> fo1;
    typedef left_equality_comparable_archetype<null_archetype> Right;
    forward_iterator_archetype<Right> fo2;
    fo1 = std::find_end(fo1, fo1, fo2, fo2);
  }
  {
    // SGI STL docs: LeftEqualityComparable missing
    typedef convertible_to_archetype<null_archetype> Left;
    forward_iterator_archetype<Left> fo1;
    typedef convertible_to_archetype<null_archetype,
      left_equality_comparable_archetype<Left> > Right;
    forward_iterator_archetype<Right> fo2;
    binary_predicate_archetype<null_archetype, null_archetype> pred;
    fo1 = std::find_end(fo1, fo1, fo2, fo2, pred);
  }

  //===========================================================================
  // Mutating Algorithms

  // UNDER CONSTRUCTION

  {
    // SGI STL docs missing CopyConstructible and Assignable
    typedef equality_comparable_archetype< copy_constructible_archetype< 
      assignable_archetype<> > > T;
    input_iterator_archetype<T> in;
    output_iterator_archetype out;
    out = std::unique_copy(in, in, out);
  }

  //===========================================================================
  // Sorting Algorithms

  // UNDER CONSTRUCTION

  {
    typedef less_than_comparable_archetype< 
      copy_constructible_archetype<
        assignable_archetype<> > > ValueType;
    random_access_iterator_archetype<ValueType> ri;
    std::stable_sort(ri, ri);
  }

  //===========================================================================
  // Generalized Numeric Algorithms

  // UNDER CONSTRUCTION


  return 0;
}
