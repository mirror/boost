// (C) Copyright Jeremy Siek 2000. Permission to copy, use, modify,
// sell and distribute this software is granted provided this
// copyright notice appears in all copies. This software is provided
// "as is" without express or implied warranty, and with no claim as
// to its suitability for any purpose.

#include <boost/pending/concept_checks.hpp>
#include <boost/pending/concept_archetypes.hpp>
#include <algorithm>

/*

  This file uses the archetype classes to find out which concepts
  actually *cover* the algorithms true requirements. The
  archetypes/concepts chosen do not necessarily match the C++ standard
  or the SGI STL documentation, but instead were chosen based on the
  minimal concepts that current STL implementations require, which in
  many cases is less stringent than the standard. It is an open issue
  as to whether the C++ standard should be changed to reflect these
  weaker requirements.

*/

#define BOOST_HIDE_EXPECTED_ERRORS

  // This is a special concept needed for std::swap_ranges.
  // It is mutually convertible, and also SGIAssignable
  template <class T>
  class mutually_convertible_archetype
  {
  private:
    mutually_convertible_archetype() { }
  public:
    mutually_convertible_archetype(const mutually_convertible_archetype&) { }
    mutually_convertible_archetype& 
    operator=(const mutually_convertible_archetype&)
      { return *this; }
    mutually_convertible_archetype(boost::detail::dummy_constructor) { }

    template <class U>
    mutually_convertible_archetype& 
    operator=(const mutually_convertible_archetype<U>&)
      { return *this; }

  };

