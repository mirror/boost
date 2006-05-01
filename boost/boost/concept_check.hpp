//
// (C) Copyright Jeremy Siek 2000.
// Distributed under the Boost Software License, Version 1.0. (See
// accompanying file LICENSE_1_0.txt or copy at
// http://www.boost.org/LICENSE_1_0.txt)
//
// Revision History:
//   05 May   2001: Workarounds for HP aCC from Thomas Matelich. (Jeremy Siek)
//   02 April 2001: Removed limits header altogether. (Jeremy Siek)
//   01 April 2001: Modified to use new <boost/limits.hpp> header. (JMaddock)
//

// See http://www.boost.org/libs/concept_check for documentation.

#ifndef BOOST_CONCEPT_CHECKS_HPP
# define BOOST_CONCEPT_CHECKS_HPP

# include <boost/concept_check/assert.hpp>

# include <boost/iterator.hpp>
# include <boost/type_traits/conversion_traits.hpp>
# include <utility>
# include <boost/type_traits/is_same.hpp>
# include <boost/type_traits/is_void.hpp>
# include <boost/mpl/assert.hpp>
# include <boost/detail/workaround.hpp>
# include <boost/detail/iterator.hpp>


namespace boost
{

  //
  // Backward compatibility
  //
  
  template <class Model>
  inline void function_requires(BOOST_EXPLICIT_TEMPLATE_TYPE(Model))
  {
      BOOST_CONCEPT_ASSERT((Model));
  }    
  template <class T> inline void ignore_unused_variable_warning(T const&) {}
  
#  define BOOST_CLASS_REQUIRE(type_var, ns, concept)    \
    BOOST_CONCEPT_ASSERT((ns::concept<type_var>))

#  define BOOST_CLASS_REQUIRE2(type_var1, type_var2, ns, concept)   \
    BOOST_CONCEPT_ASSERT((ns::concept<type_var1,type_var2>))

#  define BOOST_CLASS_REQUIRE3(tv1, tv2, tv3, ns, concept)  \
    BOOST_CONCEPT_ASSERT((ns::concept<tv1,tv2,tv3>))

#  define BOOST_CLASS_REQUIRE4(tv1, tv2, tv3, tv4, ns, concept) \
    BOOST_CONCEPT_ASSERT((ns::concept<tv1,tv2,tv3,tv4>))

  
  //
  // Begin concept definitions
  //
  template <class T>
  struct IntegerConcept {
    ~IntegerConcept() { 
      x.error_type_must_be_an_integer_type();
    }
   private:
    T x;
  };

  template <> struct IntegerConcept<signed char> {};
  template <> struct IntegerConcept<unsigned char> {};
  template <> struct IntegerConcept<short> {};
  template <> struct IntegerConcept<unsigned short> {};
  template <> struct IntegerConcept<int> {};
  template <> struct IntegerConcept<unsigned int> {};
  template <> struct IntegerConcept<long> {};
  template <> struct IntegerConcept<unsigned long> {};
  // etc.

  template <class T>
  struct SignedIntegerConcept {
    ~SignedIntegerConcept() { 
      x.error_type_must_be_a_signed_integer_type();
    }
   private:
    T x;
  };
  template <> struct SignedIntegerConcept<signed char> { };
  template <> struct SignedIntegerConcept<short> {};
  template <> struct SignedIntegerConcept<int> {};
  template <> struct SignedIntegerConcept<long> {};
# if defined(BOOST_HAS_LONG_LONG)
  template <> struct SignedIntegerConcept< ::boost::long_long_type> {};
  // etc.
#endif      

  template <class T>
  struct UnsignedIntegerConcept {
    ~UnsignedIntegerConcept() { 
      x.error_type_must_be_an_unsigned_integer_type();
    }
   private:
    T x;
  };
  
  template <> struct UnsignedIntegerConcept<unsigned char> {};
  template <> struct UnsignedIntegerConcept<unsigned short> {};
  template <> struct UnsignedIntegerConcept<unsigned int> {};
  template <> struct UnsignedIntegerConcept<unsigned long> {};
# if defined(BOOST_HAS_LONG_LONG)
  template <> struct UnsignedIntegerConcept< ::boost::ulong_long_type> {};
  // etc.
#endif      

