// (C) Copyright David Abrahams 2000. Permission to copy, use,
// modify, sell and distribute this software is granted provided this
// copyright notice appears in all copies. This software is provided
// "as is" without express or implied warranty, and with no claim as
// to its suitability for any purpose.
//
// (C) Copyright Jeremy Siek 2000. Permission to copy, use, modify,
// sell and distribute this software is granted provided this
// copyright notice appears in all copies. This software is provided
// "as is" without express or implied warranty, and with no claim as
// to its suitability for any purpose.
//
// Revision History:

// 08 Mar 2001   Jeremy Siek
//      Added support for optional named template parameters.
// 19 Feb 2001   David Abrahams
//      Rolled back reverse_iterator_pair_generator again, as it doesn't
//      save typing on a conforming compiler.
// 18 Feb 2001   David Abrahams
//      Reinstated reverse_iterator_pair_generator
// 16 Feb 2001   David Abrahams
//      Add an implicit conversion operator to operator_arrow_proxy
//      as CW and BCC workarounds.
// 11 Feb 2001   David Abrahams
//      Switch to use of BOOST_STATIC_CONSTANT where possible
// 11 Feb 2001   Jeremy Siek
//      Removed workaround for older MIPSpro compiler. The workaround
//        was preventing the proper functionality of the underlying
//        iterator being carried forward into the iterator adaptor.
//        Also added is_bidirectional enum to avoid EDG compiler error.
// 11 Feb 2001   David Abrahams
//      Borland fixes up the wazoo. It finally works!
// 10 Feb 2001   David Abrahams
//      Removed traits argument from iterator_adaptor<> and switched to
//        explicit trait specification for maximum ease-of-use.
//      Added comments to detail::iterator_defaults<>
//      Began using detail::iterator_defaults<> unconditionally for code clarity
//      Changed uses of `Iterator' to `Base' where non-iterators can be used.
//
// 10 Feb 2001   David Abrahams
//      Rolled in supposed Borland fixes from John Maddock, but not seeing any
//        improvement yet
//      Changed argument order to indirect_ generator, for convenience in the
//        case of input iterators (where Reference must be a value type).
//      Removed derivation of filter_iterator_policies from
//        default_iterator_policies, since the iterator category is likely to be
//        reduced (we don't want to allow illegal operations like decrement).
//      Support for a simpler filter iterator interface.
//
// 09 Feb 2001   David Abrahams
//      Improved interface to indirect_ and reverse_ iterators
//      Rolled back Jeremy's new constructor for now; it was causing
//        problems with counting_iterator_test
//      Attempted fix for Borland
//
// 09 Feb 2001   Jeremy Siek
//      Added iterator constructor to allow const adaptor
//        from non-const adaptee.
//      Changed make_xxx to pass iterators by-value to
//        get arrays converted to pointers.
//      Removed InnerIterator template parameter from
//        indirect_iterator_generator.
//      Rearranged parameters for make_filter_iterator
//
// 07 Feb 2001   Jeremy Siek
//      Removed some const iterator adaptor generators.
//      Added make_xxx_iterator() helper functions for remaining
//        iterator adaptors.
//      Removed some traits template parameters where they
//        where no longer needed thanks to detail::iterator_traits.
//      Moved some of the compile-time logic into enums for
//      EDG compatibility.
//
// 07 Feb 2001  David Abrahams
//      Removed iterator_adaptor_pair_generator and
//        reverse_iterator_pair_generator (more such culling to come)
//      Improved comments
//      Changed all uses of std::iterator_traits as default arguments
//        to boost::detail::iterator_traits for improved utility in
//        non-generic contexts
//      Fixed naming convention of non-template parameter names
//
// 06 Feb 2001   David Abrahams
//      Produce operator-> proxy objects for InputIterators
//      Added static assertions to do some basic concept checks
//      Renamed single-type generators -> xxx_generator
//      Renamed const/nonconst iterator generators -> xxx_pair_generator
//      Added make_transform_iterator(iter, function)
//      The existence of boost::detail::iterator_traits allowed many
//        template arguments to be defaulted. Some arguments had to be
//        moved to accomplish it.
//
// 04 Feb 2001  MWERKS bug workaround, concept checking for proper
//              reference types (David Abrahams)

#ifndef BOOST_ITERATOR_ADAPTOR_DWA053000_HPP_
# define BOOST_ITERATOR_ADAPTOR_DWA053000_HPP_

# include <boost/iterator.hpp>
# include <boost/utility.hpp>
# include <boost/compressed_pair.hpp>
# include <boost/concept_check.hpp>
# include <boost/type.hpp>
# include <boost/static_assert.hpp>
# include <boost/type_traits.hpp>
# include <boost/detail/iterator.hpp>
# include <boost/detail/select_type.hpp>
# include <boost/detail/named_template_params.hpp>

// I was having some problems with VC6. I couldn't tell whether our hack for
// stock GCC was causing problems so I needed an easy way to turn it on and
// off. Now we can test the hack with various compilers and still have an 
// "out" if it doesn't work. -dwa 7/31/00
# if __GNUC__ == 2 && __GNUC_MINOR__ <= 96 && !defined(__STL_USE_NAMESPACES)
#  define BOOST_RELOPS_AMBIGUITY_BUG 1
# endif

