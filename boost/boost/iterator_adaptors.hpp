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

// 09 Feb 2001   David Abrahams
//      Improved interface to indirect_ and reverse_ iterators
//
//      Rolled back Jeremy's new constructor for now; it was causing
//      problems with counting_iterator_test
//
//      Attempted fix for Borland
//
// 09 Feb 2001   Jeremy Siek
//      Added iterator constructor to allow const adaptor
//      from non-const adaptee.
//
//      Changed make_xxx to pass iterators by-value to
//      get arrays converted to pointers.
//
//      Removed InnerIterator template parameter from
//      indirect_iterator_generator.
//
//      Rearranged parameters for make_filter_iterator
//
// 07 Feb 2001   Jeremy Siek
//      Removed some const iterator adaptor generators.
//
//      Added make_xxx_iterator() helper functions for remaining
//      iterator adaptors.
//
//      Removed some traits template parameters where they
//      where no longer needed thanks to detail::iterator_traits.
//
//      Moved some of the compile-time logic into enums for
//      EDG compatibility.
//
// 07 Feb 2001  David Abrahams
//      Removed iterator_adaptor_pair_generator and
//      reverse_iterator_pair_generator (more such culling to come)
//
//      Improved comments
//
//      Changed all uses of std::iterator_traits as default arguments
//      to boost::detail::iterator_traits for improved utility in
//      non-generic contexts
//
//      Fixed naming convention of non-template parameter names
//
// 06 Feb 2001   David Abrahams
//      Produce operator-> proxy objects for InputIterators
//
//      Added static assertions to do some basic concept checks
//
//      Renamed single-type generators -> xxx_generator
//      Renamed const/nonconst iterator generators -> xxx_pair_generator
//
//      Added make_transform_iterator(iter, function)
//                
//      The existence of boost::detail::iterator_traits allowed many
//      template arguments to be defaulted. Some arguments had to be
//      moved to accomplish it.
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

    template <class Iterator>
    void initialize(Iterator&)
        { }

    template <class Reference, class Iterator>
    Reference dereference(type<Reference>, const Iterator& x) const
        { return *x; }

    template <class Iterator>
    void increment(Iterator& x)
        { ++x; }

    template <class Iterator>
    void decrement(Iterator& x)
        { --x; }

    template <class Iterator, class DifferenceType>
    void advance(Iterator& x, DifferenceType n)
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

//============================================================================
// Some compilers (SGI MIPSpro 7.1.3.3) instantiate/compile member functions
// whether or not they are used. The following functions make sure that
// when the base iterators do not support particular operators, those
// operators do not get used.

namespace detail {

#if defined(__sgi) && !defined(__GNUC__)
  // Dummy versions for iterators that don't support various operators
  template <class Iter>
  inline typename Iter::pointer
  operator_arrow(const Iter&, std::output_iterator_tag) {
    return typename Iter::pointer();
  }

  template <class Iter, class Diff>
  inline void advance_impl(Iter&, Diff, std::input_iterator_tag) { }
  template <class Iter, class Diff>
  inline void advance_impl(Iter&, Diff, std::output_iterator_tag) { }

  template <class Iter>
  inline void decrement_impl(Iter&, std::input_iterator_tag) { }
  template <class Iter>
  inline void decrement_impl(Iter&, std::output_iterator_tag) { }
#endif

  // Real versions

  // operator->() needs special support for input iterators to strictly meet the
  // standard's requirements. If *i is not a reference type, we must still
  // produce a (constant) lvalue to which a pointer can be formed. We do that by
  // returning an instantiation of this special proxy class template.

  template <class T>
  struct operator_arrow_proxy
  {
      operator_arrow_proxy(const T& x) : m_value(x) {}
      const T* operator->() const { return &m_value; }
      T m_value;
  };

  template <class Iter>
  inline operator_arrow_proxy<typename Iter::value_type>
  operator_arrow(const Iter& i, std::input_iterator_tag) {
      return operator_arrow_proxy<typename Iter::value_type>(*i);
  }

  template <class Iter>
  inline typename Iter::pointer
  operator_arrow(const Iter& i, std::forward_iterator_tag) {
    return &(*i);
  }

  template <class Traits>
  struct operator_arrow_result_generator
  {
      typedef typename Traits::iterator_category category;
      typedef operator_arrow_proxy<typename Traits::value_type> proxy;
      typedef typename Traits::pointer pointer;
      