  // etc.

  //===========================================================================
  // Basic Concepts

  template <class TT>
  struct DefaultConstructibleConcept
  {
    ~DefaultConstructibleConcept() {
      TT a;               // require default constructor
      ignore_unused_variable_warning(a);
    }
  };

  template <class TT>
  struct AssignableConcept
  {
    ~AssignableConcept() {
#if !defined(_ITERATOR_) // back_insert_iterator broken for VC++ STL
      a = a;              // require assignment operator
#endif
      const_constraints(a);
    }
   private:
    void const_constraints(const TT& b) {
#if !defined(_ITERATOR_) // back_insert_iterator broken for VC++ STL
      a = b;              // const required for argument to assignment
#endif
    }
   private:
    TT a;
  };

  template <class TT>
  struct CopyConstructibleConcept
  {
    ~CopyConstructibleConcept() {
      TT a(b);            // require copy constructor
      TT* ptr = &a;       // require address of operator
      const_constraints(a);
      ignore_unused_variable_warning(ptr);
    }
   private:
    void const_constraints(const TT& a) {
      TT c(a);            // require const copy constructor
      const TT* ptr = &a; // require const address of operator
      ignore_unused_variable_warning(c);
      ignore_unused_variable_warning(ptr);
    }
    TT b;
  };

  // The SGI STL version of Assignable requires copy constructor and operator=
  template <class TT>
  struct SGIAssignableConcept
  {
    ~SGIAssignableConcept() {
      TT b(a);
#if !defined(_ITERATOR_) // back_insert_iterator broken for VC++ STL
      a = a;              // require assignment operator
#endif
      const_constraints(a);
      ignore_unused_variable_warning(b);
    }
   private:
    void const_constraints(const TT& b) {
      TT c(b);
#if !defined(_ITERATOR_) // back_insert_iterator broken for VC++ STL
      a = b;              // const required for argument to assignment
#endif
      ignore_unused_variable_warning(c);
    }
    TT a;
  };

  template <class X, class Y>
  struct ConvertibleConcept
  {
    ~ConvertibleConcept() {
      Y y = x;
      ignore_unused_variable_warning(y);
    }
   private:
    X x;
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
  template <class TT>
  void require_boolean_expr(const TT& t) {
    bool x = t;
    ignore_unused_variable_warning(x);
  }

  template <class TT>
  struct EqualityComparableConcept
  {
    ~EqualityComparableConcept() {
      require_boolean_expr(a == b);
      require_boolean_expr(a != b);
    }
   private:
    TT a, b;
  };

  template <class TT>
  struct LessThanComparableConcept
  {
    ~LessThanComparableConcept() {
      require_boolean_expr(a < b);
    }
   private:
    TT a, b;
  };

  // This is equivalent to SGI STL's LessThanComparable.
  template <class TT>
  struct ComparableConcept
  {
    ~ComparableConcept() {
      require_boolean_expr(a < b);
      require_boolean_expr(a > b);
      require_boolean_expr(a <= b);
      require_boolean_expr(a >= b);
    }
   private:
    TT a, b;
  };

#define BOOST_DEFINE_BINARY_PREDICATE_OP_CONSTRAINT(OP,NAME)    \
    template <class First, class Second>                        \
    struct NAME {                                               \
        ~NAME() { (void)constraints_(); }                        \
     private:                                                   \
        bool constraints_() {                                   \
            return  a OP b;                                     \
        }                                                       \
        First a;                                         \
        Second b;                                        \
    }

#define BOOST_DEFINE_BINARY_OPERATOR_CONSTRAINT(OP,NAME)    \
    template <class Ret, class First, class Second>         \
    struct NAME {                                           \
        ~NAME() { (void)constraints_(); }                    \
     private:                                               \
        Ret constraints_() {                                \
            return a OP b;                                  \
        }                                                   \
        First a;                                     \
        Second b;                                    \
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
  // Function Object Concepts

  template <class Func, class Return>
  struct GeneratorConcept
  {
      ~GeneratorConcept() { test(is_void<Return>()); }
      
   private:
      void test(boost::mpl::false_)
      {
          // Do we really want a reference here?
          const Return& r = f();
          ignore_unused_variable_warning(r);
      }