namespace boost {

//============================================================================
// Concept checking classes that express the requirements for iterator
// policies and adapted types. These classes are mostly for
// documentation purposes, and are not used in this header file. They
// merely provide a more succinct statement of what is expected of the
// iterator policies.

template <class Policies, class Adapted, class Traits>
struct TrivialIteratorPoliciesConcept
{
  typedef typename Traits::reference Reference;
  void constraints() {
    function_requires< AssignableConcept<Policies> >();
    function_requires< DefaultConstructibleConcept<Policies> >();
    function_requires< AssignableConcept<Adapted> >();
    function_requires< DefaultConstructibleConcept<Adapted> >();

    const_constraints();
  }
  void const_constraints() const {
    Reference r = p.dereference(type<Reference>(), x);
    b = p.equal(x, x);
    ignore_unused_variable_warning(r);
  }
  Policies p;
  Adapted x;
  mutable bool b;
};

// Add InputIteratorPoliciesConcept?

template <class Policies, class Adapted, class Traits>
struct ForwardIteratorPoliciesConcept
{
  typedef typename Traits::iterator_category iterator_category;
  void constraints() {
    function_requires< 
      TrivialIteratorPoliciesConcept<Policies, Adapted, Traits>
      >();

    p.increment(x);
    std::forward_iterator_tag t = iterator_category();
    ignore_unused_variable_warning(t);
  }
  Policies p;
  Adapted x;
  iterator_category category;
};

template <class Policies, class Adapted, class Traits>
struct BidirectionalIteratorPoliciesConcept
{
  typedef typename Traits::iterator_category iterator_category;
  void constraints() {
    function_requires< 
      ForwardIteratorPoliciesConcept<Policies, Adapted, Traits>
      >();

    p.decrement(x);
    std::bidirectional_iterator_tag t = iterator_category();
    ignore_unused_variable_warning(t);
  }
  Policies p;
  Adapted x;
};

template <class Policies, class Adapted, class Traits>
struct RandomAccessIteratorPoliciesConcept
{
  typedef typename Traits::difference_type DifferenceType;
  typedef typename Traits::iterator_category iterator_category;
  void constraints() {
    function_requires< 
      BidirectionalIteratorPoliciesConcept<Policies, Adapted, Traits>
      >();

    p.advance(x, n);
    std::random_access_iterator_tag t = iterator_category();
    const_constraints();
    ignore_unused_variable_warning(t);
  }
  void const_constraints() const {
    n = p.distance(type<DifferenceType>(), x, x);
    b = p.less(x, x);
  }
  Policies p;
  Adapted x;
  mutable DifferenceType n;
  mutable bool b;
};


//============================================================================
// Default policies for iterator adaptors. You can use this as a base
// class if you want to customize particular policies.
struct default_iterator_policies
{
    // Some of these members were defined static, but Borland got confused
    // and thought they were non-const. Also, Sun C++ does not like static
    // function templates.

    template <class Base>
    void initialize(Base&)
        { }

    // The "type<Reference>" parameter is a portable mechanism for
    // the iterator_adaptor class to tell this member function what
    // the Reference type is, which is needed for the return type.
    template <class Reference, class Base>
    Reference dereference(type<Reference>, const Base& x) const
        { return *x; }

    template <class Base>
    void increment(Base& x)
        { ++x; }

    template <class Base>
    void decrement(Base& x)
        { --x; }

    template <class Base, class DifferenceType>
    void advance(Base& x, DifferenceType n)
        { x += n; }

    template <class Difference, class Iterator1, class Iterator2>
    Difference distance(type<Difference>, const Iterator1& x,
                        const Iterator2& y) const
        { return y - x; }

    template <class Iterator1, class Iterator2>
    bool equal(const Iterator1& x, const Iterator2& y) const
        { return x == y; }

    template <class Iterator1, class Iterator2>
    bool less(const Iterator1& x, const Iterator2& y) const
        { return x < y; }
};

// putting the comparisons in a base class avoids the g++ 
// ambiguous overload bug due to the relops operators

#ifdef BOOST_RELOPS_AMBIGUITY_BUG
template <class Derived, class Base>
struct iterator_comparisons : Base { };

template <class D1, class D2, class Base1, class Base2>
inline bool operator==(const iterator_comparisons<D1,Base1>& xb, 
                       const iterator_comparisons<D2,Base2>& yb)
{
        const D1& x = static_cast<const D1&>(xb);
    const D2& y = static_cast<const D2&>(yb);
    return x.policies().equal(x.iter(), y.iter());
}

template <class D1, class D2, class Base1, class Base2>
inline bool operator!=(const iterator_comparisons<D1,Base1>& xb, 
                       const iterator_comparisons<D2,Base2>& yb)
{
    const D1& x = static_cast<const D1&>(xb);
    const D2& y = static_cast<const D2&>(yb);
    return !x.policies().equal(x.iter(), y.iter());
}

template <class D1, class D2, class Base1, class Base2>
inline bool operator<(const iterator_comparisons<D1,Base1>& xb, 
                      const iterator_comparisons<D2,Base2>& yb)
{
    const D1& x = static_cast<const D1&>(xb);
    const D2& y = static_cast<const D2&>(yb);
    return x.policies().less(x.iter(), y.iter());
}

template <class D1, class D2, class Base1, class Base2>
inline bool operator>(const iterator_comparisons<D1,Base1>& xb, 
                      const iterator_comparisons<D2,Base2>& yb)
{ 
    const D1& x = static_cast<const D1&>(xb);
    const D2& y = static_cast<const D2&>(yb);
    return x.policies().less(y.iter(), x.iter());
}

template <class D1, class D2, class Base1, class Base2>
inline bool operator>=(const iterator_comparisons<D1,Base1>& xb, 
                       const iterator_comparisons<D2,Base2>& yb)
{
    const D1& x = static_cast<const D1&>(xb);
    const D2& y = static_cast<const D2&>(yb);
    return !x.policies().less(x.iter(), y.iter());
}

template <class D1, class D2, class Base1, class Base2>
inline bool operator<=(const iterator_comparisons<D1,Base1>& xb, 
                       const iterator_comparisons<D2,Base2>& yb)
{
    const D1& x = static_cast<const D1&>(xb);
    const D2& y = static_cast<const D2&>(yb);
    return !x.policies().less(y.iter(), x.iter());
}
#endif

namespace detail {

