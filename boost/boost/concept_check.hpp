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

# include <boost/config.hpp>
# include <boost/iterator.hpp>
# include <boost/type_traits/conversion_traits.hpp>
# include <utility>
# include <boost/type_traits/is_same.hpp>
# include <boost/mpl/assert.hpp>
# include <boost/mpl/identity.hpp>
# include <boost/detail/workaround.hpp>
# include <new>
# include <boost/parameter/aux_/parenthesized_type.hpp>
# include <boost/preprocessor/cat.hpp>
# include <boost/detail/iterator.hpp>

namespace boost
{

/*
  "inline" is used for ignore_unused_variable_warning()
   and function_requires() to make sure there is no
   overhead with g++.
 */

# if !BOOST_WORKAROUND(BOOST_MSVC, BOOST_TESTED_AT(1400)) \
    && !BOOST_WORKAROUND(__BORLANDC__, BOOST_TESTED_AT(0x543))
  namespace concept_checking
  {
    template <class Model>
    void* failed(BOOST_EXPLICIT_TEMPLATE_TYPE(Model))
    { return new ((void*)0) Model; }
    
    template <void*(*)()> struct instantiate;
  }
  
  template <class ModelFn>
  struct concept_check
  {
      typedef typename boost::parameter::aux::unaryfunptr_arg_type<ModelFn>::type model;
      typedef concept_checking::instantiate<concept_checking::failed<model> > type;
      
      enum { instantiate = 1 };
  };

# else 
  namespace concept_checking
  {
    template <class T>
    struct test
    {
        static void inline failed() { new ((void*)0) T; }
    };

    template <class T> inline void instantiate(T const&) {}
  }

  template <class ModelFn>
  struct concept_check
  {
      typedef typename boost::parameter::aux::unaryfunptr_arg_type<ModelFn>::type model;
      
#  if !BOOST_WORKAROUND(BOOST_MSVC, < 1300)
      // This occasionally causes ICE with vc6, and in-class checks
      // don't work with that compiler anyway, and if you want the
      // in-function checks to work you have to use
      // function_requires<>, so disabling it does no harm.
      virtual void failed() { new ((void*)0) model; }
#  endif 
      
      enum { instantiate = 1 };
  };
# endif 
  
  // Usage, in class or function context:
  //
  //     BOOST_CONCEPT_ASSERT((UnaryFunctionConcept<F,bool,int>));
  //
  // This macro works everywhere except vc-6.0 and Borland.  On those
  // compilers it will be innocuous but will never cause a compilation
  // error.  Concept checks at class level seem to be impossible on
  // those compilers.  If you want to see errors at function level,
  // you have to use the old boost_function_requires idiom, which
  // works everywhere.
# define BOOST_CONCEPT_ASSERT( ModelInParens )                      \
  typedef int BOOST_PP_CAT(boost_concept_check,__LINE__)[           \
        ::boost::concept_check< void(*)ModelInParens >::instantiate \
    ]

  //
  // Backward compatibility
  //
  