      void test(boost::mpl::true_)
      {
          f();
      }
      
      Func f;
  };


  template <class Func, class Return, class Arg>
  struct UnaryFunctionConcept
  {
      ~UnaryFunctionConcept() { test(is_void<Return>()); }
      
   private:
      void test(boost::mpl::false_)
      {
          f(arg);               // "priming the pump" this way keeps msvc6 happy (ICE)
          Return r = f(arg);
          ignore_unused_variable_warning(r); 
      }
      
      void test(boost::mpl::true_)
      {
          f(arg);
      }
      
      Func f;
      Arg arg;
  };

  template <class Func, class Return, class First, class Second>
  struct BinaryFunctionConcept
  {
      ~BinaryFunctionConcept() { test(is_void<Return>()); }
   private:
      void test(boost::mpl::false_)
      {
          f(first,second);
          Return r = f(first, second); // require operator()
          (void)r;
      }
      
      void test(boost::mpl::true_)
      {
          f(first,second);
      }
      
      Func f;
      First first;
      Second second;
      Return r;
  };

  template <class Func, class Arg>
  struct UnaryPredicateConcept
  {
    ~UnaryPredicateConcept() {
      require_boolean_expr(f(arg)); // require operator() returning bool
    }
   private:
    Func f;
    Arg arg;
  };

  template <class Func, class First, class Second>
  struct BinaryPredicateConcept
  {
    ~BinaryPredicateConcept() {
      require_boolean_expr(f(a, b)); // require operator() returning bool
    }
   private:
    Func f;
    First a;
    Second b;
  };

  // use this when functor is used inside a container class like std::set
  template <class Func, class First, class Second>
  struct Const_BinaryPredicateConcept
    : BinaryPredicateConcept<Func, First, Second>
  {
    ~Const_BinaryPredicateConcept() { 
      const_constraints(f);
    }
   private:
    void const_constraints(const Func& fun) {
      // operator() must be a const member function
      require_boolean_expr(fun(a, b));
    }
    Func f;
    First a;
    Second b;
  };

  template <class Func, class Return>
  struct AdaptableGeneratorConcept
    : GeneratorConcept<Func, typename Func::result_type>
  {
      typedef typename Func::result_type result_type;
      
      ~AdaptableGeneratorConcept()
      {
          BOOST_CONCEPT_ASSERT((ConvertibleConcept<result_type, Return>));
      }
  };

  template <class Func, class Return, class Arg>
  struct AdaptableUnaryFunctionConcept
    : UnaryFunctionConcept<Func, typename Func::result_type, typename Func::argument_type>
  {
      typedef typename Func::argument_type argument_type;
      typedef typename Func::result_type result_type;

      ~AdaptableUnaryFunctionConcept()
      {
          BOOST_CONCEPT_ASSERT((ConvertibleConcept<result_type, Return>));
          BOOST_CONCEPT_ASSERT((ConvertibleConcept<Arg, argument_type>));
      }
  };

  template <class Func, class Return, class First, class Second>
  struct AdaptableBinaryFunctionConcept
    : BinaryFunctionConcept<
          Func
        , typename Func::result_type
        , typename Func::first_argument_type
        , typename Func::second_argument_type
      >
  {
      typedef typename Func::first_argument_type first_argument_type;
      typedef typename Func::second_argument_type second_argument_type;
      typedef typename Func::result_type result_type;
      
      ~AdaptableBinaryFunctionConcept()
      {
          BOOST_CONCEPT_ASSERT((ConvertibleConcept<result_type, Return>));
          BOOST_CONCEPT_ASSERT((ConvertibleConcept<First, first_argument_type>));
          BOOST_CONCEPT_ASSERT((ConvertibleConcept<Second, second_argument_type>));
      }
  };

  template <class Func, class Arg>
  struct AdaptablePredicateConcept
    : UnaryPredicateConcept<Func, Arg>
    , AdaptableUnaryFunctionConcept<Func, bool, Arg>
  {};

  template <class Func, class First, class Second>
  struct AdaptableBinaryPredicateConcept
    : BinaryPredicateConcept<Func, First, Second>
    , AdaptableBinaryFunctionConcept<Func, bool, First, Second>
  {};

  //===========================================================================
  // Iterator Concepts

