//
// (C) Copyright Jeremy Siek 2000. Permission to copy, use, modify,
// sell and distribute this software is granted provided this
// copyright notice appears in all copies. This software is provided
// "as is" without express or implied warranty, and with no claim as
// to its suitability for any purpose.
//
#ifndef BOOST_CONCEPT_CHECKS_HPP
#define BOOST_CONCEPT_CHECKS_HPP

#include <iterator>
#include <utility>
#include <boost/config.hpp>
#include <boost/pending/limits.hpp>

#if (__GNUC__) || defined(__KCC) || defined(__ghs) || defined(__MWERKS__)
#define BOOST_FPTR &
#else
#define BOOST_FPTR
#endif

namespace boost {

template <class T> void ignore_unused_variable_warning(const T&) { }

template <class Concept>
void function_requires()
{
#if !defined(NDEBUG)
  void (Concept::*x)() = BOOST_FPTR Concept::constraints;
  ignore_unused_variable_warning(x);
#endif
}

template <class Concept>
class class_requires
{
#if defined(NDEBUG)
public:
  typedef int check;
#else
  typedef void (Concept::* function_pointer)();

  template <function_pointer Fptr>
  struct dummy_struct { };
public:
  typedef dummy_struct< BOOST_FPTR Concept::constraints > check;
#endif
};

#if !defined BOOST_NO_TEMPLATE_PARTIAL_SPECIALIZATION
template <class T, class U>
struct require_same { };

template <class T>
struct require_same<T,T> { typedef T type; };
#else
// This version does not perform checking, but will not do any harm.
template <class T, class U>
struct require_same { typedef T type; };
#endif

  template <class T>
  struct IntegerConcept {
    void constraints() { 
#if !defined BOOST_NO_TEMPLATE_PARTIAL_SPECIALIZATION
      error__type_must_be_an_integer_type();
#endif      
    }
  };
#if !defined BOOST_NO_TEMPLATE_PARTIAL_SPECIALIZATION
  template <> struct IntegerConcept<short> { void constraints() {} };
  template <> struct IntegerConcept<unsigned short> { void constraints() {} };
  template <> struct IntegerConcept<int> { void constraints() {} };
  template <> struct IntegerConcept<unsigned int> { void constraints() {} };
  template <> struct IntegerConcept<long> { void constraints() {} };
  template <> struct IntegerConcept<unsigned long> { void constraints() {} };
  // etc.
#endif      

  template <class T>
  struct SignedIntegerConcept {
    void constraints() { 
#if !defined BOOST_NO_TEMPLATE_PARTIAL_SPECIALIZATION
      error__type_must_be_a_signed_integer_type();
#endif      
    }
  };
#if !defined BOOST_NO_TEMPLATE_PARTIAL_SPECIALIZATION
  template <> struct SignedIntegerConcept<short> { void constraints() {} };
  template <> struct SignedIntegerConcept<int> { void constraints() {} };
  template <> struct SignedIntegerConcept<long> { void constraints() {} };
  // etc.
#endif      

  template <class T>
  struct UnsignedIntegerConcept {
    void constraints() { 
#if !defined BOOST_NO_TEMPLATE_PARTIAL_SPECIALIZATION
      error__type_must_be_an_unsigned_integer_type();
#endif      
    }
  };
#if !defined BOOST_NO_TEMPLATE_PARTIAL_SPECIALIZATION
  template <> struct UnsignedIntegerConcept<unsigned short>
    { void constraints() {} };
  template <> struct UnsignedIntegerConcept<unsigned int>
    { void constraints() {} };
  template <> struct UnsignedIntegerConcept<unsigned long>
    { void constraints() {} };
  // etc.
#endif      

  //===========================================================================
  // Basic Concepts

  template <class X, class Y>
  struct ConvertibleConcept
  {
    void constraints() {
      Y y = x;
      ignore_unused_variable_warning(y);
    }
    X x;
  };

  template <class TT>
  struct AssignableConcept
  {
    void constraints() {
#if !defined(_ITERATOR_) // back_insert_iterator broken for VC++ STL
      a = a;              // require assignment operator
#endif
      const_constraints(a);
    }
    void const_constraints(const TT& b) {
#if !defined(_ITERATOR_) // back_insert_iterator broken for VC++ STL
      a = b;              // const required for argument to assignment
#endif
    }
    TT a;
  };