  // operator->() needs special support for input iterators to strictly meet the
  // standard's requirements. If *i is not a reference type, we must still
  // produce a (constant) lvalue to which a pointer can be formed. We do that by
  // returning an instantiation of this special proxy class template.

  template <class T>
  struct operator_arrow_proxy
  {
      operator_arrow_proxy(const T& x) : m_value(x) {}
      const T* operator->() const { return &m_value; }
      // This function is needed for MWCW and BCC, which won't call operator->
      // again automatically per 13.3.1.2 para 8
      operator const T*() const { return &m_value; }
      T m_value;
  };

  template <class Iter>
  inline operator_arrow_proxy<typename Iter::value_type>
  operator_arrow(const Iter& i, std::input_iterator_tag) {
      return operator_arrow_proxy<
#ifndef BOOST_MSVC
          typename
#endif
          Iter::value_type>(*i);
  }

  template <class Iter>
  inline typename Iter::pointer
  operator_arrow(const Iter& i, std::forward_iterator_tag) {
    return &(*i);
  }

  template <class Category, class Value, class Pointer>
  struct operator_arrow_result_generator
  {
      typedef operator_arrow_proxy<Value> proxy;
      
      // Borland chokes unless it's an actual enum (!)
      enum { is_input_iter
            = (boost::is_convertible<Category*,std::input_iterator_tag*>::value
               & !boost::is_convertible<Category*,std::forward_iterator_tag*>::value)
      };
      
      typedef typename boost::detail::if_true<(is_input_iter)>::template
      then<
        proxy,
   // else
        Pointer
      >::type type;
  };


# ifdef BOOST_NO_TEMPLATE_PARTIAL_SPECIALIZATION

   // Select default pointer and reference types for adapted non-pointer
   // iterators based on the iterator and the value_type. Poor man's partial
   // specialization is in use here.
   template <bool is_pointer>
   struct iterator_defaults_select
   {
       template <class Iterator,class Value>
       struct traits
       {
           // The assumption is that iterator_traits can deduce these types
           // properly as long as the iterator is not a pointer.
           typedef typename boost::detail::iterator_traits<Iterator>::pointer pointer;
           typedef typename boost::detail::iterator_traits<Iterator>::reference reference;
       };
   };

   // Select default pointer and reference types for adapted pointer iterators
   // given a (possibly-const) value_type.
   template <>
   struct iterator_defaults_select<true>
   {
       template <class Iterator,class Value>
       struct traits
       {
           typedef Value* pointer;
           typedef Value& reference;
       };
   };

   // Consolidate selection of the default pointer and reference type
   template <class Iterator,class Value>
   struct iterator_defaults
   {
       BOOST_STATIC_CONSTANT(bool, is_ptr = boost::is_pointer<Iterator>::value);

       typedef iterator_defaults_select<is_ptr>::template traits<Iterator,Value> traits;
       typedef typename traits::pointer pointer;
       typedef typename traits::reference reference;
   };
# else
   template <class Iterator,class Value>
   struct iterator_defaults : iterator_traits<Iterator>
   {
       // Trying to factor the common is_same expression into an enum or a
       // static bool constant confused Borland.
       typedef typename if_true<(
               ::boost::is_same<Value,typename iterator_traits<Iterator>::value_type>::value
           )>::template then<
                typename iterator_traits<Iterator>::pointer,
                Value*
       >::type pointer;
       
       typedef typename if_true<(
               ::boost::is_same<Value,typename iterator_traits<Iterator>::value_type>::value
           )>::template then<
                typename iterator_traits<Iterator>::reference,
                Value&
       >::type reference;
       
   };
# endif

  //===========================================================================
  // Specify the defaults for iterator_adaptor's template parameters
  
  struct default_value_type {
    template <class Base, class Traits>
    struct bind {
      typedef typename boost::detail::iterator_traits<Base>::value_type type;
    };
  };
  struct default_difference_type {
    template <class Base, class Traits>
    struct bind {
      typedef typename boost::detail::iterator_traits<Base>::difference_type type;
    };
  };
  struct default_iterator_category {
    template <class Base, class Traits>
    struct bind {
      typedef typename boost::detail::iterator_traits<Base>::iterator_category type;
    };
  };
  struct default_pointer {
    template <class Base, class Traits>
    struct bind {
      typedef typename Traits::value_type Value;
      typedef typename boost::detail::iterator_defaults<Base,Value>::pointer 
	type;
    };
  };
  struct default_reference {
    template <class Base, class Traits>
    struct bind {
      typedef typename Traits::value_type Value;
      typedef typename boost::detail::iterator_defaults<Base,Value>::reference 
	type;
    };
  };