  template <class TT>
  struct InputIteratorConcept
    : AssignableConcept<TT>
    , EqualityComparableConcept<TT>
  {
      // require iterator_traits typedef's
      typedef typename boost::detail::iterator_traits<TT>::difference_type difference_type;
      // Hmm, the following is a bit fragile
      typedef typename boost::detail::iterator_traits<TT>::reference reference;
      typedef typename boost::detail::iterator_traits<TT>::pointer pointer;
      typedef typename boost::detail::iterator_traits<TT>::iterator_category iterator_category;

      ~InputIteratorConcept()
      {
        BOOST_CONCEPT_ASSERT((SignedIntegerConcept<difference_type>));
        BOOST_CONCEPT_ASSERT((ConvertibleConcept<iterator_category, std::input_iterator_tag>));
        
        TT j(i);
        (void)*i;           // require dereference operator
        ++j;                // require preincrement operator
        i++;                // require postincrement operator
      }
   private:
    TT i;
  };

  template <class TT, class ValueT>
  struct OutputIteratorConcept
    : AssignableConcept<TT>
  {
    ~OutputIteratorConcept() {
      
      ++i;                // require preincrement operator
      i++;                // require postincrement operator
      *i++ = t;           // require postincrement and assignment
    }
   private:
    TT i, j;
    ValueT t;
  };

  template <class TT>
  struct ForwardIteratorConcept
    : InputIteratorConcept<TT>
  {
      ~ForwardIteratorConcept()
      {
          BOOST_CONCEPT_ASSERT((ConvertibleConcept<
              BOOST_DEDUCED_TYPENAME ForwardIteratorConcept::iterator_category
            , std::forward_iterator_tag
          >));
          
          typename InputIteratorConcept<TT>::reference r = *i;
          ignore_unused_variable_warning(r);
      }
      
   private:
      TT i;
  };

  template <class TT>
  struct Mutable_ForwardIteratorConcept
    : ForwardIteratorConcept<TT>
  {
      ~Mutable_ForwardIteratorConcept() {
        *i++ = *i;         // require postincrement and assignment
      }
   private:
      TT i;
  };

  template <class TT>
  struct BidirectionalIteratorConcept
    : ForwardIteratorConcept<TT>
  {
      ~BidirectionalIteratorConcept()
      {
          BOOST_CONCEPT_ASSERT((ConvertibleConcept<
              BOOST_DEDUCED_TYPENAME BidirectionalIteratorConcept::iterator_category
            , std::bidirectional_iterator_tag
          >));

          --i;                // require predecrement operator
          i--;                // require postdecrement operator
      }
   private:
      TT i;
  };

  template <class TT>
  struct Mutable_BidirectionalIteratorConcept
    : BidirectionalIteratorConcept<TT>
    , Mutable_ForwardIteratorConcept<TT>
  {
      ~Mutable_BidirectionalIteratorConcept()
      {
          *i-- = *i;                  // require postdecrement and assignment
      }
   private:
      TT i;
  };


  template <class TT>
  struct RandomAccessIteratorConcept
    : BidirectionalIteratorConcept<TT>
    , ComparableConcept<TT>
  {
      ~RandomAccessIteratorConcept()
      {
          BOOST_CONCEPT_ASSERT((ConvertibleConcept<
              BOOST_DEDUCED_TYPENAME BidirectionalIteratorConcept<TT>::iterator_category
            , std::random_access_iterator_tag
          >));

          i += n;             // require assignment addition operator
          i = i + n; i = n + i; // require addition with difference type
          i -= n;             // require assignment subtraction operator
          i = i - n;                  // require subtraction with difference type
          n = i - j;                  // require difference operator
          (void)i[n];                 // require element access operator
      }
      
   private:
    TT a, b;
    TT i, j;
      typename boost::detail::iterator_traits<TT>::difference_type n;
  };

  template <class TT>
  struct Mutable_RandomAccessIteratorConcept
    : RandomAccessIteratorConcept<TT>
    , Mutable_BidirectionalIteratorConcept<TT>
  {
    ~Mutable_RandomAccessIteratorConcept() {
      i[n] = *i;                  // require element access and assignment
    }
   private:
    TT i;
    typename boost::detail::iterator_traits<TT>::difference_type n;
  };