      enum { is_input_iter = boost::is_convertible<category,std::input_iterator_tag>::value
             & !boost::is_convertible<category,std::forward_iterator_tag>::value };
      
      typedef typename boost::detail::if_true<(is_input_iter)>::template
      then<
        proxy,
   // else
        pointer
      >::type type;
  };

  template <class Iter, class Diff>
  inline void
  advance_impl(Iter& i, Diff n, std::random_access_iterator_tag) {
        i.policies().advance(i.iter(), n);
  }

  template <class Iter>
  inline void
  decrement_impl(Iter& i, std::bidirectional_iterator_tag) {
        i.policies().decrement(i.iter());
  }

} // namespace detail

//============================================================================
//iterator_adaptor - Adapts a generic piece of data as an iterator. Adaptation
//      is especially easy if the data being adapted is itself an iterator
//
//   Iterator - the iterator type being wrapped.
//
//   Policies - a set of policies determining how the resulting iterator
//      works.
//
//   Traits - a class satisfying the same requirements as a specialization of
//      std::iterator_traits for the resulting iterator.
//
template <class Iterator, class Policies, 
          class Traits = boost::detail::iterator_traits<Iterator>
         >
struct iterator_adaptor :
#ifdef BOOST_RELOPS_AMBIGUITY_BUG
    iterator_comparisons<
          iterator_adaptor<Iterator,Policies,Traits>,
#endif
          boost::iterator<typename Traits::iterator_category, 
              typename Traits::value_type, typename Traits::difference_type,
              typename Traits::pointer, typename Traits::reference>