  //===========================================================================
  // Support for named template parameters

#if !defined(__BORLANDC__)
  // Borland C++ thinks the nested recursive inheritance here is illegal.

  template <class V = default_argument, 
            class R = default_argument, 
            class P = default_argument,
            class C = default_argument,
            class D = default_argument>
  struct iter_traits_gen : public named_template_param_base {
    template <class T>
    struct value_type : public iter_traits_gen<T,R,P,C,D> { };
    template <class T>
    struct reference : public iter_traits_gen<V,T,P,C,D> { };
    template <class T>
    struct pointer : public iter_traits_gen<V,R,T,C,D> { };
    template <class T>
    struct iterator_category : public iter_traits_gen<V,R,P,T,D>{};
    template <class T>
    struct difference_type : public iter_traits_gen<V,R,P,C,T> { };

    typedef boost::iterator<C, V, D, P, R> traits;
  };
#endif

  BOOST_NAMED_TEMPLATE_PARAM(value_type);
  BOOST_NAMED_TEMPLATE_PARAM(reference);
  BOOST_NAMED_TEMPLATE_PARAM(pointer);
  BOOST_NAMED_TEMPLATE_PARAM(iterator_category);
  BOOST_NAMED_TEMPLATE_PARAM(difference_type);

  template <class Base, class Value, class Reference, class Pointer,
            class Category, class Distance>
  class iterator_adaptor_traits_gen
  {
    typedef boost::iterator<Category, Value, Distance, Pointer, Reference>
      Traits0;

    typedef typename get_value_type<Base, 
        typename boost::remove_const<Value>::type, Traits0
        >::type value_type;
    typedef typename get_difference_type<Base, Distance, Traits0>::type
      difference_type;
    typedef typename get_iterator_category<Base, Category, Traits0>::type
      iterator_category;

    typedef boost::iterator<iterator_category, value_type, difference_type,
      Pointer, Reference> Traits1;
    