  //===========================================================================
  // Container Concepts

  template <class Container>
  struct ContainerConcept
    : AssignableConcept<Container>
  {
    typedef typename Container::value_type value_type;
    typedef typename Container::difference_type difference_type;
    typedef typename Container::size_type size_type;
    typedef typename Container::const_reference const_reference;
    typedef typename Container::const_pointer const_pointer;
    typedef typename Container::const_iterator const_iterator;

      ~ContainerConcept()
      {
          BOOST_CONCEPT_ASSERT((InputIteratorConcept<const_iterator>));
          const_constraints(c);
      }
      
   private:
      void const_constraints(const Container& cc) {
          i = cc.begin();
          i = cc.end();
          n = cc.size();
          n = cc.max_size();
          b = cc.empty();
      }
      Container c;
      bool b;
      const_iterator i;
      size_type n;
  };

  template <class Container>
  struct Mutable_ContainerConcept
    : ContainerConcept<Container>
  {
      typedef typename Container::reference reference;
      typedef typename Container::iterator iterator;
      typedef typename Container::pointer pointer;
    
      ~Mutable_ContainerConcept()
      {
          BOOST_CONCEPT_ASSERT((
               AssignableConcept<typename Mutable_ContainerConcept::value_type>));
          
          BOOST_CONCEPT_ASSERT((InputIteratorConcept<iterator>));
          
          i = c.begin();
          i = c.end();
          c.swap(c2);
      }
      
   private:
      iterator i;
      Container c, c2;
  };

  template <class ForwardContainer>
  struct ForwardContainerConcept
    : ContainerConcept<ForwardContainer>
  {
      ~ForwardContainerConcept()
      {
          BOOST_CONCEPT_ASSERT((
               ForwardIteratorConcept<
                    typename ForwardContainerConcept::const_iterator
               >));
      }
  };  

  template <class ForwardContainer>
  struct Mutable_ForwardContainerConcept
    : ForwardContainerConcept<ForwardContainer>
    , Mutable_ContainerConcept<ForwardContainer>
  {
      ~Mutable_ForwardContainerConcept()
      {
          BOOST_CONCEPT_ASSERT((
               Mutable_ForwardIteratorConcept<
                   typename Mutable_ForwardContainerConcept::iterator
               >));
      }
  };  

  template <class ReversibleContainer>
  struct ReversibleContainerConcept
    : ForwardContainerConcept<ReversibleContainer>
  {
      typedef typename
        ReversibleContainer::const_reverse_iterator
      const_reverse_iterator;

      ~ReversibleContainerConcept()
      {
          BOOST_CONCEPT_ASSERT((
              BidirectionalIteratorConcept<
                  typename ReversibleContainerConcept::const_iterator>));
          
          BOOST_CONCEPT_ASSERT((BidirectionalIteratorConcept<const_reverse_iterator>));
          
          const_constraints(c);
      }
   private:
      void const_constraints(const ReversibleContainer& cc)
      {
          const_reverse_iterator i = cc.rbegin();
          i = cc.rend();
      }
      ReversibleContainer c;
  };

  template <class ReversibleContainer>
  struct Mutable_ReversibleContainerConcept
    : Mutable_ForwardContainerConcept<ReversibleContainer>
    , ReversibleContainerConcept<ReversibleContainer>
  {
      typedef typename ReversibleContainer::iterator iterator;
      typedef typename ReversibleContainer::reverse_iterator reverse_iterator;

      ~Mutable_ReversibleContainerConcept()
      {
        BOOST_CONCEPT_ASSERT((Mutable_BidirectionalIteratorConcept<iterator>));
        BOOST_CONCEPT_ASSERT((Mutable_BidirectionalIteratorConcept<reverse_iterator>));
        reverse_iterator i = c.rbegin();
        i = c.rend();
      }
   private:  
      ReversibleContainer c;
  };