  template <class Model>
  inline void function_requires(BOOST_EXPLICIT_TEMPLATE_TYPE(Model))
  {
# if BOOST_WORKAROUND(BOOST_MSVC, < 1300) \
    || BOOST_WORKAROUND(__BORLANDC__, BOOST_TESTED_AT(0x543))
      concept_checking::instantiate(&concept_checking::test<Model>::failed);
# else 
      BOOST_CONCEPT_ASSERT((Model));
# endif 
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

  template <class T>
  struct IntegerConcept {
    IntegerConcept() { 
#if !defined BOOST_NO_TEMPLATE_PARTIAL_SPECIALIZATION
      x.error_type_must_be_an_integer_type();
#endif      
    }
   private:
    static T x;
  };
#if !defined BOOST_NO_TEMPLATE_PARTIAL_SPECIALIZATION
  template <> struct IntegerConcept<short> { IntegerConcept() {} };
  template <> struct IntegerConcept<unsigned short> { IntegerConcept() {} };
  template <> struct IntegerConcept<int> { IntegerConcept() {} };
  template <> struct IntegerConcept<unsigned int> { IntegerConcept() {} };
  template <> struct IntegerConcept<long> { IntegerConcept() {} };
  template <> struct IntegerConcept<unsigned long> { IntegerConcept() {} };
  // etc.
#endif      

  template <class T>
  struct SignedIntegerConcept {
    SignedIntegerConcept() { 
#if !defined BOOST_NO_TEMPLATE_PARTIAL_SPECIALIZATION
      x.error_type_must_be_a_signed_integer_type();
#endif      
    }
   private:
    static T x;
  };
#if !defined BOOST_NO_TEMPLATE_PARTIAL_SPECIALIZATION
  template <> struct SignedIntegerConcept<short> { SignedIntegerConcept() {} };
  template <> struct SignedIntegerConcept<int> { SignedIntegerConcept() {} };
  template <> struct SignedIntegerConcept<long> { SignedIntegerConcept() {} };
# if defined(BOOST_HAS_LONG_LONG)
  template <> struct SignedIntegerConcept< ::boost::long_long_type> { SignedIntegerConcept() {} };
# endif
  // etc.
#endif      

  template <class T>
  struct UnsignedIntegerConcept {
    UnsignedIntegerConcept() { 
#if !defined BOOST_NO_TEMPLATE_PARTIAL_SPECIALIZATION
      x.error_type_must_be_an_unsigned_integer_type();
#endif      
    }
   private:
    static T x;
  };
#if !defined BOOST_NO_TEMPLATE_PARTIAL_SPECIALIZATION
  template <> struct UnsignedIntegerConcept<unsigned short>
    { UnsignedIntegerConcept() {} };
  template <> struct UnsignedIntegerConcept<unsigned int>
    { UnsignedIntegerConcept() {} };
  template <> struct UnsignedIntegerConcept<unsigned long>
    { UnsignedIntegerConcept() {} };
  // etc.
#endif      

  //===========================================================================
  // Basic Concepts

  template <class TT>
  struct DefaultConstructibleConcept
  {
    DefaultConstructibleConcept() {
      TT a;               // require default constructor
      ignore_unused_variable_warning(a);
    }
  };

  template <class TT>
  struct AssignableConcept
  {
    AssignableConcept() {
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
    static TT a;
  };

  template <class TT>
  struct CopyConstructibleConcept
  {
    CopyConstructibleConcept() {
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
    static TT b;
  };

  // The SGI STL version of Assignable requires copy constructor and operator=
  template <class TT>
  struct SGIAssignableConcept
  {
    SGIAssignableConcept() {
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
    static TT a;
  };

  template <class X, class Y>
  struct ConvertibleConcept
  {
    ConvertibleConcept() {
      Y y = x;
      ignore_unused_variable_warning(y);
    }
   private:
    static X x;
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
    EqualityComparableConcept() {
      require_boolean_expr(a == b);
      require_boolean_expr(a != b);
    }
   private:
    static TT a, b;
  };

  template <class TT>
  struct LessThanComparableConcept
  {
    LessThanComparableConcept() {
      require_boolean_expr(a < b);
    }
   private:
    static TT a, b;
  };

  // This is equivalent to SGI STL's LessThanComparable.
  template <class TT>
  struct ComparableConcept
  {
    ComparableConcept() {
      require_boolean_expr(a < b);
      require_boolean_expr(a > b);
      require_boolean_expr(a <= b);
      require_boolean_expr(a >= b);
    }
   private:
    static TT a, b;
  };

#define BOOST_DEFINE_BINARY_PREDICATE_OP_CONSTRAINT(OP,NAME)    \
    template <class First, class Second>                        \
    struct NAME {                                               \
        NAME() { (void)constraints_(); }                        \
     private:                                                   \
        bool constraints_() {                                   \
            return  a OP b;                                     \
        }                                                       \
        static First a;                                         \
        static Second b;                                        \
    }

#define BOOST_DEFINE_BINARY_OPERATOR_CONSTRAINT(OP,NAME)    \
    template <class Ret, class First, class Second>         \
    struct NAME {                                           \
        NAME() { (void)constraints_(); }                    \
     private:                                               \
        Ret constraints_() {                                \
            return a OP b;                                  \
        }                                                   \
        static First a;                                     \
        static Second b;                                    \
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
    GeneratorConcept() {
      const Return& r = f();   // require operator() member function
      ignore_unused_variable_warning(r);
    }
   private:
    static Func f;
  };


#if !defined BOOST_NO_TEMPLATE_PARTIAL_SPECIALIZATION
  template <class Func>
  struct GeneratorConcept<Func,void>
  {
    GeneratorConcept() {
      f();              // require operator() member function
    }
   private:
      static Func f;
  };
#endif

  template <class Func, class Return, class Arg>
  struct UnaryFunctionConcept
  {
    UnaryFunctionConcept() {
      r = f(arg); // require operator()
    }
   private:
    static Func f;
    static Arg arg;
    static Return r;
  };

#if !defined BOOST_NO_TEMPLATE_PARTIAL_SPECIALIZATION
  template <class Func, class Arg>
  struct UnaryFunctionConcept<Func, void, Arg> {
    UnaryFunctionConcept() { 
      f(arg);                 // require operator()
    }
   private:
    static Func f;
    static Arg arg;
  };
#endif

  template <class Func, class Return, class First, class Second>
  struct BinaryFunctionConcept
  {
    BinaryFunctionConcept() { 
      r = f(first, second); // require operator()
    }
   private:
    static Func f;
    static First first;
    static Second second;
    static Return r;
  };

#if !defined BOOST_NO_TEMPLATE_PARTIAL_SPECIALIZATION
  template <class Func, class First, class Second>
  struct BinaryFunctionConcept<Func, void, First, Second>
  {
    BinaryFunctionConcept() {
      f(first, second); // require operator()
    }
   private:
    static Func f;
    static First first;
    static Second second;
  };
#endif

  template <class Func, class Arg>
  struct UnaryPredicateConcept
  {
    UnaryPredicateConcept() {
      require_boolean_expr(f(arg)); // require operator() returning bool
    }
   private:
    static Func f;
    static Arg arg;
  };

  template <class Func, class First, class Second>
  struct BinaryPredicateConcept
  {
    BinaryPredicateConcept() {
      require_boolean_expr(f(a, b)); // require operator() returning bool
    }
   private:
    static Func f;
    static First a;
    static Second b;
  };

  // use this when functor is used inside a container class like std::set
  template <class Func, class First, class Second>
  struct Const_BinaryPredicateConcept
    : BinaryPredicateConcept<Func, First, Second>
  {
    Const_BinaryPredicateConcept() { 
      const_constraints(f);
    }
   private:
    void const_constraints(const Func& fun) {
      // operator() must be a const member function
      require_boolean_expr(fun(a, b));
    }
    static Func f;
    static First a;
    static Second b;
  };

  template <class Func, class Return>
  struct AdaptableGeneratorConcept
    : GeneratorConcept<Func, typename Func::result_type>
  {
      typedef typename Func::result_type result_type;
      
      AdaptableGeneratorConcept()
      {
          BOOST_MPL_ASSERT((is_convertible<result_type, Return>));
      }
  };

  template <class Func, class Return, class Arg>
  struct AdaptableUnaryFunctionConcept
    : UnaryFunctionConcept<Func, typename Func::result_type, typename Func::argument_type>
  {
      typedef typename Func::argument_type argument_type;
      typedef typename Func::result_type result_type;
      
      AdaptableUnaryFunctionConcept()
      {
          BOOST_MPL_ASSERT((is_convertible<result_type, Return>));
          BOOST_MPL_ASSERT((is_convertible<Arg, argument_type>));
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
      
      AdaptableBinaryFunctionConcept()
      {
          BOOST_MPL_ASSERT((is_convertible<result_type, Return>));
          BOOST_MPL_ASSERT((is_convertible<First, first_argument_type>));
          BOOST_MPL_ASSERT((is_convertible<Second, second_argument_type>));
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

      InputIteratorConcept()
      {
        SignedIntegerConcept<difference_type>();
        ConvertibleConcept<iterator_category, std::input_iterator_tag>();
        
        TT j(i);
        (void)*i;           // require dereference operator
        ++j;                // require preincrement operator
        i++;                // require postincrement operator
      }
   private:
    static TT i;
  };

  template <class TT, class ValueT>
  struct OutputIteratorConcept
    : AssignableConcept<TT>
  {
    OutputIteratorConcept() {
      
      ++i;                // require preincrement operator
      i++;                // require postincrement operator
      *i++ = t;           // require postincrement and assignment
    }
   private:
    static TT i, j;
    static ValueT t;
  };

  template <class TT>
  struct ForwardIteratorConcept
    : InputIteratorConcept<TT>
  {
      ForwardIteratorConcept()
      {
          ConvertibleConcept<
              BOOST_DEDUCED_TYPENAME ForwardIteratorConcept::iterator_category
            , std::forward_iterator_tag
          >();
          
          typename InputIteratorConcept<TT>::reference r = *i;
          ignore_unused_variable_warning(r);
      }
      
   private:
      static TT i;
  };

  template <class TT>
  struct Mutable_ForwardIteratorConcept
    : ForwardIteratorConcept<TT>
  {
      Mutable_ForwardIteratorConcept() {
        *i++ = *i;         // require postincrement and assignment
      }
   private:
      static TT i;
  };

  template <class TT>
  struct BidirectionalIteratorConcept
    : ForwardIteratorConcept<TT>
  {
      BidirectionalIteratorConcept()
      {
          ConvertibleConcept<
              BOOST_DEDUCED_TYPENAME BidirectionalIteratorConcept::iterator_category
            , std::bidirectional_iterator_tag
          >();

          --i;                // require predecrement operator
          i--;                // require postdecrement operator
      }
   private:
      static TT i;
  };

  template <class TT>
  struct Mutable_BidirectionalIteratorConcept
    : BidirectionalIteratorConcept<TT>
    , Mutable_ForwardIteratorConcept<TT>
  {
      Mutable_BidirectionalIteratorConcept()
      {
          *i-- = *i;                  // require postdecrement and assignment
      }
   private:
      static TT i;
  };


  template <class TT>
  struct RandomAccessIteratorConcept
    : BidirectionalIteratorConcept<TT>
    , ComparableConcept<TT>
  {
      RandomAccessIteratorConcept()
      {
          ConvertibleConcept<
              BOOST_DEDUCED_TYPENAME BidirectionalIteratorConcept<TT>::iterator_category
            , std::random_access_iterator_tag
          >();

          i += n;             // require assignment addition operator
          i = i + n; i = n + i; // require addition with difference type
          i -= n;             // require assignment subtraction operator
          i = i - n;                  // require subtraction with difference type
          n = i - j;                  // require difference operator
          (void)i[n];                 // require element access operator
      }
      
   private:
    static TT a, b;
    static TT i, j;
      typename boost::detail::iterator_traits<TT>::difference_type n;
  };

  template <class TT>
  struct Mutable_RandomAccessIteratorConcept
    : RandomAccessIteratorConcept<TT>
    , Mutable_BidirectionalIteratorConcept<TT>
  {
    Mutable_RandomAccessIteratorConcept() {
      i[n] = *i;                  // require element access and assignment
    }
   private:
    static TT i;
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

      ContainerConcept()
      {
          InputIteratorConcept<const_iterator>();
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
      static Container c;
      static bool b;
      static const_iterator i;
      static size_type n;
  };

  template <class Container>
  struct Mutable_ContainerConcept
    : ContainerConcept<Container>
  {
      typedef typename Container::reference reference;
      typedef typename Container::iterator iterator;
      typedef typename Container::pointer pointer;
    
      Mutable_ContainerConcept()
      {
          AssignableConcept<typename Mutable_ContainerConcept::value_type>();
          InputIteratorConcept<iterator>();
          
          i = c.begin();
          i = c.end();
          c.swap(c2);
      }
      
   private:
      static iterator i;
      static Container c, c2;
  };

  template <class ForwardContainer>
  struct ForwardContainerConcept
    : ContainerConcept<ForwardContainer>
  {
      ForwardContainerConcept()
      {
          ForwardIteratorConcept<typename ForwardContainerConcept::const_iterator>();
      }
  };  

  template <class ForwardContainer>
  struct Mutable_ForwardContainerConcept
    : ForwardContainerConcept<ForwardContainer>
    , Mutable_ContainerConcept<ForwardContainer>
  {
      Mutable_ForwardContainerConcept()
      {
          Mutable_ForwardIteratorConcept<
             typename Mutable_ForwardContainerConcept::iterator
          >();
      }
  };  

  template <class ReversibleContainer>
  struct ReversibleContainerConcept
    : ForwardContainerConcept<ReversibleContainer>
  {
      typedef typename
        ReversibleContainer::const_reverse_iterator
      const_reverse_iterator;

      ReversibleContainerConcept()
      {
          BidirectionalIteratorConcept<typename ReversibleContainerConcept::const_iterator>();
          BidirectionalIteratorConcept<const_reverse_iterator>();
          const_constraints(c);
      }
   private:
      void const_constraints(const ReversibleContainer& cc)
      {
          const_reverse_iterator i = cc.rbegin();
          i = cc.rend();
      }
      static ReversibleContainer c;
  };

  template <class ReversibleContainer>
  struct Mutable_ReversibleContainerConcept
    : Mutable_ForwardContainerConcept<ReversibleContainer>
    , ReversibleContainerConcept<ReversibleContainer>
  {
      typedef typename ReversibleContainer::iterator iterator;
      typedef typename ReversibleContainer::reverse_iterator reverse_iterator;

      Mutable_ReversibleContainerConcept()
      {
        Mutable_BidirectionalIteratorConcept<iterator>();
        Mutable_BidirectionalIteratorConcept<reverse_iterator>();
        reverse_iterator i = c.rbegin();
        i = c.rend();
      }
   private:  
      static ReversibleContainer c;
  };

  template <class RandomAccessContainer>
  struct RandomAccessContainerConcept
    : ReversibleContainerConcept<RandomAccessContainer>
  {
      typedef typename RandomAccessContainer::size_type size_type;
      typedef typename RandomAccessContainer::const_reference const_reference;

      RandomAccessContainerConcept()
      {
          RandomAccessIteratorConcept<
            typename RandomAccessContainerConcept::const_iterator
          >();
          
          const_constraints(c);
      }
   private:
      void const_constraints(const RandomAccessContainer& cc)
      {
          const_reference r = cc[n];
          ignore_unused_variable_warning(r);
      }
    
      static RandomAccessContainer c;
      static size_type n;
  };

  template <class RandomAccessContainer>
  struct Mutable_RandomAccessContainerConcept
    : Mutable_ReversibleContainerConcept<RandomAccessContainer>
    , RandomAccessContainerConcept<RandomAccessContainer>
  {
   private:
      typedef Mutable_RandomAccessContainerConcept self;
   public:
      Mutable_RandomAccessContainerConcept()
      {
          Mutable_RandomAccessIteratorConcept<typename self::iterator>();
          Mutable_RandomAccessIteratorConcept<typename self::reverse_iterator>();
          
          typename self::reference r = c[i];
          ignore_unused_variable_warning(r);
      }
      
   private:
      static typename Mutable_ReversibleContainerConcept<RandomAccessContainer>::size_type i;
      static RandomAccessContainer c;
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
      SequenceConcept()
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
    
      static typename Sequence::value_type t;
      static typename Sequence::size_type n;
      static typename Sequence::value_type* first, *last;
      static typename Sequence::iterator p, q;
  };

  template <class FrontInsertionSequence>
  struct FrontInsertionSequenceConcept
    : SequenceConcept<FrontInsertionSequence>
  {
      FrontInsertionSequenceConcept()
      {
          c.push_front(t);
          c.pop_front();
      }
   private:
      static FrontInsertionSequence c;
      static typename FrontInsertionSequence::value_type t;
  };

  template <class BackInsertionSequence>
  struct BackInsertionSequenceConcept
    : SequenceConcept<BackInsertionSequence>
  {
      BackInsertionSequenceConcept()
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
      static BackInsertionSequence c;
      static typename BackInsertionSequence::value_type t;
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

      AssociativeContainerConcept()
      {
          i = c.find(k);
          r = c.equal_range(k);
          c.erase(k);
          c.erase(i);
          c.erase(r.first, r.second);
          const_constraints(c);
          BinaryPredicateConcept<key_compare,key_type,key_type>();
          
          typedef typename AssociativeContainerConcept::value_type value_type;
          BinaryPredicateConcept<value_compare,value_type,value_type>();
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

      static AssociativeContainer c;
      static iterator i;
      static std::pair<iterator,iterator> r;
      static const_iterator ci;
      static std::pair<const_iterator,const_iterator> cr;
      static typename AssociativeContainer::key_type k;
      static typename AssociativeContainer::size_type n;
  };

  template <class UniqueAssociativeContainer>
  struct UniqueAssociativeContainerConcept
    : AssociativeContainerConcept<UniqueAssociativeContainer>
  {
      UniqueAssociativeContainerConcept()
      {
          UniqueAssociativeContainer c(first, last);
      
          pos_flag = c.insert(t);
          c.insert(first, last);

          ignore_unused_variable_warning(c);
      }
   private:
      static std::pair<typename UniqueAssociativeContainer::iterator, bool> pos_flag;
      static typename UniqueAssociativeContainer::value_type t;
      static typename UniqueAssociativeContainer::value_type* first, *last;
  };

  template <class MultipleAssociativeContainer>
  struct MultipleAssociativeContainerConcept
    : AssociativeContainerConcept<MultipleAssociativeContainer>
  {
      MultipleAssociativeContainerConcept()
      {
          MultipleAssociativeContainer c(first, last);
      
          pos = c.insert(t);
          c.insert(first, last);

          ignore_unused_variable_warning(c);
          ignore_unused_variable_warning(pos);
      }
   private:
      static typename MultipleAssociativeContainer::iterator pos;
      static typename MultipleAssociativeContainer::value_type t;
      static typename MultipleAssociativeContainer::value_type* first, *last;
  };

  template <class SimpleAssociativeContainer>
  struct SimpleAssociativeContainerConcept
    : AssociativeContainerConcept<SimpleAssociativeContainer>
  {
      SimpleAssociativeContainerConcept()
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
      PairAssociativeContainerConcept()
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
      SortedAssociativeContainerConcept()
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
      static typename SortedAssociativeContainer::key_compare kc;
      static typename SortedAssociativeContainer::value_compare vc;
      static typename SortedAssociativeContainer::value_type t;
      static typename SortedAssociativeContainer::key_type k;
      typedef typename SortedAssociativeContainer::iterator iterator;
      typedef typename SortedAssociativeContainer::const_iterator const_iterator;

      typedef SortedAssociativeContainerConcept self;
      static iterator p;
      static const_iterator cp;
      static std::pair<typename self::iterator,typename self::iterator> r;
      static std::pair<typename self::const_iterator,typename self::const_iterator> cr;
      static typename SortedAssociativeContainer::value_type* first, *last;
  };

  // HashedAssociativeContainer

} // namespace boost

#endif // BOOST_CONCEPT_CHECKS_HPP