    typedef typename get_pointer<Base, Pointer, Traits1>::type pointer;
    typedef typename get_reference<Base, Reference, Traits1>::type reference;
  public:
    typedef boost::iterator<iterator_category, value_type, difference_type,
      pointer, reference> type;
  };
  
} // namespace detail


#if !defined(__BORLANDC__)
struct iterator_traits_generator
  : public detail::iter_traits_gen<> { };
#endif

// This macro definition is only temporary in this file
# if !defined(BOOST_MSVC)
#  define BOOST_ARG_DEPENDENT_TYPENAME typename
# else
#  define BOOST_ARG_DEPENDENT_TYPENAME
# endif

template <class T> struct undefined;

//============================================================================
//iterator_adaptor - Adapts a generic piece of data as an iterator. Adaptation
//      is especially easy if the data being adapted is itself an iterator
//
//   Base - the base (usually iterator) type being wrapped.
//
//   Policies - a set of policies determining how the resulting iterator
//      works.
//
//   Value - if supplied, the value_type of the resulting iterator, unless
//      const. If const, a conforming compiler strips constness for the
//      value_type. If not supplied, iterator_traits<Base>::value_type is used
//
//   Reference - the reference type of the resulting iterator, and in
//      particular, the result type of operator*(). If not supplied but
//      Value is supplied, Value& is used. Otherwise
//      iterator_traits<Base>::reference is used.
//
//   Pointer - the pointer type of the resulting iterator, and in
//      particular, the result type of operator->(). If not
//      supplied but Value is supplied, Value* is used. Otherwise
//      iterator_traits<Base>::pointer is used.
//
//   Category - the iterator_category of the resulting iterator. If not
//      supplied, iterator_traits<Base>::iterator_category is used.
//
//   Distance - the difference_type of the resulting iterator. If not
//      supplied, iterator_traits<Base>::difference_type is used.
template <class Base, class Policies, 
    class Value = detail::default_argument,
    class Reference = BOOST_ARG_DEPENDENT_TYPENAME detail::choose_default_argument<Value>::type,
    class Pointer = BOOST_ARG_DEPENDENT_TYPENAME detail::choose_default_argument<Reference>::type,
    class Category = BOOST_ARG_DEPENDENT_TYPENAME detail::choose_default_argument<Pointer>::type,
    class Distance = BOOST_ARG_DEPENDENT_TYPENAME detail::choose_default_argument<Category>::type
         >
struct iterator_adaptor :
#ifdef BOOST_RELOPS_AMBIGUITY_BUG
    iterator_comparisons<
          iterator_adaptor<Base,Policies,Value,Reference,Pointer,Category,Distance>,
    typename detail::iterator_adaptor_traits_gen<Base,Value,Reference,Pointer,Category, Distance>::type
 >
#else
    detail::iterator_adaptor_traits_gen<Base,Value,Reference,Pointer,Category,Distance>::type
#endif
{
    typedef iterator_adaptor<Base,Policies,Value,Reference,Pointer,Category,Distance> self;
 public:
    typedef typename detail::iterator_adaptor_traits_gen<Base,Value,Reference,Pointer,Category,Distance>::type Traits;

    typedef typename Traits::difference_type difference_type;
    typedef typename Traits::value_type value_type;
    typedef typename Traits::pointer pointer;
    typedef typename Traits::reference reference;
    typedef typename Traits::iterator_category iterator_category;

    typedef Base base_type;
    typedef Policies policies_type;

 private:
    BOOST_STATIC_CONSTANT(bool, is_input_or_output_iter
          = (boost::is_convertible<iterator_category*,std::input_iterator_tag*>::value
             || boost::is_convertible<iterator_category*,std::output_iterator_tag*>::value));

    // Iterators should satisfy one of the known categories
    BOOST_STATIC_ASSERT(is_input_or_output_iter);

    // Iterators >= ForwardIterator must produce real references
    // as required by the C++ standard requirements in Table 74.
    BOOST_STATIC_CONSTANT(bool, forward_iter_with_real_reference =
           (!boost::is_convertible<iterator_category*,std::forward_iterator_tag*>::value
           || boost::is_same<reference,value_type&>::value
           || boost::is_same<reference,const value_type&>::value));
    
#if !defined(BOOST_MSVC)
    // This check gives incorrect results in iter_traits_gen_test.cpp
    BOOST_STATIC_ASSERT(forward_iter_with_real_reference);
#endif

 public:
    iterator_adaptor() { }

    explicit
    iterator_adaptor(const Base& it, const Policies& p = Policies())
        : m_iter_p(it, p) {
      policies().initialize(iter());
    }

    template <class Iter2, class Value2, class Pointer2, class Reference2>
    iterator_adaptor (
        const iterator_adaptor<Iter2,Policies,Value2,Reference2,Pointer2,Category,Distance>& src)
            : m_iter_p(src.iter(), src.policies())
    {
        policies().initialize(iter());
    }

#ifdef BOOST_MSVC
    // This is required to prevent a bug in how VC++ generates
    // the assignment operator for compressed_pair.
    iterator_adaptor& operator= (const iterator_adaptor& x) {
        m_iter_p = x.m_iter_p;
        return *this;
    }
#endif
    reference operator*() const {
        return policies().dereference(type<reference>(), iter());
    }

#ifdef _MSC_VER
# pragma warning(push)
# pragma warning( disable : 4284 )
#endif

    typename boost::detail::operator_arrow_result_generator<iterator_category,value_type,pointer>::type
    operator->() const
        { return detail::operator_arrow(*this, iterator_category()); }

#ifdef _MSC_VER
# pragma warning(pop)
#endif

    value_type operator[](difference_type n) const
        { return *(*this + n); }
    
    self& operator++() {
#ifdef __MWERKS__
        // Odd bug, MWERKS couldn't  deduce the type for the member template
        // Workaround by explicitly specifying the type.
        policies().increment<Base>(iter());
#else
        policies().increment(iter());
#endif
        return *this;
    }

    self operator++(int) { self tmp(*this); ++*this; return tmp; }
    
    self& operator--() {
        policies().decrement(iter());
        return *this;
    }
    
    self operator--(int) { self tmp(*this); --*this; return tmp; }

    self& operator+=(difference_type n) {
        policies().advance(iter(), n);
        return *this;
    }
  
    self& operator-=(difference_type n) {
        policies().advance(iter(), -n);
        return *this;
    }

    base_type base() const { return m_iter_p.first(); }

    // Moved from global scope to avoid ambiguity with the operator-() which
    // subtracts iterators from one another.
    self operator-(difference_type x) const
        { self result(*this); return result -= x; }
private:
    compressed_pair<Base,Policies> m_iter_p;

public: // implementation details (too many compilers have trouble when these are private).
    Policies& policies() { return m_iter_p.second(); }
    const Policies& policies() const { return m_iter_p.second(); }
    
    Base& iter() { return m_iter_p.first(); }
    const Base& iter() const { return m_iter_p.first(); }
};

template <class Base, class Policies, class Value, class Reference, class Pointer,
    class Category, class Distance1, class Distance2>
iterator_adaptor<Base,Policies,Value,Reference,Pointer,Category,Distance1>
operator+(
    iterator_adaptor<Base,Policies,Value,Reference,Pointer,Category,Distance1> p,
    Distance2 x)
{
    return p += x;
}

template <class Base, class Policies, class Value, class Reference, class Pointer,
    class Category, class Distance1, class Distance2>
iterator_adaptor<Base,Policies,Value,Reference,Pointer,Category,Distance1>
operator+(
    Distance2 x,
    iterator_adaptor<Base,Policies,Value,Reference,Pointer,Category,Distance1> p)
{
    return p += x;
}

template <class Iterator1, class Iterator2, class Policies, class Value1, class Value2,
    class Reference1, class Reference2, class Pointer1, class Pointer2, class Category,
    class Distance>
typename iterator_adaptor<Iterator1,Policies,Value1,Reference1,Pointer1,Category,Distance>::difference_type
operator-(
    const iterator_adaptor<Iterator1,Policies,Value1,Reference1,Pointer1,Category,Distance>& x,
    const iterator_adaptor<Iterator2,Policies,Value2,Reference2,Pointer2,Category,Distance>& y)
{
  typedef typename iterator_adaptor<Iterator1,Policies,Value1,Reference1,
    Pointer1,Category,Distance>::difference_type difference_type;
  return x.policies().distance(type<difference_type>(), y.iter(), x.iter());
}

#ifndef BOOST_RELOPS_AMBIGUITY_BUG
template <class Iterator1, class Iterator2, class Policies, class Value1, class Value2,
    class Reference1, class Reference2, class Pointer1, class Pointer2,
    class Category, class Distance>
inline bool 
operator==(
    const iterator_adaptor<Iterator1,Policies,Value1,Reference1,Pointer1,Category,Distance>& x,
    const iterator_adaptor<Iterator2,Policies,Value2,Reference2,Pointer2,Category,Distance>& y)
{
    return x.policies().equal(x.iter(), y.iter());
}

template <class Iterator1, class Iterator2, class Policies, class Value1, class Value2,
    class Reference1, class Reference2, class Pointer1, class Pointer2,
    class Category, class Distance>
inline bool 
operator<(
    const iterator_adaptor<Iterator1,Policies,Value1,Reference1,Pointer1,Category,Distance>& x,
    const iterator_adaptor<Iterator2,Policies,Value2,Reference2,Pointer2,Category,Distance>& y)
{
    return x.policies().less(x.iter(), y.iter());
}

template <class Iterator1, class Iterator2, class Policies, class Value1, class Value2,
    class Reference1, class Reference2, class Pointer1, class Pointer2,
    class Category, class Distance>
inline bool 
operator>(
    const iterator_adaptor<Iterator1,Policies,Value1,Reference1,Pointer1,Category,Distance>& x,
    const iterator_adaptor<Iterator2,Policies,Value2,Reference2,Pointer2,Category,Distance>& y)
{ 
    return x.policies().less(y.iter(), x.iter());
}

template <class Iterator1, class Iterator2, class Policies, class Value1, class Value2,
    class Reference1, class Reference2, class Pointer1, class Pointer2,
    class Category, class Distance>
inline bool 
operator>=(
    const iterator_adaptor<Iterator1,Policies,Value1,Reference1,Pointer1,Category,Distance>& x,
    const iterator_adaptor<Iterator2,Policies,Value2,Reference2,Pointer2,Category,Distance>& y)
{
    return !x.policies().less(x.iter(), y.iter());
}

template <class Iterator1, class Iterator2, class Policies, class Value1, class Value2,
    class Reference1, class Reference2, class Pointer1, class Pointer2,
    class Category, class Distance>
inline bool 
operator<=(
    const iterator_adaptor<Iterator1,Policies,Value1,Reference1,Pointer1,Category,Distance>& x,
    const iterator_adaptor<Iterator2,Policies,Value2,Reference2,Pointer2,Category,Distance>& y)
{
    return !x.policies().less(y.iter(), x.iter());
}

template <class Iterator1, class Iterator2, class Policies, class Value1, class Value2,
    class Reference1, class Reference2, class Pointer1, class Pointer2,
    class Category, class Distance>
inline bool 
operator!=(
    const iterator_adaptor<Iterator1,Policies,Value1,Reference1,Pointer1,Category,Distance>& x, 
    const iterator_adaptor<Iterator2,Policies,Value2,Reference2,Pointer2,Category,Distance>& y)
{
    return !x.policies().equal(x.iter(), y.iter());
}
#endif

//=============================================================================
// Transform Iterator Adaptor
//
// Upon deference, apply some unary function object and return the
// result by value.

template <class AdaptableUnaryFunction>
struct transform_iterator_policies : public default_iterator_policies
{
    transform_iterator_policies() { }
    transform_iterator_policies(const AdaptableUnaryFunction& f) : m_f(f) { }
    