  template <class RandomAccessContainer>
  struct RandomAccessContainerConcept
    : ReversibleContainerConcept<RandomAccessContainer>
  {
      typedef typename RandomAccessContainer::size_type size_type;
      typedef typename RandomAccessContainer::const_reference const_reference;

      ~RandomAccessContainerConcept()
      {
          BOOST_CONCEPT_ASSERT((
              RandomAccessIteratorConcept<
                  typename RandomAccessContainerConcept::const_iterator
              >));
          
          const_constraints(c);
      }
   private:
      void const_constraints(const RandomAccessContainer& cc)
      {
          const_reference r = cc[n];
          ignore_unused_variable_warning(r);
      }
    
      RandomAccessContainer c;
      size_type n;
  };

  template <class RandomAccessContainer>
  struct Mutable_RandomAccessContainerConcept
    : Mutable_ReversibleContainerConcept<RandomAccessContainer>
    , RandomAccessContainerConcept<RandomAccessContainer>
  {
   private:
      typedef Mutable_RandomAccessContainerConcept self;
   public:
      ~Mutable_RandomAccessContainerConcept()
      {
          BOOST_CONCEPT_ASSERT((Mutable_RandomAccessIteratorConcept<typename self::iterator>));
          BOOST_CONCEPT_ASSERT((Mutable_RandomAccessIteratorConcept<typename self::reverse_iterator>));
          
          typename self::reference r = c[i];
          ignore_unused_variable_warning(r);
      }
      
   private:
      typename Mutable_ReversibleContainerConcept<RandomAccessContainer>::size_type i;
      RandomAccessContainer c;
  };

  // A Sequence is inherently mutable
  template <class Sequence>
  struct SequenceConcept
    : Mutable_ForwardContainerConcept<Sequence>
      // Matt Austern's book puts DefaultConstructible here, the C++
      // standard places it in Container --JGS
      // ... so why aren't we following the standard?  --DWA
    , DefaultConstructibleConcept<Sequence>
  {
      ~SequenceConcept()
      {
          Sequence 
              c(n),
              c2(n, t),
              c3(first, last);

          c.insert(p, t);
          c.insert(p, n, t);
          c.insert(p, first, last);

          c.erase(p);
          c.erase(p, q);

          typename SequenceConcept::reference r = c.front();

          ignore_unused_variable_warning(c);
          ignore_unused_variable_warning(c2);
          ignore_unused_variable_warning(c3);
          ignore_unused_variable_warning(r);
          const_constraints(c);
      }
   private:
      void const_constraints(const Sequence& c) {
          typename SequenceConcept::const_reference r = c.front();
          ignore_unused_variable_warning(r);
      }
    
      typename Sequence::value_type t;
      typename Sequence::size_type n;
      typename Sequence::value_type* first, *last;
      typename Sequence::iterator p, q;
  };

  template <class FrontInsertionSequence>
  struct FrontInsertionSequenceConcept
    : SequenceConcept<FrontInsertionSequence>
  {
      ~FrontInsertionSequenceConcept()
      {
          c.push_front(t);
          c.pop_front();
      }
   private:
      FrontInsertionSequence c;
      typename FrontInsertionSequence::value_type t;
  };

  template <class BackInsertionSequence>
  struct BackInsertionSequenceConcept
    : SequenceConcept<BackInsertionSequence>
  {
      ~BackInsertionSequenceConcept()
      {
          c.push_back(t);
          c.pop_back();
          typename BackInsertionSequenceConcept::reference r = c.back();
          ignore_unused_variable_warning(r);
          const_constraints(c);
      }
   private:
      void const_constraints(const BackInsertionSequence& cc) {
          typename BackInsertionSequenceConcept::const_reference
              r = cc.back();
          ignore_unused_variable_warning(r);
      };
      BackInsertionSequence c;
      typename BackInsertionSequence::value_type t;
  };