#ifdef BOOST_RELOPS_AMBIGUITY_BUG
>
#endif
{
    typedef iterator_adaptor<Iterator, Policies, Traits> Self;
public:
    typedef typename Traits::difference_type difference_type;
    typedef typename Traits::value_type value_type;
    typedef typename Traits::pointer pointer;
    typedef typename Traits::reference reference;
    typedef typename Traits::iterator_category iterator_category;
    typedef Iterator iterator_type;

    enum { is_input_or_output_iter = 
           boost::is_convertible<iterator_category*,std::input_iterator_tag*>::value
           || boost::is_convertible<iterator_category*,std::output_iterator_tag*>::value };

    // Iterators should satisfy one of the known categories
    BOOST_STATIC_ASSERT(is_input_or_output_iter);

    // Iterators >= ForwardIterator must produce real references.
    enum { forward_iter_with_real_reference =
           (!boost::is_convertible<iterator_category,std::forward_iterator_tag>::value
           || boost::is_same<reference,value_type&>::value
           || boost::is_same<reference,const value_type&>::value) };
    BOOST_STATIC_ASSERT(forward_iter_with_real_reference);

    iterator_adaptor() { }

    iterator_adaptor(const Iterator& it, const Policies& p = Policies())
        : m_iter_p(it, p) {
      policies().initialize(iter());
    }

#if 0 // ndef BOOST_MSVC
    // To allow construction of const adaptor from non-const adaptee.
    // However, when this is defined MSVC gives ambiguous error.
    template <class OtherIterator>
    iterator_adaptor(const OtherIterator& it, const Policies& p = Policies())
        : m_iter_p(it, p) {
      policies().initialize(iter());
    }
#endif

    template <class OtherIter, class OtherTraits>
    iterator_adaptor (const iterator_adaptor<OtherIter, Policies,
            OtherTraits>& src)
            : m_iter_p(src.iter(), src.policies()) {
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

    typename boost::detail::operator_arrow_result_generator<Traits>::type
    operator->() const
        { return detail::operator_arrow(*this, iterator_category()); }

#ifdef _MSC_VER
# pragma warning(pop)
#endif

    value_type operator[](difference_type n) const
        { return *(*this + n); }
    
    Self& operator++() {
#ifdef __MWERKS__
        // Odd bug, MWERKS couldn't  deduce the type for the member template
        // Workaround by explicitly specifying the type.
        policies().increment<Iterator>(iter());
#else
        policies().increment(iter());
#endif
        return *this;
    }

    Self operator++(int) { Self tmp(*this); ++*this; return tmp; }
    
    Self& operator--() {
        detail::decrement_impl(*this, iterator_category());
        return *this;
    }
    
    Self operator--(int) { Self tmp(*this); --*this; return tmp; }

    Self& operator+=(difference_type n) {
        detail::advance_impl(*this, n, iterator_category());
        return *this;
    }
  
    Self& operator-=(difference_type n) {
        detail::advance_impl(*this, -n, iterator_category());
        return *this;
    }

    iterator_type base() const { return m_iter_p.first(); }

private:
    typedef Policies policies_type;
    compressed_pair<Iterator,Policies> m_iter_p;
public: // too many compilers have trouble when these are private.
    Policies& policies() { return m_iter_p.second(); }
    const Policies& policies() const { return m_iter_p.second(); }
    Iterator& iter() { return m_iter_p.first(); }
    const Iterator& iter() const { return m_iter_p.first(); }
};


template <class Iterator, class Policies, class Traits>
iterator_adaptor<Iterator,Policies,Traits>
operator-(iterator_adaptor<Iterator,Policies,Traits> p, const typename Traits::difference_type x)
{
    return p -= x;
}

template <class Iterator, class Policies, class Traits>
iterator_adaptor<Iterator,Policies,Traits>
operator+(iterator_adaptor<Iterator,Policies,Traits> p, typename Traits::difference_type x)
{
    return p += x;
}

template <class Iterator, class Policies, class Traits>
iterator_adaptor<Iterator,Policies,Traits>
operator+(typename Traits::difference_type x, iterator_adaptor<Iterator,Policies,Traits> p)
{
    return p += x;
}

template <class Iterator1, class Iterator2, class Policies, class Traits1, class Traits2>
typename Traits1::difference_type operator-(
    const iterator_adaptor<Iterator1,Policies,Traits1>& x,
    const iterator_adaptor<Iterator2,Policies,Traits2>& y )
{
    typedef typename Traits1::difference_type difference_type;
    return x.policies().distance(type<difference_type>(), y.iter(), x.iter());
}

#ifndef BOOST_RELOPS_AMBIGUITY_BUG
template <class Iterator1, class Iterator2, class Policies, class Traits1, class Traits2>
inline bool 
operator==(const iterator_adaptor<Iterator1,Policies,Traits1>& x, const iterator_adaptor<Iterator2,Policies,Traits2>& y) {
    return x.policies().equal(x.iter(), y.iter());
}

template <class Iterator1, class Iterator2, class Policies, class Traits1, class Traits2>
inline bool 
operator<(const iterator_adaptor<Iterator1,Policies,Traits1>& x, const iterator_adaptor<Iterator2,Policies,Traits2>& y) {
    return x.policies().less(x.iter(), y.iter());
}

template <class Iterator1, class Iterator2, class Policies, class Traits1, class Traits2>
inline bool 
operator>(const iterator_adaptor<Iterator1,Policies,Traits1>& x,
          const iterator_adaptor<Iterator2,Policies,Traits2>& y) { 
    return x.policies().less(y.iter(), x.iter());
}

template <class Iterator1, class Iterator2, class Policies, class Traits1, class Traits2>
inline bool 
operator>=(const iterator_adaptor<Iterator1,Policies,Traits1>& x, const iterator_adaptor<Iterator2,Policies,Traits2>& y) {
    return !x.policies().less(x.iter(), y.iter());
}

template <class Iterator1, class Iterator2, class Policies, class Traits1, class Traits2>
inline bool 
operator<=(const iterator_adaptor<Iterator1,Policies,Traits1>& x,
           const iterator_adaptor<Iterator2,Policies,Traits2>& y) {
    return !x.policies().less(y.iter(), x.iter());
}

template <class Iterator1, class Iterator2, class Policies, class Traits1, class Traits2>
inline bool 
operator!=(const iterator_adaptor<Iterator1,Policies,Traits1>& x, 
           const iterator_adaptor<Iterator2,Policies,Traits2>& y) {
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
    typedef typename boost::detail::iterator_traits<Iterator>::difference_type
      difference_type;
    typedef typename AdaptableUnaryFunction::result_type value_type;
public:
    typedef boost::iterator<std::input_iterator_tag, 
      value_type, difference_type, value_type*, value_type> transform_traits;
    typedef iterator_adaptor<Iterator, 
      transform_iterator_policies<AdaptableUnaryFunction>, transform_traits>
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

// This macro definition is only temporary in this file
# if !defined(BOOST_MSVC)
#  define BOOST_ARG_DEPENDENT_TYPENAME typename
# else
#  define BOOST_ARG_DEPENDENT_TYPENAME
# endif

} template <class T> struct undefined; namespace boost {

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
          , class Pointer = Value*
          , class Reference = Value&
         >
class indirect_iterator_generator
{
    typedef boost::detail::iterator_traits<OuterIterator> outer_traits;
    typedef typename outer_traits::difference_type difference_type;
    typedef typename outer_traits::iterator_category iterator_category;

    typedef typename boost::remove_const<Value>::type value_type;
    typedef Pointer pointer;
    typedef Reference reference;
public:
    typedef boost::iterator<iterator_category, value_type, difference_type, pointer, reference> indirect_traits;
    typedef iterator_adaptor<OuterIterator, indirect_iterator_policies, indirect_traits> type;
};

template <class OuterIterator,      // Mutable or Immutable, does not matter
          class Value
#if !defined(BOOST_MSVC)
                = BOOST_ARG_DEPENDENT_TYPENAME detail::value_type_of_value_type<OuterIterator>::type
#endif
          , class Pointer = Value*
          , class Reference = Value&
          , class ConstPointer = const Value*
          , class ConstReference = const Value&
           >
struct indirect_iterator_pair_generator
{
  typedef typename indirect_iterator_generator<OuterIterator,
    Value, Pointer, Reference>::type iterator;
  typedef typename indirect_iterator_generator<OuterIterator,
    Value, ConstPointer, ConstReference>::type const_iterator;
};

// Tried to allow InnerTraits to be provided by explicit template
// argument to the function, but could not get it to work. -Jeremy Siek
template <class Value, class OuterIterator>
inline typename indirect_iterator_generator<OuterIterator,Value>::type
make_indirect_iterator(OuterIterator base, Value* = 0)
{
    typedef typename indirect_iterator_generator
        <OuterIterator, Value>::type result_t;
    return result_t(base);
}

# if 0 // This just doesn't seem to work under any circumstances!
template <class OuterIterator>
inline typename indirect_iterator_generator<OuterIterator>::type
make_indirect_iterator(OuterIterator base)
{
    typedef typename indirect_iterator_generator
        <OuterIterator>::type result_t;
    return result_t(base);
}
# endif


//=============================================================================
// Reverse Iterators Adaptor

struct reverse_iterator_policies : public default_iterator_policies
{
    template <class Reference, class Iterator>
    Reference dereference(type<Reference>, const Iterator& x) const
        { return *boost::prior(x); }
    
    template <class Iterator>
    void increment(Iterator& x) const
        { --x; }
    
    template <class Iterator>
    void decrement(Iterator& x) const
        { ++x; }
    
    template <class Iterator, class DifferenceType>
    void advance(Iterator& x, DifferenceType n) const
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
  
#ifdef BOOST_NO_TEMPLATE_PARTIAL_SPECIALIZATION
namespace detail {
   template <bool is_pointer>
   struct iterator_defaults_select
   {
       template <class Iterator,class Value>
       struct traits
       {
           typedef typename boost::detail::iterator_traits<Iterator>::value_type value_type;
           typedef typename boost::detail::iterator_traits<Iterator>::pointer pointer;
           typedef typename boost::detail::iterator_traits<Iterator>::reference reference;
       };
   };

   template <>
   struct iterator_defaults_select<true>
   {
       template <class Iterator,class Value>
       struct traits
       {
           typedef Value value_type;
           typedef Value* pointer;
           typedef Value& reference;
       };
   };

   template <class Iterator,class Value>
   struct iterator_defaults
   {
       enum { is_ptr = boost::is_pointer<Iterator>::value };
       typedef iterator_defaults_select<is_ptr>::template traits<Iterator,Value> traits;
       typedef typename traits::pointer pointer;
       typedef typename traits::reference reference;
   };
}
#endif

template <class Iterator,
    class Value = BOOST_ARG_DEPENDENT_TYPENAME boost::detail::iterator_traits<Iterator>::value_type,
#ifndef BOOST_NO_TEMPLATE_PARTIAL_SPECIALIZATION
    class Pointer = BOOST_ARG_DEPENDENT_TYPENAME boost::detail::iterator_traits<Iterator>::pointer,
    class Reference = BOOST_ARG_DEPENDENT_TYPENAME boost::detail::iterator_traits<Iterator>::reference,
#else
    class Pointer = BOOST_ARG_DEPENDENT_TYPENAME boost::detail::iterator_defaults<Iterator,Value>::pointer,
    class Reference = BOOST_ARG_DEPENDENT_TYPENAME boost::detail::iterator_defaults<Iterator,Value>::reference,
#endif
    class Category = BOOST_ARG_DEPENDENT_TYPENAME boost::detail::iterator_traits<Iterator>::iterator_category,
    class Distance = BOOST_ARG_DEPENDENT_TYPENAME boost::detail::iterator_traits<Iterator>::difference_type
         >
struct reverse_iterator_generator
{
    typedef typename boost::remove_const<Value>::type value_type;
    typedef boost::iterator<Category,value_type,Distance,Pointer,Reference> traits;
    typedef iterator_adaptor<Iterator,reverse_iterator_policies,traits> type;
};

template <class Iterator>
inline typename reverse_iterator_generator<Iterator>::type
make_reverse_iterator(Iterator base)
{
    typedef typename reverse_iterator_generator<Iterator>::type result_t;
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
    typedef boost::detail::iterator_traits<Iterator> Traits;
    typedef typename AdaptableUnaryFunction::result_type value_type;
    typedef boost::iterator<typename Traits::iterator_category, 
        value_type, typename Traits::difference_type, value_type*, value_type&>
            projection_traits;
public:
    typedef iterator_adaptor<Iterator,
        projection_iterator_policies<AdaptableUnaryFunction>,
            projection_traits> type;
};

template <class AdaptableUnaryFunction, class Iterator>
class const_projection_iterator_generator {
    typedef boost::detail::iterator_traits<Iterator> Traits;
    typedef typename AdaptableUnaryFunction::result_type value_type;
    typedef boost::iterator<typename Traits::iterator_category, 
        value_type, typename Traits::difference_type, const value_type*, const value_type&>
            projection_traits;
public:
    typedef iterator_adaptor<Iterator,
        projection_iterator_policies<AdaptableUnaryFunction>,
            projection_traits> type;
};

template <class AdaptableUnaryFunction, class Iterator, class ConstIterator>
struct projection_iterator_pair_generator {
    typedef typename projection_iterator_generator<AdaptableUnaryFunction, Iterator>::type iterator;
    typedef typename const_projection_iterator_generator<AdaptableUnaryFunction, Iterator>::type const_iterator;
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
class filter_iterator_policies : public default_iterator_policies {
public:
    filter_iterator_policies() { }

    filter_iterator_policies(const Predicate& p, const Iterator& end) 
        : m_predicate(p), m_end(end) { }

    void initialize(Iterator& x) {
        advance(x);
    }

    // dwa 2/4/01 - The Iter template argument neccessary for compatibility with
    // a MWCW bug workaround
    template <class Iter>
    void increment(Iter& x) {
        ++x;
        advance(x);
    }
private:
    void advance(Iterator& iter)
    {
        while (m_end != iter && !m_predicate(*iter))
            ++iter;
    }  
    Predicate m_predicate;
    Iterator m_end;
};

template <class Predicate, class Iterator, 
          class Traits = boost::detail::iterator_traits<Iterator>
         >
class filter_iterator_generator {
    typedef filter_iterator_policies<Predicate, Iterator> Policies;
public:
    typedef filter_iterator_policies<Predicate, Iterator> policies_type;
    typedef iterator_adaptor<Iterator, Policies, Traits> type;
};


// WARNING: Do not use this three argument version of
// make_filter_iterator() if the iterator is a builtin pointer type
// and if your compiler does not support partial specialization.

// If the Predicate argument "p" is left out, an explicit template
// argument for the Predicate is required, i.e.,
// make_filter_iterator<Predicate>(f, l).
template <class Predicate, class Iterator>
inline typename filter_iterator_generator<Predicate, Iterator>::type
make_filter_iterator(Iterator first, Iterator last, const Predicate& p = Predicate())
{
  typedef filter_iterator_generator<Predicate, Iterator> Gen;
  typedef typename Gen::policies_type policies_t;
  typedef typename Gen::type result_t;
  return result_t(first, policies_t(p, last));
}

// Supply the Traits type via an exaplicit template argument, i.e.,
// make_filter_iterator<Traits>(f, l).
//
// If the Predicate argument "p" is left out, an explicit template
// argument for the Predicate is also required, i.e.,
// make_filter_iterator<Traits, Predicate>(f, l).
template <class Traits, class Predicate, class Iterator>
inline typename filter_iterator_generator<Predicate, Iterator, Traits>::type
make_filter_iterator(Iterator first, Iterator last, const Predicate& p = Predicate(), Traits* = 0)
{
  typedef filter_iterator_generator<Predicate, Iterator, Traits> Gen;
  typedef typename Gen::policies_type policies_t;
  typedef typename Gen::type result_t;
  return result_t(first, policies_t(p, last));
}


} // namespace boost
# undef BOOST_ARG_DEPENDENT_TYPENAME


#endif