    template <class Reference, class Iterator>
    Reference dereference(type<Reference>, const Iterator& iter) const
        { return m_f(*iter); }

    AdaptableUnaryFunction m_f;
};

template <class AdaptableUnaryFunction, class Iterator>
class transform_iterator_generator
{
    typedef typename AdaptableUnaryFunction::result_type value_type;
public:
    typedef iterator_adaptor<Iterator, 
      transform_iterator_policies<AdaptableUnaryFunction>,
        value_type, value_type, value_type*, std::input_iterator_tag>
      type;
};

template <class AdaptableUnaryFunction, class Iterator>
inline typename transform_iterator_generator<AdaptableUnaryFunction,Iterator>::type
make_transform_iterator(
    Iterator base,
    const AdaptableUnaryFunction& f = AdaptableUnaryFunction())
{
    typedef typename transform_iterator_generator<AdaptableUnaryFunction,Iterator>::type result_t;
    return result_t(base, f);
}

//=============================================================================
// Indirect Iterators Adaptor

// Given a pointer to pointers (or iterator to iterators),
// apply a double dereference inside operator*().
//
// We use the term "outer" to refer to the first level iterator type
// and "inner" to refer to the second level iterator type.  For
// example, given T**, T* is the inner iterator type and T** is the
// outer iterator type. Also, const T* would be the const inner
// iterator.

// We tried to implement this with transform_iterator, but that required
// using boost::remove_ref, which is not compiler portable.

struct indirect_iterator_policies : public default_iterator_policies
{
    template <class Reference, class Iterator>
    Reference dereference(type<Reference>, const Iterator& x) const
        { return **x; }
};

namespace detail {
# if !defined(BOOST_MSVC) // stragely instantiated even when unused! Maybe try a recursive template someday ;-)
  template <class T>
  struct value_type_of_value_type {
      typedef typename boost::detail::iterator_traits<T>::value_type outer_value;
      typedef typename boost::detail::iterator_traits<outer_value>::value_type type;
  };
# endif
}

template <class OuterIterator,      // Mutable or Immutable, does not matter
          class Value
#if !defined(BOOST_MSVC)
                = BOOST_ARG_DEPENDENT_TYPENAME detail::value_type_of_value_type<OuterIterator>::type
#endif
          , class Reference = Value&
          , class Category = BOOST_ARG_DEPENDENT_TYPENAME boost::detail::iterator_traits<OuterIterator>::iterator_category
          , class Pointer = Value*
         >
struct indirect_iterator_generator
{
    typedef iterator_adaptor<OuterIterator,
        indirect_iterator_policies,Value,Reference,Pointer,Category> type;
};

template <class OuterIterator,      // Mutable or Immutable, does not matter
          class Value
#if !defined(BOOST_MSVC)
                = BOOST_ARG_DEPENDENT_TYPENAME detail::value_type_of_value_type<OuterIterator>::type
#endif
          , class Reference = Value&
          , class ConstReference = const Value&
          , class Category = BOOST_ARG_DEPENDENT_TYPENAME boost::detail::iterator_traits<OuterIterator>::iterator_category
          , class Pointer = Value*
          , class ConstPointer = const Value*
           >
struct indirect_iterator_pair_generator
{
  typedef typename indirect_iterator_generator<OuterIterator,
    Value, Reference,Category,Pointer>::type iterator;
  typedef typename indirect_iterator_generator<OuterIterator,
    Value, ConstReference,Category,ConstPointer>::type const_iterator;
};

#ifndef BOOST_MSVC
template <class OuterIterator>
inline typename indirect_iterator_generator<OuterIterator>::type
make_indirect_iterator(OuterIterator base)
{
    typedef typename indirect_iterator_generator
        <OuterIterator>::type result_t;
    return result_t(base);
}
#endif

//=============================================================================
// Reverse Iterators Adaptor

struct reverse_iterator_policies : public default_iterator_policies
{
    template <class Reference, class BidirectionalIterator>
    Reference dereference(type<Reference>, const BidirectionalIterator& x) const
        { return *boost::prior(x); }
    
