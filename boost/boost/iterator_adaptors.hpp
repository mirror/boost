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

// 07 Feb 2001
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
// 06 Feb 2001
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
      typedef typename boost::detail::if_true<(
          boost::is_convertible<category,std::input_iterator_tag>::value
          & !boost::is_convertible<category,std::forward_iterator_tag>::value
      )>::template
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

    // Iterators should satisfy one of the known categories
    BOOST_STATIC_ASSERT((boost::is_convertible<iterator_category,std::input_iterator_tag>::value
                         || boost::is_convertible<iterator_category,std::output_iterator_tag>::value));

    // Iterators >= ForwardIterator must produce real references.
    BOOST_STATIC_ASSERT((!boost::is_convertible<iterator_category,std::forward_iterator_tag>::value
                         || boost::is_same<reference,value_type&>::value
                         || boost::is_same<reference,const value_type&>::value));

    iterator_adaptor() { }

    iterator_adaptor(const Iterator& it, const Policies& p = Policies())
        : m_iter_p(it, p) {
      policies().initialize(iter());
    }

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

template <class AdaptableUnaryFunction, class IteratorTraits>
struct transform_iterator_traits {
    typedef typename AdaptableUnaryFunction::result_type value_type;
    typedef value_type reference;
    typedef value_type* pointer;
    typedef typename IteratorTraits::difference_type difference_type;
    typedef std::input_iterator_tag iterator_category;
};
  
template <class AdaptableUnaryFunction,
          class Iterator,
          class Traits = boost::detail::iterator_traits<Iterator>
         >
struct transform_iterator_generator
{
    typedef transform_iterator_traits<AdaptableUnaryFunction,Traits>
      transform_traits;
    typedef iterator_adaptor<Iterator, 
      transform_iterator_policies<AdaptableUnaryFunction>, transform_traits>
      type;
};

template <class AdaptableUnaryFunction, class Iterator>
typename transform_iterator_generator<AdaptableUnaryFunction,Iterator>::type
make_transform_iterator(
    const Iterator& base,
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

template <class OuterIterator,
          class InnerIterator = typename boost::detail::iterator_traits<OuterIterator>::value_type,
          class InnerTraits = boost::detail::iterator_traits<InnerIterator>,
          class OuterTraits = boost::detail::iterator_traits<OuterIterator> // never needed (?)
       >
struct indirect_traits
{
    typedef typename OuterTraits::difference_type difference_type;
    typedef typename InnerTraits::value_type value_type;
    typedef typename InnerTraits::pointer pointer;
    typedef typename InnerTraits::reference reference;
    typedef typename OuterTraits::iterator_category iterator_category;
};

template <class OuterIterator,      // Mutable or Immutable, does not matter
    // Mutable -> mutable indirect iterator;  Immutable -> immutable indirect iterator
          class InnerIterator = typename boost::detail::iterator_traits<OuterIterator>::value_type,
          class InnerTraits = boost::detail::iterator_traits<InnerIterator>,
          class OuterTraits = boost::detail::iterator_traits<OuterIterator> // never needed (?)
           >
struct indirect_iterator_generator
{
    typedef iterator_adaptor<OuterIterator,
        indirect_iterator_policies,
        indirect_traits<OuterIterator, InnerIterator,
                        InnerTraits, OuterTraits>
    > type;
};

template <class OuterIterator,      // Mutable or Immutable, does not matter
          class ConstInnerIterator, // Immutable
          class ConstInnerTraits = boost::detail::iterator_traits<ConstInnerIterator>,
          class InnerIterator = typename boost::detail::iterator_traits<OuterIterator>::value_type,
          class InnerTraits = boost::detail::iterator_traits<InnerIterator>,
          class OuterTraits = boost::detail::iterator_traits<OuterIterator> // never needed (?)
           >
struct indirect_iterator_pair_generator
{
    typedef iterator_adaptor<OuterIterator,
        indirect_traits<OuterIterator, InnerIterator, InnerTraits, OuterTraits>,
        indirect_iterator_policies> iterator;
        
    typedef iterator_adaptor<OuterIterator,
        indirect_traits<OuterIterator, ConstInnerIterator, ConstInnerTraits, OuterTraits>,
        indirect_iterator_policies> const_iterator;
};


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
  
template <class Iterator,
          class Traits = boost::detail::iterator_traits<Iterator>
         >
struct reverse_iterator_generator
{
    typedef iterator_adaptor<Iterator, reverse_iterator_policies,
        Traits> type;
};

template <class ConstIterator,
          class ConstTraits = boost::detail::iterator_traits<ConstIterator>
         >
struct const_reverse_iterator_generator
{
    typedef iterator_adaptor<ConstIterator, reverse_iterator_policies,
        ConstTraits> type;
};

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

template <class AdaptableUnaryFunction, class Traits>
struct projection_iterator_traits {
    typedef typename AdaptableUnaryFunction::result_type value_type;
    typedef value_type& reference;
    typedef value_type* pointer;
    typedef typename Traits::difference_type difference_type;
    typedef typename Traits::iterator_category iterator_category;
};

template <class AdaptableUnaryFunction, class Traits>
struct const_projection_iterator_traits {
    typedef typename AdaptableUnaryFunction::result_type value_type;
    typedef value_type const& reference;
    typedef value_type const* pointer;
    typedef typename Traits::difference_type difference_type;
    typedef typename Traits::iterator_category iterator_category;
};

template <class AdaptableUnaryFunction, class Iterator,
        class Traits = boost::detail::iterator_traits<Iterator>
        >
struct projection_iterator_generator {
    typedef projection_iterator_traits<AdaptableUnaryFunction, Traits>
            projection_traits;
    typedef iterator_adaptor<Iterator,
            projection_iterator_policies<AdaptableUnaryFunction>,
            projection_traits> type;
};

template <class AdaptableUnaryFunction, class Iterator,
        class Traits = boost::detail::iterator_traits<Iterator>
        >
struct const_projection_iterator_generator {
    typedef const_projection_iterator_traits<AdaptableUnaryFunction,
            Traits> projection_traits;
    typedef iterator_adaptor<Iterator,
            projection_iterator_policies<AdaptableUnaryFunction>,
            projection_traits> type;
};

template <class AdaptableUnaryFunction, class Iterator, class ConstIterator,
        class Traits = boost::detail::iterator_traits<Iterator>,
        class ConstTraits = boost::detail::iterator_traits<ConstIterator>
        >
struct projection_iterator_pair_generator {
    typedef projection_iterator_traits<AdaptableUnaryFunction, Traits>
            projection_traits;
    typedef const_projection_iterator_traits<AdaptableUnaryFunction,
            ConstTraits> const_projection_traits;
    typedef iterator_adaptor<Iterator, projection_iterator_policies<AdaptableUnaryFunction>,
        projection_traits> iterator;
    typedef iterator_adaptor<ConstIterator, projection_iterator_policies<AdaptableUnaryFunction>,
        const_projection_traits > const_iterator;
};

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
    typedef iterator_adaptor<Iterator, Policies, Traits> type;
  };


} // namespace boost

#endif



