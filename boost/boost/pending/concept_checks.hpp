//
// (C) Copyright Jeremy Siek 2000. Permission to copy, use, modify,
// sell and distribute this software is granted provided this
// copyright notice appears in all copies. This software is provided
// "as is" without express or implied warranty, and with no claim as
// to its suitability for any purpose.
//
#ifndef BOOST_GRAPH_DETAIL_CONCEPT_CHECKS_HPP
#define BOOST_GRAPH_DETAIL_CONCEPT_CHECKS_HPP

#include <iterator>
#include <utility>
#include <boost/config.hpp>
#include <boost/pending/limits.hpp>

#if defined(__GNUC__) || defined(__KCC) || defined(__ghs) || defined(__MWERKS__)
#define BOOST_FPTR &
#else
#define BOOST_FPTR
#endif

#define REQUIRE(__type_var, __concept) \
do { \
  void (__concept##_concept <__type_var>::*__x)() = \
    BOOST_FPTR __concept##_concept <__type_var>::constraints; \
  __x = __x; } while (0)

#define REQUIRE2(__type_var1, __type_var2, __concept) \
do { \
  void (__concept##_concept <__type_var1, __type_var2>::*__x)() = \
    BOOST_FPTR __concept##_concept <__type_var1, __type_var2>::constraints; \
  __x = __x; } while (0)

#define REQUIRE3(__type_var1, __type_var2, __type_var3,__concept) \
do { \
  void (__concept##_concept <__type_var1, __type_var2, __type_var3>::*__x)() = \
    BOOST_FPTR __concept##_concept <__type_var1, __type_var2, __type_var3>::constraints; \
  __x = __x; } while (0)

#define REQUIRE4(__type_var1, __type_var2, __type_var3,__type_var4,__concept) \
do { \
 void (__concept##_concept <__type_var1,__type_var2,__type_var3,__type_var4>::*__x)() = \
 BOOST_FPTR __concept##_concept <__type_var1, __type_var2, __type_var3, __type_var4>::constraints;\
  __x = __x; } while (0)


#define CLASS_REQUIRES(__tv, __concept) \
  typedef void (__concept##_concept <__tv>::* __func##__tv##__concept)(); \
  template <__func##__tv##__concept _Tp1> \
  struct __dummy_struct_##__tv##__concept { }; \
  typedef __dummy_struct_##__tv##__concept< \
    BOOST_FPTR __concept##_concept <__tv>::constraints> \
    __dummy_typedef_##__tv##__concept

#define CLASS_REQUIRES2(__tv1, __tv2, __concept) \
  typedef void (__concept##_concept <__tv1,__tv2>::* __func##__tv1##__tv2##__concept)(); \
  template <__func##__tv1##__tv2##__concept _Tp1> \
  struct __dummy_struct_##__tv1##__tv2##__concept { }; \
  typedef __dummy_struct_##__tv1##__tv2##__concept< \
    BOOST_FPTR __concept##_concept <__tv1,__tv2>::constraints> \
    __dummy_typedef_##__tv1##__tv2##__concept

#define CLASS_REQUIRES3(__tv1, __tv2, __tv3, __concept) \
  typedef void (__concept##_concept <__tv1,__tv2,__tv3>::* __func##__tv1##__tv2##__tv3##__concept)(); \
  template <__func##__tv1##__tv2##__tv3##__concept _Tp1> \
  struct __dummy_struct_##__tv1##__tv2##__tv3##__concept { }; \
  typedef __dummy_struct_##__tv1##__tv2##__tv3##__concept< \
    BOOST_FPTR __concept##_concept <__tv1,__tv2,__tv3>::constraints>  \
  __dummy_typedef_##__tv1##__tv2##__tv3##__concept

#define CLASS_REQUIRES4(__tv1, __tv2, __tv3, __tv4, __concept) \
  typedef void (__concept##_concept <__tv1,__tv2,__tv3,__tv4>::* __func##__tv1##__tv2##__tv3##__tv4##__concept)(); \
  template <__func##__tv1##__tv2##__tv3##__tv4##__concept _Tp1> \
  struct __dummy_struct_##__tv1##__tv2##__tv3##__tv4##__concept { }; \
  typedef __dummy_struct_##__tv1##__tv2##__tv3##__tv4##__concept< \
    BOOST_FPTR __concept##_concept <__tv1,__tv2,__tv3,__tv4>::constraints>  \
    __dummy_typedef_##__tv1##__tv2##__tv3##__tv4##__concept


#if !defined BOOST_NO_TEMPLATE_PARTIAL_SPECIALIZATION
template <class T, class U>
struct require_same_type { };

template <class T>
struct require_same_type<T,T> { typedef T type; };
#else
template <class T, class U>
struct require_same_type { typedef T type; };
#endif

#define REQUIRE_SAME_TYPE(X,Y) \
  typedef typename require_same_type<X,Y>::type X##_same_##Y

#define CLASS_REQUIRES_SAME_TYPE(X,Y) \
  typedef typename require_same_type<X,Y>::type X##_same_##Y

template <class T> void ignore_unused_variable_warning(const T&) { }

  template <class T>
  struct Integer_concept {
    void constraints() { 
#if !defined BOOST_NO_TEMPLATE_PARTIAL_SPECIALIZATION
      error__type_must_be_an_integer_type();
#endif      
    }
  };
#if !defined BOOST_NO_TEMPLATE_PARTIAL_SPECIALIZATION
  template <> struct Integer_concept<short> { void constraints() {} };
  template <> struct Integer_concept<unsigned short> { void constraints() {} };
  template <> struct Integer_concept<int> { void constraints() {} };
  template <> struct Integer_concept<unsigned int> { void constraints() {} };
  template <> struct Integer_concept<long> { void constraints() {} };
  template <> struct Integer_concept<unsigned long> { void constraints() {} };
  // etc.
#endif      

  template <class T>
  struct SignedInteger_concept {
    void constraints() { 
#if !defined BOOST_NO_TEMPLATE_PARTIAL_SPECIALIZATION
      error__type_must_be_a_signed_integer_type();
#endif      
    }
  };
#if !defined BOOST_NO_TEMPLATE_PARTIAL_SPECIALIZATION
  template <> struct SignedInteger_concept<short> { void constraints() {} };
  template <> struct SignedInteger_concept<int> { void constraints() {} };
  template <> struct SignedInteger_concept<long> { void constraints() {} };
  // etc.
#endif      

  //===========================================================================
  // Basic Concepts

  template <class X, class Y>
  struct Convertible_concept
  {
    void constraints() {
      Y y = x;
      ignore_unused_variable_warning(y);
    }
    X x;
  };

  // Issue, the SGI STL version of Assignable is
  // different from the C++ standard definition of Assignable.
  // This follows the C++ standard version.
  template <class TT>
  struct Assignable_concept
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
  struct DefaultConstructible_concept
  {
    void constraints() {
      TT a;               // require default constructor
      ignore_unused_variable_warning(a);
    }
  };

  template <class T>
  struct CopyConstructible_concept
  {
    void constraints() {
      T a(b);            // require copy constructor
      T* ptr = &a;       // require address of operator
      const_constraints(a);
    }
    void const_constraints(const T& a) {
      T c(a);            // require const copy constructor
      const T* ptr = &a; // require const address of operator
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
  struct EqualityComparable_concept
  {
    void constraints() {
      require_boolean_expr(a == b);
      require_boolean_expr(a != b);
    }
    bool boolean;
    TT a, b;
  };

  template <class XX, class YY>
  struct LeftEqualityComparable_concept
  {
    void constraints() {
      require_boolean_expr(b == a);
      require_boolean_expr(b != a);
    }
    XX a;
    YY b;
  };

  template <class TT>
  struct LessThanComparable_concept
  {
    void constraints() {
      require_boolean_expr(a < b);
      require_boolean_expr(a > b);
      require_boolean_expr(a <= b);
      require_boolean_expr(a >= b);
    }
    bool boolean;
    TT a, b;
  };

  //===========================================================================
  // Iterator Concepts

  template <class TT>
  struct TrivialIterator_concept
  {
    void constraints() {
      REQUIRE(TT, Assignable);
      REQUIRE(TT, DefaultConstructible);
      REQUIRE(TT, EqualityComparable);
#ifndef BOOST_NO_STD_ITERATOR_TRAITS
      typedef typename std::iterator_traits<TT>::value_type V;
#endif
      (void)*i;           // require dereference operator
    }
    TT i;
  };

  template <class TT>
  struct Mutable_TrivialIterator_concept
  {
    void constraints() {
      REQUIRE(TT, TrivialIterator);
      *i = *j;            // require dereference and assignment
    }
    TT i, j;
  };

  template <class TT>
  struct InputIterator_concept
  {
    void constraints() {
      REQUIRE(TT, TrivialIterator);
      // require iterator_traits typedef's
#ifndef BOOST_NO_STD_ITERATOR_TRAITS
      typedef typename std::iterator_traits<TT>::difference_type D;
      REQUIRE(D, SignedInteger);
      typedef typename std::iterator_traits<TT>::reference R;
      typedef typename std::iterator_traits<TT>::pointer P;
      typedef typename std::iterator_traits<TT>::iterator_category C;
      REQUIRE2(typename std::iterator_traits<TT>::iterator_category,
               std::input_iterator_tag, Convertible);
#endif
      ++i;                // require preincrement operator
      i++;                // require postincrement operator
    }
    TT i;
  };

  template <class TT, class ValueT>
  struct OutputIterator_concept
  {
    void constraints() {
      REQUIRE(TT, Assignable);
      ++i;                // require preincrement operator
      i++;                // require postincrement operator
      *i++ = t;           // require postincrement and assignment
    }
    TT i, j;
    ValueT t;
  };

  template <class TT>
  struct ForwardIterator_concept
  {
    void constraints() {
      REQUIRE(TT, InputIterator);
#ifndef BOOST_NO_STD_ITERATOR_TRAITS
      REQUIRE2(typename std::iterator_traits<TT>::iterator_category,
               std::forward_iterator_tag, Convertible);
      typedef typename std::iterator_traits<TT>::reference reference;
      reference r = *i;
      ignore_unused_variable_warning(r);
#endif
    }
    TT i;
  };

  template <class TT>
  struct Mutable_ForwardIterator_concept
  {
    void constraints() {
      REQUIRE(TT, ForwardIterator);
      *i++ = *i;         // require postincrement and assignment
    }
    TT i;
  };

  template <class TT>
  struct BidirectionalIterator_concept
  {
    void constraints() {
      REQUIRE(TT, ForwardIterator);
#ifndef BOOST_NO_STD_ITERATOR_TRAITS
      REQUIRE2(typename std::iterator_traits<TT>::iterator_category,
               std::bidirectional_iterator_tag, Convertible);
#endif
      --i;                // require predecrement operator
      i--;                // require postdecrement operator
    }
    TT i;
  };

  template <class TT>
  struct Mutable_BidirectionalIterator_concept
  {
    void constraints() {
      REQUIRE(TT, BidirectionalIterator);
      REQUIRE(TT, Mutable_ForwardIterator);
      *i-- = *i;                  // require postdecrement and assignment
    }
    TT i;
  };


  template <class TT>
  struct RandomAccessIterator_concept
  {
    void constraints() {
      REQUIRE(TT, BidirectionalIterator);
      REQUIRE(TT, LessThanComparable);
#ifndef BOOST_NO_STD_ITERATOR_TRAITS
      REQUIRE2(typename std::iterator_traits<TT>::iterator_category,
        std::random_access_iterator_tag, Convertible);
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
  struct Mutable_RandomAccessIterator_concept
  {
    void constraints() {
      REQUIRE(TT, RandomAccessIterator);
      REQUIRE(TT, Mutable_BidirectionalIterator);
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
  struct Generator_concept
  {
    void constraints() {
      __r = __f();   // require operator() member function
    }
    _Func __f;
    _Ret __r;
  };


#if !defined BOOST_NO_TEMPLATE_PARTIAL_SPECIALIZATION
  template <class _Func>
  struct Generator_concept<_Func,void>
  {
    void constraints() {
      __f();              // require operator() member function
    }
    _Func __f;
  };
#endif

  template <class _Func, class _Ret, class _Arg>
  struct UnaryFunction_concept
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
  struct UnaryFunction_concept<_Func,void,_Arg> {
    void constraints() { 
      __f(__arg);                 // require operator()
    }
    _Func __f;
  };
#endif

  template <class _Func, class _Ret, class _First, class _Second>
  struct BinaryFunction_concept
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
  struct BinaryFunction_concept<_Func,void,_First,_Second>
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
  struct UnaryPredicate_concept
  {
    void constraints() {
      require_boolean_expr(f(arg)); // require operator() returning bool
    }
    Func f;
    Arg arg;
  };

  template <class Func, class First, class Second>
  struct BinaryPredicate_concept
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
  struct Const_BinaryPredicate_concept {
    void constraints() { 
      REQUIRE3(Func, First, Second, BinaryPredicate);
      require_boolean_expr(f(a, b)); // operator() must be a const member function
    }
    const Func f;
    First a;
    Second b;
  };

#define __STL_DEFINE_BINARY_OPERATOR_CONSTRAINT(_OP,_NAME) \
  template <class _Ret, class _First, class _Second> \
  struct _NAME##_concept { \
    void constraints() { (void)_constraints(); } \
    _Ret _constraints() {  \
      return __a _OP __b; \
    } \
    _First __a; \
    _Second __b; \
  }

  __STL_DEFINE_BINARY_OPERATOR_CONSTRAINT(==, _OP_EQUAL);
  __STL_DEFINE_BINARY_OPERATOR_CONSTRAINT(!=, _OP_NOT_EQUAL);
  __STL_DEFINE_BINARY_OPERATOR_CONSTRAINT(<, _OP_LESS_THAN);
  __STL_DEFINE_BINARY_OPERATOR_CONSTRAINT(<=, _OP_LESS_EQUAL);
  __STL_DEFINE_BINARY_OPERATOR_CONSTRAINT(>, _OP_GREATER_THAN);
  __STL_DEFINE_BINARY_OPERATOR_CONSTRAINT(>=, _OP_GREATER_EQUAL);
  __STL_DEFINE_BINARY_OPERATOR_CONSTRAINT(+, _OP_PLUS);
  __STL_DEFINE_BINARY_OPERATOR_CONSTRAINT(*, _OP_TIMES);
  __STL_DEFINE_BINARY_OPERATOR_CONSTRAINT(/, _OP_DIVIDE);
  __STL_DEFINE_BINARY_OPERATOR_CONSTRAINT(-, _OP_SUBTRACT);
  __STL_DEFINE_BINARY_OPERATOR_CONSTRAINT(%, _OP_MOD);

  //===========================================================================
  // Container Concepts

  template <class Container>
  struct Container_concept
  {
    typedef typename Container::value_type value_type;
    typedef typename Container::difference_type difference_type;
    typedef typename Container::size_type size_type;
    typedef typename Container::const_reference const_reference;
    typedef typename Container::const_pointer const_pointer;
    typedef typename Container::const_iterator const_iterator;

    void constraints() {
      REQUIRE(const_iterator, InputIterator);
      REQUIRE(Container, Assignable);
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
  struct Mutable_Container_concept
  {
    typedef typename Container::value_type value_type;
    typedef typename Container::reference reference;
    typedef typename Container::iterator iterator;
    typedef typename Container::pointer pointer;
    
    void constraints() {
      REQUIRE(Container, Container);
      REQUIRE(value_type, Assignable);
      REQUIRE(iterator, InputIterator);

      i = c.begin();
      i = c.end();
      c.swap(c2);
    }
    iterator i;
    Container c, c2;
  };

  template <class ForwardContainer>
  struct ForwardContainer_concept
  {
    void constraints() {
      REQUIRE(ForwardContainer, Container);
      typedef typename ForwardContainer::const_iterator const_iterator;
      REQUIRE(const_iterator, ForwardIterator);
    }
  };  

  template <class ForwardContainer>
  struct Mutable_ForwardContainer_concept
  {
    void constraints() {
      REQUIRE(ForwardContainer, ForwardContainer);
      REQUIRE(ForwardContainer, Mutable_Container);
      typedef typename ForwardContainer::iterator iterator;
      REQUIRE(iterator, Mutable_ForwardIterator);
    }
  };  

  template <class ReversibleContainer>
  struct ReversibleContainer_concept
  {
    typedef typename ReversibleContainer::const_iterator const_iterator;
    typedef typename ReversibleContainer::const_reverse_iterator
      const_reverse_iterator;

    void constraints() {
      REQUIRE(ReversibleContainer, ForwardContainer);
      REQUIRE(const_iterator, BidirectionalIterator);
      REQUIRE(const_reverse_iterator, BidirectionalIterator);

      const ReversibleContainer c;
      const_reverse_iterator i = c.rbegin();
      i = c.rend();
    }
  };

  template <class ReversibleContainer>
  struct Mutable_ReversibleContainer_concept
  {
    typedef typename ReversibleContainer::iterator iterator;
    typedef typename ReversibleContainer::reverse_iterator reverse_iterator;

    void constraints() {
      REQUIRE(ReversibleContainer, ReversibleContainer);
      REQUIRE(ReversibleContainer, Mutable_ForwardContainer);
      REQUIRE(iterator, Mutable_BidirectionalIterator);
      REQUIRE(reverse_iterator, Mutable_BidirectionalIterator);

      reverse_iterator i = c.rbegin();
      i = c.rend();
    }
    ReversibleContainer c;
  };

  template <class RandomAccessContainer>
  struct RandomAccessContainer_concept
  {
    typedef typename RandomAccessContainer::size_type size_type;
    typedef typename RandomAccessContainer::const_reference const_reference;
    typedef typename RandomAccessContainer::const_iterator const_iterator;
    typedef typename RandomAccessContainer::const_reverse_iterator
      const_reverse_iterator;

    void constraints() {
      REQUIRE(RandomAccessContainer, ReversibleContainer);
      REQUIRE(const_iterator, RandomAccessIterator);
      REQUIRE(const_reverse_iterator, RandomAccessIterator);

      const RandomAccessContainer c;
      const_reference r = c[n];
      ignore_unused_variable_warning(r);
    }
    size_type n;
  };

  template <class RandomAccessContainer>
  struct Mutable_RandomAccessContainer_concept
  {
    typedef typename RandomAccessContainer::size_type size_type;
    typedef typename RandomAccessContainer::reference reference;
    typedef typename RandomAccessContainer::iterator iterator;
    typedef typename RandomAccessContainer::reverse_iterator reverse_iterator;

    void constraints() {
      REQUIRE(RandomAccessContainer, RandomAccessContainer);
      REQUIRE(RandomAccessContainer, Mutable_ReversibleContainer);    
      REQUIRE(iterator, Mutable_RandomAccessIterator);
      REQUIRE(reverse_iterator, Mutable_RandomAccessIterator);

      reference r = c[i];
      ignore_unused_variable_warning(r);
    }
    size_type i;
    RandomAccessContainer c;
  };

  // A Sequence is inherently mutable
  template <class Sequence>
  struct Sequence_concept
  {
    // Matt put's DefaultConstructible here, the C++ standard
    // places it in Container
    //    CLASS_REQUIRES(Sequence, DefaultConstructible);

    typedef typename Sequence::reference reference;
    typedef typename Sequence::const_reference const_reference;

    void constraints() {
      REQUIRE(Sequence, Mutable_ForwardContainer);
      REQUIRE(Sequence, DefaultConstructible);

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
  struct FrontInsertionSequence_concept
  {
    void constraints() {
      REQUIRE(FrontInsertionSequence, Sequence);

      c.push_front(t);
      c.pop_front();
    }
    FrontInsertionSequence c;
    typename FrontInsertionSequence::value_type t;
  };

  template <class BackInsertionSequence>
  struct BackInsertionSequence_concept
  {
    typedef typename BackInsertionSequence::reference reference;
    typedef typename BackInsertionSequence::const_reference const_reference;

    void constraints() {
      REQUIRE(BackInsertionSequence, Sequence);

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
  struct AssociativeContainer_concept
  {
    void constraints() {
      REQUIRE(AssociativeContainer, ForwardContainer);
      REQUIRE(AssociativeContainer, DefaultConstructible);
    
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
  struct UniqueAssociativeContainer_concept
  {
    void constraints() {
      REQUIRE(UniqueAssociativeContainer, AssociativeContainer);
    
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
  struct MultipleAssociativeContainer_concept
  {
    void constraints() {
      REQUIRE(MultipleAssociativeContainer, AssociativeContainer);

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
  struct SimpleAssociativeContainer_concept
  {
    void constraints() {
      REQUIRE(SimpleAssociativeContainer, AssociativeContainer);
      typedef typename SimpleAssociativeContainer::key_type key_type;
      typedef typename SimpleAssociativeContainer::value_type value_type;
      REQUIRE_SAME_TYPE(key_type, value_type);
    }
  };

  template <class SimpleAssociativeContainer>
  struct PairAssociativeContainer_concept
  {
    void constraints() {
      REQUIRE(SimpleAssociativeContainer, AssociativeContainer);
      typedef typename SimpleAssociativeContainer::key_type key_type;
      typedef typename SimpleAssociativeContainer::value_type value_type;
      typedef typename SimpleAssociativeContainer::mapped_type mapped_type;
      typedef std::pair<const key_type, mapped_type> required_value_type;
      REQUIRE_SAME_TYPE(value_type, required_value_type);
    }
  };

  template <class SortedAssociativeContainer>
  struct SortedAssociativeContainer_concept
  {
    void constraints() {
      REQUIRE(SortedAssociativeContainer, AssociativeContainer);
      REQUIRE(SortedAssociativeContainer, ReversibleContainer);

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

#endif /* BOOST_GRAPH_DETAIL_CONCEPT_CHECKS_H */