  template <class TT>
  struct AssignableSGIConcept
  {
    void constraints() {
#if !defined(_ITERATOR_) // back_insert_iterator broken for VC++ STL
      a = a;              // require assignment operator
#endif
      const_constraints(a);
    }
    void const_constraints(const TT& b) {
#if !defined(_ITERATOR_) // back_insert_iterator broken for VC++ STL
      a = b;              // const required for argument to assignment
#endif
    }
    TT a;
  };

  template <class TT>
  struct DefaultConstructibleConcept
  {
    void constraints() {
      TT a;               // require default constructor
      ignore_unused_variable_warning(a);
    }
  };

  template <class T>
  struct CopyConstructibleConcept
  {
    void constraints() {
      T a(b);            // require copy constructor
      T* ptr = &a;       // require address of operator
      const_constraints(a);
      ignore_unused_variable_warning(ptr);
    }
    void const_constraints(const T& a) {
      T c(a);            // require const copy constructor
      const T* ptr = &a; // require const address of operator
      ignore_unused_variable_warning(c);
      ignore_unused_variable_warning(ptr);
    }
    T b;
  };

  // The C++ standard requirements for many concepts talk about return
  // types that must be "convertible to bool".  The problem with this
  // requirement is that it leaves the door open for evil proxies that
  // define things like operator|| with strange return types.  Two
  // possible solutions are:
  // 1) require the return type to be exactly bool
  // 2) stay with convertible to bool, and also
  //    specify stuff about all the logical operators.
  // For now we just test for convertible to bool.
  template <class T>
  void require_boolean_expr(const T& t) {
    bool x = t;
    ignore_unused_variable_warning(x);
  }

  template <class TT>
  struct EqualityComparableConcept
  {
    void constraints() {
      require_boolean_expr(a == b);
      require_boolean_expr(a != b);
    }
    TT a, b;
  };

  template <class AA, class BB>
  struct EqualityComparable2Concept
  {
    void constraints() {
      require_boolean_expr(a == b);
      require_boolean_expr(b == a);
      require_boolean_expr(a != b);
      require_boolean_expr(b != a);
    }
    AA a;
    BB b;
  };

  template <class TT>
  struct LessThanComparableConcept
  {
    void constraints() {
      require_boolean_expr(a < b);
    }
    TT a, b;
  };

  template <class AA, class BB>
  struct LessThanComparable2Concept
  {
    void constraints() {
      function_requires< LessThanComparableConcept<AA> >();
      function_requires< LessThanComparableConcept<BB> >();
      require_boolean_expr(a < b);
      require_boolean_expr(b < a);
    }
    AA a;
    BB b;
  };

  // This is equivalent to SGI STL's LessThanComparable.
  template <class TT>
  struct ComparableConcept
  {
    void constraints() {
      function_requires< EqualityComparableConcept<TT> >();
      require_boolean_expr(a < b);
      require_boolean_expr(a > b);
      require_boolean_expr(a <= b);
      require_boolean_expr(a >= b);
    }
    TT a, b;
  };

  // This is a generalization of SGI STL's LessThanComparable
  // concept to 2 types.
  template <class AA, class BB>
  struct Comparable2Concept
  {
    void constraints() {
      function_requires< EqualityComparable2Concept<AA,BB> >();
      function_requires< ComparableConcept<AA> >();
      function_requires< ComparableConcept<BB> >();
      require_boolean_expr(a < b);
      require_boolean_expr(b < a);
      require_boolean_expr(a > b);
      require_boolean_expr(b > a);
      require_boolean_expr(a <= b);
      require_boolean_expr(b <= a);
      require_boolean_expr(a >= b);
      require_boolean_expr(b >= a);
    }
    AA a;
    BB b;
  };

  //===========================================================================
  // Iterator Concepts

  template <class TT>
  struct TrivialIteratorConcept
  {
    void constraints() {
      function_requires< AssignableConcept<TT> >();
      function_requires< DefaultConstructibleConcept<TT> >();
      function_requires< EqualityComparableConcept<TT> >();
#ifndef BOOST_NO_STD_ITERATOR_TRAITS
      typedef typename std::iterator_traits<TT>::value_type V;
#endif
      (void)*i;           // require dereference operator
    }
    TT i;
  };