  template <class AssociativeContainer>
  struct AssociativeContainerConcept
    : ForwardContainerConcept<AssociativeContainer>
    , DefaultConstructibleConcept<AssociativeContainer>
  {
      typedef typename AssociativeContainer::key_type key_type;
      typedef typename AssociativeContainer::key_compare key_compare;
      typedef typename AssociativeContainer::value_compare value_compare;
      typedef typename AssociativeContainer::iterator iterator;

      ~AssociativeContainerConcept()
      {
          i = c.find(k);
          r = c.equal_range(k);
          c.erase(k);
          c.erase(i);
          c.erase(r.first, r.second);
          const_constraints(c);
          BOOST_CONCEPT_ASSERT((BinaryPredicateConcept<key_compare,key_type,key_type>));
          
          typedef typename AssociativeContainerConcept::value_type value_type_;
          BOOST_CONCEPT_ASSERT((BinaryPredicateConcept<value_compare,value_type_,value_type_>));
      }
      
      // Redundant with the base concept, but it helps below.
      typedef typename AssociativeContainer::const_iterator const_iterator;
   private:
      void const_constraints(const AssociativeContainer& cc)
      {
          ci = cc.find(k);
          n = cc.count(k);
          cr = cc.equal_range(k);
      }

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
    : AssociativeContainerConcept<UniqueAssociativeContainer>
  {
      ~UniqueAssociativeContainerConcept()
      {
          UniqueAssociativeContainer c(first, last);
      
          pos_flag = c.insert(t);
          c.insert(first, last);

          ignore_unused_variable_warning(c);
      }
   private:
      std::pair<typename UniqueAssociativeContainer::iterator, bool> pos_flag;
      typename UniqueAssociativeContainer::value_type t;
      typename UniqueAssociativeContainer::value_type* first, *last;
  };

  template <class MultipleAssociativeContainer>
  struct MultipleAssociativeContainerConcept
    : AssociativeContainerConcept<MultipleAssociativeContainer>
  {
      ~MultipleAssociativeContainerConcept()
      {
          MultipleAssociativeContainer c(first, last);
      
          pos = c.insert(t);
          c.insert(first, last);

          ignore_unused_variable_warning(c);
          ignore_unused_variable_warning(pos);
      }
   private:
      typename MultipleAssociativeContainer::iterator pos;
      typename MultipleAssociativeContainer::value_type t;
      typename MultipleAssociativeContainer::value_type* first, *last;
  };

  template <class SimpleAssociativeContainer>
  struct SimpleAssociativeContainerConcept
    : AssociativeContainerConcept<SimpleAssociativeContainer>
  {
      ~SimpleAssociativeContainerConcept()
      {
          typedef typename SimpleAssociativeContainer::key_type key_type;
          typedef typename SimpleAssociativeContainer::value_type value_type;
          BOOST_MPL_ASSERT((boost::is_same<key_type,value_type>));
      }
  };

  template <class SimpleAssociativeContainer>
  struct PairAssociativeContainerConcept
    : AssociativeContainerConcept<SimpleAssociativeContainer>
  {
      ~PairAssociativeContainerConcept()
      {
          typedef typename SimpleAssociativeContainer::key_type key_type;
          typedef typename SimpleAssociativeContainer::value_type value_type;
          typedef typename SimpleAssociativeContainer::mapped_type mapped_type;
          typedef std::pair<const key_type, mapped_type> required_value_type;
          BOOST_MPL_ASSERT((boost::is_same<value_type,required_value_type>));
      }
  };

  template <class SortedAssociativeContainer>
  struct SortedAssociativeContainerConcept
    : AssociativeContainerConcept<SortedAssociativeContainer>
    , ReversibleContainerConcept<SortedAssociativeContainer>
  {
      ~SortedAssociativeContainerConcept()
      {
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
          const_constraints(c);
      }
      
      void const_constraints(const SortedAssociativeContainer& c)
      {
          kc = c.key_comp();
          vc = c.value_comp();

          cp = c.upper_bound(k);
          cp = c.lower_bound(k);
          cr = c.equal_range(k);
      }
      
   private:
      typename SortedAssociativeContainer::key_compare kc;
      typename SortedAssociativeContainer::value_compare vc;
      typename SortedAssociativeContainer::value_type t;
      typename SortedAssociativeContainer::key_type k;
      typedef typename SortedAssociativeContainer::iterator iterator;
      typedef typename SortedAssociativeContainer::const_iterator const_iterator;

      typedef SortedAssociativeContainerConcept self;
      iterator p;
      const_iterator cp;
      std::pair<typename self::iterator,typename self::iterator> r;
      std::pair<typename self::const_iterator,typename self::const_iterator> cr;
      typename SortedAssociativeContainer::value_type* first, *last;
  };

  // HashedAssociativeContainer

} // namespace boost

#endif // BOOST_CONCEPT_CHECKS_HPP