    template <class BidirectionalIterator>
    void increment(BidirectionalIterator& x) const
        { --x; }
    
    template <class BidirectionalIterator>
    void decrement(BidirectionalIterator& x) const
        { ++x; }
    
    template <class BidirectionalIterator, class DifferenceType>
    void advance(BidirectionalIterator& x, DifferenceType n) const
        { x -= n; }
    
    template <class Difference, class Iterator1, class Iterator2>
    Difference distance(type<Difference>, const Iterator1& x, 
                        const Iterator2& y) const
        { return x - y; }
    
    template <class Iterator1, class Iterator2>
    bool equal(const Iterator1& x, const Iterator2& y) const
        { return x == y; }
    
    template <class Iterator1, class Iterator2>
    bool less(const Iterator1& x, const Iterator2& y) const
        { return y < x; }
};
  
template <class BidirectionalIterator,
    class Value = BOOST_ARG_DEPENDENT_TYPENAME boost::detail::iterator_traits<BidirectionalIterator>::value_type,
    class Reference = BOOST_ARG_DEPENDENT_TYPENAME boost::detail::iterator_defaults<BidirectionalIterator,Value>::reference,
    class Pointer = BOOST_ARG_DEPENDENT_TYPENAME boost::detail::iterator_defaults<BidirectionalIterator,Value>::pointer,
    class Category = BOOST_ARG_DEPENDENT_TYPENAME boost::detail::iterator_traits<BidirectionalIterator>::iterator_category,
    class Distance = BOOST_ARG_DEPENDENT_TYPENAME boost::detail::iterator_traits<BidirectionalIterator>::difference_type
         >
struct reverse_iterator_generator
{
    typedef iterator_adaptor<BidirectionalIterator,reverse_iterator_policies,
        Value,Reference,Pointer,Category,Distance> type;
};

template <class BidirectionalIterator>
inline typename reverse_iterator_generator<BidirectionalIterator>::type
make_reverse_iterator(BidirectionalIterator base)
{
    typedef typename reverse_iterator_generator<BidirectionalIterator>::type result_t;
    return result_t(base);
}

//=============================================================================
// Projection Iterators Adaptor

template <class AdaptableUnaryFunction>
struct projection_iterator_policies : public default_iterator_policies
{
    projection_iterator_policies() { }
    projection_iterator_policies(const AdaptableUnaryFunction& f) : m_f(f) { }

    template <class Reference, class Iterator>
    Reference dereference (type<Reference>, Iterator const& iter) const {
        return m_f(*iter);
    }

    AdaptableUnaryFunction m_f;    
};

template <class AdaptableUnaryFunction, class Iterator>
class projection_iterator_generator {
    typedef typename AdaptableUnaryFunction::result_type value_type;
    typedef projection_iterator_policies<AdaptableUnaryFunction> policies;
public:
    typedef iterator_adaptor<Iterator,policies,value_type> type;
};

template <class AdaptableUnaryFunction, class Iterator>
class const_projection_iterator_generator {
    typedef typename AdaptableUnaryFunction::result_type value_type;
    typedef projection_iterator_policies<AdaptableUnaryFunction> policies;
public:
    typedef iterator_adaptor<Iterator,policies,value_type,const value_type&,const value_type*> type;
};

template <class AdaptableUnaryFunction, class Iterator, class ConstIterator>
struct projection_iterator_pair_generator {
    typedef typename projection_iterator_generator<AdaptableUnaryFunction, Iterator>::type iterator;
    typedef typename const_projection_iterator_generator<AdaptableUnaryFunction, ConstIterator>::type const_iterator;
};


template <class AdaptableUnaryFunction, class Iterator>
inline typename projection_iterator_generator<AdaptableUnaryFunction, Iterator>::type
make_projection_iterator(
    Iterator iter, 
    const AdaptableUnaryFunction& f = AdaptableUnaryFunction())
{
    typedef typename projection_iterator_generator<AdaptableUnaryFunction, Iterator>::type result_t;
    return result_t(iter, f);
}

template <class AdaptableUnaryFunction, class Iterator>
inline typename const_projection_iterator_generator<AdaptableUnaryFunction, Iterator>::type
make_const_projection_iterator(
    Iterator iter, 
    const AdaptableUnaryFunction& f = AdaptableUnaryFunction())
{
    typedef typename const_projection_iterator_generator<AdaptableUnaryFunction, Iterator>::type result_t;
    return result_t(iter, f);
}

//=============================================================================
// Filter Iterator Adaptor

template <class Predicate, class Iterator>
class filter_iterator_policies
{
public:
    filter_iterator_policies() { }