  template <class TT>
  struct Mutable_TrivialIteratorConcept
  {
    void constraints() {
      function_requires< TrivialIteratorConcept<TT> >();
      *i = *j;            // require dereference and assignment
    }
    TT i, j;
  };

  template <class TT>
  struct InputIteratorConcept
  {
    void constraints() {
      function_requires< TrivialIteratorConcept<TT> >();
      // require iterator_traits typedef's
#ifndef BOOST_NO_STD_ITERATOR_TRAITS
      typedef typename std::iterator_traits<TT>::difference_type D;
      function_requires< SignedIntegerConcept<D> >();
      typedef typename std::iterator_traits<TT>::reference R;
      typedef typename std::iterator_traits<TT>::pointer P;
      typedef typename std::iterator_traits<TT>::iterator_category C;
      function_requires< ConvertibleConcept<
        typename std::iterator_traits<TT>::iterator_category,
        std::input_iterator_tag> >();
#endif
      ++i;                // require preincrement operator
      i++;                // require postincrement operator
    }
    TT i;
  };

  template <class TT, class ValueT>
  struct OutputIteratorConcept
  {
    void constraints() {
      function_requires< AssignableConcept<TT> >();
      ++i;                // require preincrement operator
      i++;                // require postincrement operator
      *i++ = t;           // require postincrement and assignment
    }
    TT i, j;
    ValueT t;
  };

  template <class TT>
  struct ForwardIteratorConcept
  {
    void constraints() {
      function_requires< InputIteratorConcept<TT> >();
#ifndef BOOST_NO_STD_ITERATOR_TRAITS
      function_requires< ConvertibleConcept<
        typename std::iterator_traits<TT>::iterator_category,
        std::forward_iterator_tag> >();
      typedef typename std::iterator_traits<TT>::reference reference;
      reference r = *i;
      ignore_unused_variable_warning(r);
#endif
    }
    TT i;
  };

  template <class TT>
  struct Mutable_ForwardIteratorConcept
  {
    void constraints() {
      function_requires< ForwardIteratorConcept<TT> >();
      *i++ = *i;         // require postincrement and assignment
    }
    TT i;
  };

  template <class TT>
  struct BidirectionalIteratorConcept
  {
    void constraints() {
      function_requires< ForwardIteratorConcept<TT> >();
#ifndef BOOST_NO_STD_ITERATOR_TRAITS
      function_requires< ConvertibleConcept<
        typename std::iterator_traits<TT>::iterator_category,
        std::bidirectional_iterator_tag> >();
#endif
      --i;                // require predecrement operator
      i--;                // require postdecrement operator
    }
    TT i;
  };

  template <class TT>
  struct Mutable_BidirectionalIteratorConcept
  {
    void constraints() {
      function_requires< BidirectionalIteratorConcept<TT> >();
      function_requires< Mutable_ForwardIteratorConcept<TT> >();
      *i-- = *i;                  // require postdecrement and assignment
    }
    TT i;
  };


  template <class TT>
  struct RandomAccessIteratorConcept
  {
    void constraints() {
      function_requires< BidirectionalIteratorConcept<TT> >();
      function_requires< ComparableConcept<TT> >();
#ifndef BOOST_NO_STD_ITERATOR_TRAITS
      function_requires< ConvertibleConcept<
        typename std::iterator_traits<TT>::iterator_category,
        std::random_access_iterator_tag> >();
      typedef typename std::iterator_traits<TT>::reference R;
#endif

      i += n;             // require assignment addition operator
      i = i + n; i = n + i; // require addition with difference type
      i -= n;             // require assignment subtraction operator
      i = i - n;                  // require subtraction with difference type
      n = i - j;                  // require difference operator
      (void)i[n];                 // require element access operator
    }
    TT a, b;
    TT i, j;
#ifndef BOOST_NO_STD_ITERATOR_TRAITS
    typename std::iterator_traits<TT>::difference_type n;
#else
    std::ptrdiff_t n;
#endif
  };