int
main()
{
  using namespace boost;

  //===========================================================================
  // Non-mutating Algorithms
  {
    input_iterator_archetype< 
      convertible_to_archetype< null_archetype<>  > > in;
    unary_function_archetype< null_archetype<> , null_archetype<> > 
      f(dummy_cons);
    std::for_each(in, in, f);
  }
  {
    typedef equality_comparable2_first_archetype<> Left;
    input_iterator_archetype< Left > in;
    equality_comparable2_second_archetype<> value(dummy_cons);
    in = std::find(in, in, value);
  }
  {
    input_iterator_archetype< 
      convertible_to_archetype< null_archetype<>  > > in;
    unary_predicate_archetype< null_archetype<>  > pred(dummy_cons);
    in = std::find_if(in, in, pred);
  }
  {
    forward_iterator_archetype< equality_comparable_archetype<> > fo;
    fo = std::adjacent_find(fo, fo);
  }
  {
    forward_iterator_archetype< 
      convertible_to_archetype< null_archetype<>  > > fo;
    binary_predicate_archetype<null_archetype<> , null_archetype<> > 
      pred(dummy_cons);
    fo = std::adjacent_find(fo, fo, pred);
  }
  {
    typedef equal_op_first_archetype<> Left;
    input_iterator_archetype<Left> in;
    typedef equal_op_second_archetype<> Right;
    forward_iterator_archetype<Right> fo;
    in = std::find_first_of(in, in, fo, fo);
  }
  {
    typedef equal_op_first_archetype<> Left;
    typedef input_iterator_archetype<Left> InIter;
    InIter in;
    function_requires< InputIteratorConcept<InIter> >();
    equal_op_second_archetype<> value(dummy_cons);
    std::iterator_traits<InIter>::difference_type
      n = std::count(in, in, value);
    ignore_unused_variable_warning(n);
  }
#if !defined(__KCC) && !defined(BOOST_HIDE_EXPECTED_ERRORS)
  {
    typedef equal_op_first_archetype<> Left;
    typedef input_iterator_archetype<Left> InIter;
    InIter in;
    equal_op_second_archetype<> value(dummy_cons);
    unsigned long n;
    std::count(in, in, value, n);
  }
  {
    input_iterator_archetype< convertible_to_archetype<null_archetype<> > > in;
    unary_predicate_archetype<null_archetype<> > pred;
    unsigned long n;
    std::count_if(in, in, pred, n);
  }
#endif
  {
    typedef input_iterator_archetype<
      convertible_to_archetype<null_archetype<> > > InIter;
    InIter in;
    unary_predicate_archetype<null_archetype<> > pred(dummy_cons);
    std::iterator_traits<InIter>::difference_type
      n = std::count_if(in, in, pred);
    ignore_unused_variable_warning(n);
  }
  {
    typedef equal_op_first_archetype<> Left;
    typedef input_iterator_archetype<Left> InIter1;
    InIter1 in1;
    typedef equal_op_second_archetype<> Right;
    typedef input_iterator_archetype<Right> InIter2;
    InIter2 in2;
    std::pair<InIter1, InIter2> p = std::mismatch(in1, in1, in2);
    ignore_unused_variable_warning(p);
  }
  {
    typedef input_iterator_archetype<
      convertible_to_archetype<null_archetype<> > > InIter;
    InIter in1, in2;
    binary_predicate_archetype<null_archetype<> , null_archetype<> > 
      pred(dummy_cons);
    std::pair<InIter, InIter> p = std::mismatch(in1, in1, in2, pred);
    ignore_unused_variable_warning(p);
  }
  {
    typedef equality_comparable2_first_archetype<> Left;
    input_iterator_archetype<Left> in1;
    typedef equality_comparable2_second_archetype<> Right;
    input_iterator_archetype<Right> in2;
    bool b = std::equal(in1, in1, in2);
    ignore_unused_variable_warning(b);
  }
  {
    input_iterator_archetype< convertible_to_archetype<null_archetype<> > >
      in1, in2;
    binary_predicate_archetype<null_archetype<> , null_archetype<> > 
      pred(dummy_cons);
    bool b = std::equal(in1, in1, in2, pred);
    ignore_unused_variable_warning(b);
  }
  {
    typedef equality_comparable2_first_archetype<> Left;
    forward_iterator_archetype<Left> fo1;
    typedef equality_comparable2_second_archetype<> Right;
    forward_iterator_archetype<Right> fo2;
    fo1 = std::search(fo1, fo1, fo2, fo2);
  }
  {
    typedef equality_comparable2_first_archetype< 
      convertible_to_archetype<null_archetype<> > > Left;
    forward_iterator_archetype<Left> fo1;
    typedef equality_comparable2_second_archetype<
      convertible_to_archetype<null_archetype<> > > Right;
    forward_iterator_archetype<Right> fo2;
    binary_predicate_archetype<null_archetype<> , null_archetype<> > 
      pred(dummy_cons);
    fo1 = std::search(fo1, fo1, fo2, fo2, pred);
  }
  {
    typedef equality_comparable2_first_archetype<> Left;
    forward_iterator_archetype<Left> fo;
    equality_comparable2_second_archetype<> value(dummy_cons);
    int n = 1;
    fo = std::search_n(fo, fo, n, value);
  }
  {
    forward_iterator_archetype< 
      convertible_to_archetype<null_archetype<> > > fo;
    convertible_to_archetype<null_archetype<> > value(dummy_cons);
    binary_predicate_archetype<null_archetype<> , null_archetype<> > 
      pred(dummy_cons);
    int n = 1;
    fo = std::search_n(fo, fo, n, value, pred);
  }
  {
    typedef equality_comparable2_first_archetype<> Left;
    forward_iterator_archetype<Left> fo1;
    typedef equality_comparable2_second_archetype<null_archetype<> > Right;
    forward_iterator_archetype<Right> fo2;
    fo1 = std::find_end(fo1, fo1, fo2, fo2);
  }
  {
    // equality comparable required because find_end() calls search
    typedef equality_comparable2_first_archetype<
      convertible_to_archetype<null_archetype<> > > Left;
    forward_iterator_archetype<Left> fo1;
    typedef equality_comparable2_second_archetype<
      convertible_to_archetype<null_archetype<> > > Right;
    forward_iterator_archetype<Right> fo2;
    binary_predicate_archetype<null_archetype<> , null_archetype<> > 
      pred(dummy_cons);
    fo1 = std::find_end(fo1, fo1, fo2, fo2, pred);
  }

  //===========================================================================
  // Mutating Algorithms

  {
    typedef null_archetype<> OutT;
    typedef convertible_to_archetype<OutT> InT;
    input_iterator_archetype<InT> in;
    output_iterator_archetype<OutT> out;
    out = std::copy(in, in, out);
  }
#if !defined(__KCC)
  {
    // Not in the C++ standard
    typedef null_archetype<> OutT;
    typedef convertible_to_archetype<OutT> InT;
    input_iterator_archetype<InT> in;
    output_iterator_archetype<OutT> out;
    int count = 1;
    std::pair<input_iterator_archetype<InT>,
      output_iterator_archetype<OutT> > result = std::copy_n(in, count, out);
    ignore_unused_variable_warning(result);
  }
#endif
  {
    typedef assignable_archetype<> OutT;
    typedef convertible_to_archetype<OutT> InT;
    bidirectional_iterator_archetype<InT> bid_in;
    bidirectional_iterator_archetype<OutT> bid_out;
    bid_out = std::copy_backward(bid_in, bid_in, bid_out);
  }
  {
    sgi_assignable_archetype<> a(dummy_cons), b(dummy_cons);
    std::swap(a, b);
  }
  {
    typedef sgi_assignable_archetype<> T;
    forward_iterator_archetype<T> a, b;
    std::iter_swap(a, b);
  }
  {
    typedef mutually_convertible_archetype<int> Tin;
    typedef mutually_convertible_archetype<char> Tout;
    forward_iterator_archetype<Tin> fi1;
    forward_iterator_archetype<Tout> fi2;
    fi2 = std::swap_ranges(fi1, fi1, fi2);
  }
  {
    typedef convertible_to_archetype<null_archetype<> > Tin;
    typedef null_archetype<> Tout;
    input_iterator_archetype<Tin> in;
    output_iterator_archetype<Tout> out;
    unary_function_archetype<null_archetype<> , 
      convertible_to_archetype<Tout> > op(dummy_cons);
    out = std::transform(in, in, out, op);
  }
  {
    typedef convertible_to_archetype<null_archetype<int> > Tin1;
    typedef convertible_to_archetype<null_archetype<char> > Tin2;
    typedef null_archetype<> Tout;
    input_iterator_archetype<Tin1> in1;
    input_iterator_archetype<Tin2> in2;
    output_iterator_archetype<Tout> out;
    binary_function_archetype<null_archetype<int>, null_archetype<char>,
      convertible_to_archetype<Tout> > op(dummy_cons);
    out = std::transform(in1, in1, in2, out, op);
  }
  {
    typedef equality_comparable2_first_archetype<
      assignable_archetype<> > FT;
    forward_iterator_archetype<FT> fi;
    equality_comparable2_second_archetype<
      convertible_to_archetype<FT> > value(dummy_cons);
    std::replace(fi, fi, value, value);
  }
  {
    typedef null_archetype<> PredArg;
    typedef assignable_archetype< 
      convertible_to_archetype<PredArg> > FT;
    forward_iterator_archetype<FT> fi;
    unary_predicate_archetype<PredArg> pred(dummy_cons);
    convertible_to_archetype<FT> value(dummy_cons);
    std::replace_if(fi, fi, pred, value);
  }
  {
#if 0
    // Issue, the use of ?: inside replace_copy() complicates things
    typedef equal_op_first_archetype<> Tin;
    typedef null_archetype<> Tout;
    typedef equal_op_second_archetype< convertible_to_archetype<Tout> > T;
    input_iterator_archetype<Tin> in;
    output_iterator_archetype<Tout> out;
    T value(dummy_cons);
    out = std::replace_copy(in, in, out, value, value);
#else
    typedef null_archetype<> Tout;
    typedef equal_op_second_archetype< convertible_to_archetype<Tout> > T;
    // Adding convertible to T for Tin solves the problem, so would
    // making T convertible to Tin. Not sure what the right way to
    // express the requirement would be. Also, perhaps the
    // implementation's use of ?: is invalid.
    typedef equal_op_first_archetype< convertible_to_archetype<T> > Tin;
    input_iterator_archetype<Tin> in;
    output_iterator_archetype<Tout> out;
    T value(dummy_cons);
    out = std::replace_copy(in, in, out, value, value);
#endif
  }
  {
    // The issue of ?: also affects this function
    typedef null_archetype<int> PredArg;
    typedef null_archetype<char> Tout;
    typedef convertible_to_archetype<Tout, 
      convertible_to_archetype<PredArg> > T;
    typedef convertible_to_archetype<PredArg,
      convertible_to_archetype<Tout,
      convertible_to_archetype<T> > > Tin;
    input_iterator_archetype<Tin> in;
    output_iterator_archetype<Tout> out;
    unary_predicate_archetype<PredArg> pred(dummy_cons);
    T value(dummy_cons);
    out = std::replace_copy_if(in, in, out, pred, value);
  }
  {
    typedef assignable_archetype<> FT;
    forward_iterator_archetype<FT> fi;
    typedef convertible_to_archetype<FT> T;
    T value(dummy_cons);
    std::fill(fi, fi, value);
  }  
  {
    typedef null_archetype<> Tout;
    typedef convertible_to_archetype<Tout> T;
    output_iterator_archetype<Tout> out;
    T value(dummy_cons);
    int n = 1;
    out = std::fill_n(out, n, value);
  }
  {
    typedef assignable_archetype<> FT;
    typedef convertible_to_archetype<FT> Ret;
    forward_iterator_archetype<FT> fi;
    generator_archetype<Ret> gen;
    std::generate(fi, fi, gen);
  }
  {
    typedef assignable_archetype<> FT;
    typedef convertible_to_archetype<FT> Ret;
    forward_iterator_archetype<FT> fi;
    generator_archetype<Ret> gen;
    int n = 1;
    std::generate_n(fi, n, gen);
  }
  {
    typedef assignable_archetype< equality_comparable2_first_archetype<> > FT;
    typedef equality_comparable2_second_archetype<> T;
    forward_iterator_archetype<FT> fi;
    T value(dummy_cons);
    fi = std::remove(fi, fi, value);
  }
  {
    typedef assignable_archetype<> FT;
    forward_iterator_archetype<FT> fi;
    typedef null_archetype<> PredArg;
    unary_predicate_archetype<PredArg> pred(dummy_cons);
    fi = std::remove_if(fi, fi, pred);
  }
  {
    typedef null_archetype<> Tout;
    typedef equality_comparable2_first_archetype<
      convertible_to_archetype<Tout> > Tin;
    typedef equality_comparable2_second_archetype<> T;
    input_iterator_archetype<Tin> in;
    output_iterator_archetype<Tout> out;
    T value(dummy_cons);
    out = std::remove_copy(in, in, out, value);
  }
  {
    typedef null_archetype<int> Tout;
    typedef null_archetype<char> PredArg;
    typedef convertible_to_archetype<PredArg,
      convertible_to_archetype<Tout> > Tin;
    input_iterator_archetype<Tin> in;
    output_iterator_archetype<Tout> out;
    unary_predicate_archetype<PredArg> pred(dummy_cons);
    out = std::remove_copy_if(in, in, out, pred);
  }
  {
    typedef sgi_assignable_archetype< equality_comparable_archetype<> > T;
    forward_iterator_archetype<T> fi;
    fi = std::unique(fi, fi);
  }
  {
    typedef null_archetype<int> Arg1;
    typedef null_archetype<char> Arg2;
    typedef sgi_assignable_archetype< 
      convertible_to_archetype<Arg1,
      convertible_to_archetype<Arg2> > > FT;
    forward_iterator_archetype<FT> fi;
    binary_predicate_archetype<Arg1, Arg2> pred(dummy_cons);
    fi = std::unique(fi, fi, pred);
  }
  {
    typedef equality_comparable_archetype< sgi_assignable_archetype<> > T;
    input_iterator_archetype<T> in;
    output_iterator_archetype<T> out;
    out = std::unique_copy(in, in, out);
  }
  {
    typedef null_archetype<int> Arg1;
    typedef null_archetype<char> Arg2;
    typedef null_archetype<short> Tout;
    typedef sgi_assignable_archetype< 
      convertible_to_archetype<Tout,
      convertible_to_archetype<Arg1,
      convertible_to_archetype<Arg2> > > > Tin;
    input_iterator_archetype<Tin> in;
    output_iterator_archetype<Tout> out;
    binary_predicate_archetype<Arg1, Arg2> pred(dummy_cons);
    out = std::unique_copy(in, in, out, pred);
  }
  {
    typedef sgi_assignable_archetype<> T;
    bidirectional_iterator_archetype<T> bi;
    std::reverse(bi, bi);
  }
  {
    typedef null_archetype<> Tout;
    typedef convertible_to_archetype<Tout> Tin;
    bidirectional_iterator_archetype<Tin> bi;
    output_iterator_archetype<Tout> out;
    out = std::reverse_copy(bi, bi, out);
  }
  {
    typedef sgi_assignable_archetype<> T;
    forward_iterator_archetype<T> fi;
    // Issue, SGI STL is not have void return type, C++ standard does
    std::rotate(fi, fi, fi);
  }
  {
    typedef null_archetype<> Tout;
    typedef convertible_to_archetype<Tout> FT;
    forward_iterator_archetype<FT> fi;
    output_iterator_archetype<Tout> out;
    out = std::rotate_copy(fi, fi, fi, out);
  }
  {
    typedef sgi_assignable_archetype<> T;
    random_access_iterator_archetype<T> ri;
    std::random_shuffle(ri, ri);
  }
  {
    typedef sgi_assignable_archetype<> T;
    random_access_iterator_archetype<T> ri;
    unary_function_archetype<std::ptrdiff_t, std::ptrdiff_t> ran(dummy_cons);
    std::random_shuffle(ri, ri, ran);
  }
#if !defined(__KCC)
  {
    typedef assignable_archetype<> Tout;
    typedef convertible_to_archetype<Tout> Tin;
    input_iterator_archetype<Tin> in; 
    random_access_iterator_archetype<Tout> ri_out;
    ri_out = std::random_sample(in, in, ri_out, ri_out);
  }
  {
    typedef assignable_archetype<> Tout;
    typedef convertible_to_archetype<Tout> Tin;
    input_iterator_archetype<Tin> in; 
    random_access_iterator_archetype<Tout> ri_out;
    unary_function_archetype<std::ptrdiff_t, std::ptrdiff_t> ran(dummy_cons);
    ri_out = std::random_sample(in, in, ri_out, ri_out, ran);
  }
  {
    typedef assignable_archetype<> Tout;
    typedef convertible_to_archetype<Tout> Tin;
    forward_iterator_archetype<Tin> in; 
    output_iterator_archetype<Tout> out;
    int n = 1;
    out = std::random_sample_n(in, in, out, n);
  }
  {
    typedef assignable_archetype<> Tout;
    typedef convertible_to_archetype<Tout> Tin;
    input_iterator_archetype<Tin> in; 
    forward_iterator_archetype<Tout> out;
    unary_function_archetype<std::ptrdiff_t, std::ptrdiff_t> ran(dummy_cons);
    int n = 1;
    out = std::random_sample_n(in, in, out, n, ran);
  }
#endif
  {
    typedef null_archetype<> PredArg;
    typedef sgi_assignable_archetype<convertible_to_archetype<PredArg> > FT;
    bidirectional_iterator_archetype<FT> bi;
    unary_predicate_archetype<PredArg> pred(dummy_cons);
    bi = std::partition(bi, bi, pred);
  }
  {
    typedef null_archetype<> PredArg;
    typedef sgi_assignable_archetype<convertible_to_archetype<PredArg> > FT;
    forward_iterator_archetype<FT> fi;
    unary_predicate_archetype<PredArg> pred(dummy_cons);
    fi = std::stable_partition(fi, fi, pred);
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