    filter_iterator_policies(const Predicate& p, const Iterator& end) 
        : m_predicate(p), m_end(end) { }

    void initialize(Iterator& x) {
        satisfy_predicate(x);
    }

    // The Iter template argument is neccessary for compatibility with a MWCW
    // bug workaround
    template <class Iter>
    void increment(Iter& x) {
        ++x;
        satisfy_predicate(x);
    }

    template <class Reference, class Iter>
    Reference dereference(type<Reference>, const Iter& x) const
        { return *x; }

    template <class Iterator1, class Iterator2>
    bool equal(const Iterator1& x, const Iterator2& y) const
        { return x == y; }

 private:
    void satisfy_predicate(Iterator& iter);
    Predicate m_predicate;
    Iterator m_end;
};
template <class Predicate, class Iterator>
void filter_iterator_policies<Predicate,Iterator>
::satisfy_predicate(Iterator& iter)
{
    while (m_end != iter && !m_predicate(*iter))
        ++iter;
}



namespace detail {
  // A type generator returning Base if T is derived from Base, and T otherwise.
  template <class Base, class T>
  struct reduce_to_base_class
  {
      typedef typename if_true<(
            ::boost::is_convertible<T*,Base*>::value
          )>::template then<Base,T>::type type;
  };

  // "Steps down" the category of iterators below bidirectional so the category
  // can be used with filter iterators.
  template <class Iterator>
  struct non_bidirectional_category
  {
# if !defined(__MWERKS__) || __MWERKS__ > 0x4000
      typedef typename reduce_to_base_class<
              std::forward_iterator_tag,
                   typename iterator_traits<Iterator>::iterator_category
      >::type type;
   private:
      // For some reason, putting this assertion in filter_iterator_generator fails inexplicably under MSVC
      BOOST_STATIC_CONSTANT(
          bool, is_bidirectional
          = (!boost::is_convertible<type*, std::bidirectional_iterator_tag*>::value));
      BOOST_STATIC_ASSERT(is_bidirectional);
# else
      // is_convertible doesn't work with MWERKS
      typedef typename iterator_traits<Iterator>::iterator_category input_category;
  public:
      typedef typename if_true<(
          boost::is_same<input_category,std::random_access_iterator_tag>::value
          || boost::is_same<input_category,std::bidirectional_iterator_tag>::value
        )>::template then<
          std::forward_iterator_tag,
          input_category
      >::type type;
# endif
  };
}

template <class Predicate, class Iterator, 
    class Value = BOOST_ARG_DEPENDENT_TYPENAME boost::detail::iterator_traits<Iterator>::value_type,
    class Reference = BOOST_ARG_DEPENDENT_TYPENAME boost::detail::iterator_defaults<Iterator,Value>::reference,
    class Pointer = BOOST_ARG_DEPENDENT_TYPENAME boost::detail::iterator_defaults<Iterator,Value>::pointer,
    class Category = BOOST_ARG_DEPENDENT_TYPENAME boost::detail::non_bidirectional_category<Iterator>::type,
    class Distance = BOOST_ARG_DEPENDENT_TYPENAME boost::detail::iterator_traits<Iterator>::difference_type
         >
class filter_iterator_generator {
    BOOST_STATIC_CONSTANT(bool, is_bidirectional
        = (boost::is_convertible<Category*, std::bidirectional_iterator_tag*>::value));
#ifndef BOOST_MSVC // I don't have any idea why this occurs, but it doesn't seem to hurt too badly.
    BOOST_STATIC_ASSERT(!is_bidirectional);
#endif
    typedef filter_iterator_policies<Predicate,Iterator> policies_type;
 public:
    typedef iterator_adaptor<Iterator,policies_type,
        Value,Reference,Pointer,Category,Distance> type;
};

// This keeps MSVC happy; it doesn't like to deduce default template arguments
// for template function return types
namespace detail {
  template <class Predicate, class Iterator>
  struct filter_generator {
    typedef typename boost::filter_iterator_generator<Predicate,Iterator>::type type;
  };
}

template <class Predicate, class Iterator>
inline typename detail::filter_generator<Predicate, Iterator>::type
make_filter_iterator(Iterator first, Iterator last, const Predicate& p = Predicate())
{
  typedef filter_iterator_generator<Predicate, Iterator> Gen;
  typedef filter_iterator_policies<Predicate,Iterator> policies_t;
  typedef typename Gen::type result_t;
  return result_t(first, policies_t(p, last));
}

} // namespace boost
# undef BOOST_ARG_DEPENDENT_TYPENAME


#endif