  template <class TT>
  struct Mutable_RandomAccessIteratorConcept
  {
    void constraints() {
      function_requires< RandomAccessIteratorConcept<TT> >();
      function_requires< Mutable_BidirectionalIteratorConcept<TT> >();
      i[n] = *i;                  // require element access and assignment
    }
    TT i;
#ifndef BOOST_NO_STD_ITERATOR_TRAITS
    typename std::iterator_traits<TT>::difference_type n;
#else
    std::ptrdiff_t n;
#endif
  };

  //===========================================================================
  // Function Object Concepts

  template <class _Func, class _Ret>
  struct GeneratorConcept
  {
    void constraints() {
      __r = __f();   // require operator() member function
    }
    _Func __f;
    _Ret __r;
  };


#if !defined BOOST_NO_TEMPLATE_PARTIAL_SPECIALIZATION
  template <class _Func>
  struct GeneratorConcept<_Func,void>
  {
    void constraints() {
      __f();              // require operator() member function
    }
    _Func __f;
  };
#endif

  template <class _Func, class _Ret, class _Arg>
  struct UnaryFunctionConcept
  {
    void constraints() {
      __r = __f(__arg); // require operator()
    }
    _Func __f;
    _Arg __arg;
    _Ret __r;
  };

#if !defined BOOST_NO_TEMPLATE_PARTIAL_SPECIALIZATION
  template <class _Func, class _Arg>
  struct UnaryFunctionConcept<_Func,void,_Arg> {
    void constraints() { 
      __f(__arg);                 // require operator()
    }
    _Func __f;
  };
#endif

  template <class _Func, class _Ret, class _First, class _Second>
  struct BinaryFunctionConcept
  {
    void constraints() { 
      __r = __f(__first, __second); // require operator()
    }
    _Func __f;
    _First __first;
    _Second __second;
    _Ret __r;
  };

#if !defined BOOST_NO_TEMPLATE_PARTIAL_SPECIALIZATION
  template <class _Func, class _First, class _Second>
  struct BinaryFunctionConcept<_Func,void,_First,_Second>
  {
    void constraints() {
      __f(__first, __second); // require operator()
    }
    _Func __f;
    _First __first;
    _Second __second;
  };
#endif

  template <class Func, class Arg>
  struct UnaryPredicateConcept
  {
    void constraints() {
      require_boolean_expr(f(arg)); // require operator() returning bool
    }
    Func f;
    Arg arg;
  };

  template <class Func, class First, class Second>
  struct BinaryPredicateConcept
  {
    void constraints() {
      require_boolean_expr(f(a, b)); // require operator() returning bool
    }
    Func f;
    First a;
    Second b;
  };

  // use this when functor is used inside a container class like std::set
  template <class Func, class First, class Second>
  struct Const_BinaryPredicateConcept {
    void constraints() { 
      const_constraints(f);
    }
    void const_constraints(const Func& fun) {
      function_requires<BinaryPredicateConcept<Func, First, Second> >();
      // operator() must be a const member function
      require_boolean_expr(fun(a, b));
    }
    Func f;
    First a;
    Second b;
  };

#define BOOST_DEFINE_BINARY_PREDICATE_OP_CONSTRAINT(OP,NAME) \
  template <class First, class Second> \
  struct NAME { \
    void constraints() { (void)constraints_(); } \
    bool constraints_() {  \
      return  a OP b; \
    } \
    First a; \
    Second b; \
  }

#define BOOST_DEFINE_BINARY_OPERATOR_CONSTRAINT(OP,NAME) \
  template <class Ret, class First, class Second> \
  struct NAME { \
    void constraints() { (void)constraints_(); } \
    Ret constraints_() {  \
      Ret x = a OP b; \
    } \
    First a; \
    Second b; \
  }

  BOOST_DEFINE_BINARY_PREDICATE_OP_CONSTRAINT(==, EqualOpConcept);
  BOOST_DEFINE_BINARY_PREDICATE_OP_CONSTRAINT(!=, NotEqualOpConcept);
  BOOST_DEFINE_BINARY_PREDICATE_OP_CONSTRAINT(<, LessThanOpConcept);
  BOOST_DEFINE_BINARY_PREDICATE_OP_CONSTRAINT(<=, LessEqualOpConcept);
  BOOST_DEFINE_BINARY_PREDICATE_OP_CONSTRAINT(>, GreaterThanOpConcept);
  BOOST_DEFINE_BINARY_PREDICATE_OP_CONSTRAINT(>=, GreaterEqualOpConcept);

  BOOST_DEFINE_BINARY_OPERATOR_CONSTRAINT(+, PlusOpConcept);
  BOOST_DEFINE_BINARY_OPERATOR_CONSTRAINT(*, TimesOpConcept);
  BOOST_DEFINE_BINARY_OPERATOR_CONSTRAINT(/, DivideOpConcept);
  BOOST_DEFINE_BINARY_OPERATOR_CONSTRAINT(-, SubtractOpConcept);
  BOOST_DEFINE_BINARY_OPERATOR_CONSTRAINT(%, ModOpConcept);

  //===========================================================================
  // Container Concepts

  template <class Container>
  struct ContainerConcept
  {
    typedef typename Container::value_type value_type;
    typedef typename Container::difference_type difference_type;
    typedef typename Container::size_type size_type;
    typedef typename Container::const_reference const_reference;
    typedef typename Container::const_pointer const_pointer;
    typedef typename Container::const_iterator const_iterator;

    void constraints() {
      function_requires< InputIteratorConcept<const_iterator> >();
      function_requires< AssignableConcept<Container> >();
      const Container c;
      i = c.begin();
      i = c.end();
      n = c.size();
      n = c.max_size();
      b = c.empty();
    }
    bool b;
    const_iterator i;
    size_type n;
  };

  template <class Container>
  struct Mutable_ContainerConcept
  {
    typedef typename Container::value_type value_type;
    typedef typename Container::reference reference;
    typedef typename Container::iterator iterator;
    typedef typename Container::pointer pointer;
    
    void constraints() {
      function_requires< ContainerConcept<Container> >();
      function_requires< AssignableConcept<value_type> >();
      function_requires< InputIteratorConcept<iterator> >();

      i = c.begin();
      i = c.end();
      c.swap(c2);
    }
    iterator i;
    Container c, c2;
  };

  template <class ForwardContainer>
  struct ForwardContainerConcept
  {
    void constraints() {
      function_requires< ContainerConcept<ForwardContainer> >();
      typedef typename ForwardContainer::const_iterator const_iterator;
      function_requires< ForwardIteratorConcept<const_iterator> >();
    }
  };  

  template <class ForwardContainer>
  struct Mutable_ForwardContainerConcept
  {
    void constraints() {
      function_requires< ForwardContainerConcept<ForwardContainer> >();
      function_requires< Mutable_ContainerConcept<ForwardContainer> >();
      typedef typename ForwardContainer::iterator iterator;
      function_requires< Mutable_ForwardIteratorConcept<iterator> >();
    }
  };  

  template <class ReversibleContainer>
  struct ReversibleContainerConcept
  {
    typedef typename ReversibleContainer::const_iterator const_iterator;
    typedef typename ReversibleContainer::const_reverse_iterator
      const_reverse_iterator;

    void constraints() {
      function_requires< ForwardContainerConcept<ReversibleContainer> >();
      function_requires< BidirectionalIteratorConcept<const_iterator> >();
      function_requires< BidirectionalIteratorConcept<const_reverse_iterator> >();

      const ReversibleContainer c;
      const_reverse_iterator i = c.rbegin();
      i = c.rend();
    }
  };

  template <class ReversibleContainer>
  struct Mutable_ReversibleContainerConcept
  {
    typedef typename ReversibleContainer::iterator iterator;
    typedef typename ReversibleContainer::reverse_iterator reverse_iterator;

    void constraints() {
      function_requires< ReversibleContainerConcept<ReversibleContainer> >();
      function_requires< Mutable_ForwardContainerConcept<ReversibleContainer> >();
      function_requires< Mutable_BidirectionalIteratorConcept<iterator> >();
      function_requires< Mutable_BidirectionalIteratorConcept<reverse_iterator> >();

      reverse_iterator i = c.rbegin();
      i = c.rend();
    }
    ReversibleContainer c;
  };

  template <class RandomAccessContainer>
  struct RandomAccessContainerConcept
  {
    typedef typename RandomAccessContainer::size_type size_type;
    typedef typename RandomAccessContainer::const_reference const_reference;
    typedef typename RandomAccessContainer::const_iterator const_iterator;
    typedef typename RandomAccessContainer::const_reverse_iterator
      const_reverse_iterator;

    void constraints() {
      function_requires< ReversibleContainerConcept<RandomAccessContainer> >();
      function_requires< RandomAccessIteratorConcept<const_iterator> >();
      function_requires< RandomAccessIteratorConcept<const_reverse_iterator> >();

      const RandomAccessContainer c;
      const_reference r = c[n];
      ignore_unused_variable_warning(r);
    }
    size_type n;
  };

  template <class RandomAccessContainer>
  struct Mutable_RandomAccessContainerConcept
  {
    typedef typename RandomAccessContainer::size_type size_type;
    typedef typename RandomAccessContainer::reference reference;
    typedef typename RandomAccessContainer::iterator iterator;
    typedef typename RandomAccessContainer::reverse_iterator reverse_iterator;

    void constraints() {
      function_requires< RandomAccessContainerConcept<RandomAccessContainer> >();
      function_requires< Mutable_ReversibleContainerConcept<RandomAccessContainer> >();
      function_requires< Mutable_RandomAccessIteratorConcept<iterator> >();
      function_requires< Mutable_RandomAccessIteratorConcept<reverse_iterator> >();

      reference r = c[i];
      ignore_unused_variable_warning(r);
    }
    size_type i;
    RandomAccessContainer c;
  };

  // A Sequence is inherently mutable
  template <class Sequence>
  struct SequenceConcept
  {

    typedef typename Sequence::reference reference;
    typedef typename Sequence::const_reference const_reference;

    void constraints() {
      // Matt Austern's book puts DefaultConstructible here, the C++
      // standard places it in Container
      //    function_requires< DefaultConstructible<Sequence> >();
      function_requires< Mutable_ForwardContainerConcept<Sequence> >();
      function_requires< DefaultConstructibleConcept<Sequence> >();

      Sequence 
        c(n),
        c2(n, t),
        c3(first, last);

      c.insert(p, t);
      c.insert(p, n, t);
      c.insert(p, first, last);

      c.erase(p);
      c.erase(p, q);

      reference r = c.front();

      ignore_unused_variable_warning(c);
      ignore_unused_variable_warning(c2);
      ignore_unused_variable_warning(c3);
      ignore_unused_variable_warning(r);
      const_constraints(c);
    }
    void const_constraints(const Sequence& c) {
      const_reference r = c.front();
      ignore_unused_variable_warning(r);
    }
    typename Sequence::value_type t;
    typename Sequence::size_type n;
    typename Sequence::value_type* first, *last;
    typename Sequence::iterator p, q;
  };

  template <class FrontInsertionSequence>
  struct FrontInsertionSequenceConcept
  {
    void constraints() {
      function_requires< SequenceConcept<FrontInsertionSequence> >();

      c.push_front(t);
      c.pop_front();
    }
    FrontInsertionSequence c;
    typename FrontInsertionSequence::value_type t;
  };

  template <class BackInsertionSequence>
  struct BackInsertionSequenceConcept
  {
    typedef typename BackInsertionSequence::reference reference;
    typedef typename BackInsertionSequence::const_reference const_reference;

    void constraints() {
      function_requires< SequenceConcept<BackInsertionSequence> >();

      c.push_back(t);
      c.pop_back();
      reference r = c.back();
      ignore_unused_variable_warning(r);
    }
    void const_constraints(const BackInsertionSequence& c) {
      const_reference r = c.back();
      ignore_unused_variable_warning(r);
    };
    BackInsertionSequence c;
    typename BackInsertionSequence::value_type t;
  };

  template <class AssociativeContainer>
  struct AssociativeContainerConcept
  {
    void constraints() {
      function_requires< ForwardContainerConcept<AssociativeContainer> >();
      function_requires< DefaultConstructibleConcept<AssociativeContainer> >();
    
      i = c.find(k);
      r = c.equal_range(k);
      c.erase(k);
      c.erase(i);
      c.erase(r.first, r.second);
      const_constraints(c);
    }
    void const_constraints(const AssociativeContainer& c) {
      ci = c.find(k);
      n = c.count(k);
      cr = c.equal_range(k);
    }
    typedef typename AssociativeContainer::iterator iterator;
    typedef typename AssociativeContainer::const_iterator const_iterator;

    AssociativeContainer c;
    iterator i;
    std::pair<iterator,iterator> r;
    const_iterator ci;
    std::pair<const_iterator,const_iterator> cr;
    typename AssociativeContainer::key_type k;
    typename AssociativeContainer::size_type n;
  };

  template <class UniqueAssociativeContainer>
  struct UniqueAssociativeContainerConcept
  {
    void constraints() {
      function_requires< AssociativeContainerConcept<UniqueAssociativeContainer> >();
    
      UniqueAssociativeContainer c(first, last);
      
      pos_flag = c.insert(t);
      c.insert(first, last);

      ignore_unused_variable_warning(c);
    }
    std::pair<typename UniqueAssociativeContainer::iterator, bool> pos_flag;
    typename UniqueAssociativeContainer::value_type t;
    typename UniqueAssociativeContainer::value_type* first, *last;
  };

  template <class MultipleAssociativeContainer>
  struct MultipleAssociativeContainerConcept
  {
    void constraints() {
      function_requires< AssociativeContainerConcept<MultipleAssociativeContainer> >();

      MultipleAssociativeContainer c(first, last);
      
      pos = c.insert(t);
      c.insert(first, last);

      ignore_unused_variable_warning(c);
      ignore_unused_variable_warning(pos);
    }
    typename MultipleAssociativeContainer::iterator pos;
    typename MultipleAssociativeContainer::value_type t;
    typename MultipleAssociativeContainer::value_type* first, *last;
  };

  template <class SimpleAssociativeContainer>
  struct SimpleAssociativeContainerConcept
  {
    void constraints() {
      function_requires< AssociativeContainerConcept<SimpleAssociativeContainer> >();
      typedef typename SimpleAssociativeContainer::key_type key_type;
      typedef typename SimpleAssociativeContainer::value_type value_type;
      typedef typename require_same<key_type, value_type>::type req;
    }
  };

  template <class SimpleAssociativeContainer>
  struct PairAssociativeContainerConcept
  {
    void constraints() {
      function_requires< AssociativeContainerConcept<SimpleAssociativeContainer> >();
      typedef typename SimpleAssociativeContainer::key_type key_type;
      typedef typename SimpleAssociativeContainer::value_type value_type;
      typedef typename SimpleAssociativeContainer::mapped_type mapped_type;
      typedef std::pair<const key_type, mapped_type> required_value_type;
      typedef typename require_same<value_type, required_value_type>::type req;
    }
  };

  template <class SortedAssociativeContainer>
  struct SortedAssociativeContainerConcept
  {
    void constraints() {
      function_requires< AssociativeContainerConcept<SortedAssociativeContainer> >();
      function_requires< ReversibleContainerConcept<SortedAssociativeContainer> >();

      SortedAssociativeContainer 
        c(kc),
        c2(first, last),
        c3(first, last, kc);

      p = c.upper_bound(k);
      p = c.lower_bound(k);
      r = c.equal_range(k);
      
      c.insert(p, t);
      
      ignore_unused_variable_warning(c);
      ignore_unused_variable_warning(c2);
      ignore_unused_variable_warning(c3);
    }
    void const_constraints(const SortedAssociativeContainer& c) {
      kc = c.key_comp();
      vc = c.value_comp();

      cp = c.upper_bound(k);
      cp = c.lower_bound(k);
      cr = c.equal_range(k);
    }
    typename SortedAssociativeContainer::key_compare kc;
    typename SortedAssociativeContainer::value_compare vc;
    typename SortedAssociativeContainer::value_type t;
    typename SortedAssociativeContainer::key_type k;
    typedef typename SortedAssociativeContainer::iterator iterator;
    typedef typename SortedAssociativeContainer::const_iterator const_iterator;
    iterator p;
    const_iterator cp;
    std::pair<iterator,iterator> r;
    std::pair<const_iterator,const_iterator> cr;
    typename SortedAssociativeContainer::value_type* first, *last;
  };

  // HashedAssociativeContainer

} // namespace boost

#endif // BOOST_CONCEPT_CHECKS_HPP

