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

#ifndef BOOST_ITERATOR_ADAPTOR_DWA053000_HPP_
#define BOOST_ITERATOR_ADAPTOR_DWA053000_HPP_

#include <iterator>
#include <boost/utility.hpp>
#include <boost/operators.hpp>
#include <boost/compressed_pair.hpp>

// I was having some problems with VC6. I couldn't tell whether our hack for
// stock GCC was causing problems so I needed an easy way to turn it on and
// off. Now we can test the hack with various compilers and still have an "out"
// if it doesn't work. -dwa 7/31/00
#if __GNUC__ == 2 && __GNUC_MINOR__ <= 96 && !defined(__STL_USE_NAMESPACES)
# define BOOST_RELOPS_AMBIGUITY_BUG 1
#endif

namespace boost {

// Just a "type envelope"; works around some MSVC deficiencies.
template <class T>
struct type {};

//=============================================================================
// Default policies for iterator adaptors. You can use this as a base
// class if you want to customize particular policies.
struct default_iterator_policies
{
    // Some of these members were defined static, but Borland got confused
    // and thought they were non-const.

    template <class Reference, class Iterator>
    Reference dereference(type<Reference>, const Iterator& x) const
        { return *x; }

    template <class Iterator>
    static void increment(Iterator& x)
        { ++x; }

    template <class Iterator>
    static void decrement(Iterator& x)
        { --x; }

    template <class Iterator, class DifferenceType>
    static void advance(Iterator& x, DifferenceType n)
        { x += n; }

    template <class Difference, class Iterator1, class Iterator2>
    Difference distance(type<Difference>, const Iterator1& x, const Iterator2& y) const
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

//=============================================================================
// iterator_adaptor - A generalized adaptor around an existing
//   iterator, which is itself an iterator
//
//   Iterator - the iterator type being wrapped.
//
//   Policies - a set of policies determining how the resulting iterator
//      works.
//
//   Traits - a class satisfying the same requirements as a specialization of
//      std::iterator_traits for the resulting iterator.
//
//   NonconstIterator - the corresponding non-const iterator type for
//      Iterator, if any. You don't need to supply this if you are not make a
//      const/non-const iterator pair.
//
template <class Iterator, class Policies, 
#ifdef BOOST_NO_STD_ITERATOR_TRAITS
          class Traits,
#else
          class Traits = std::iterator_traits<Iterator>,
#endif
          class NonconstIterator = Iterator
         >
struct iterator_adaptor :
#ifdef BOOST_RELOPS_AMBIGUITY_BUG
    iterator_comparisons<
          iterator_adaptor<Iterator,Policies,Traits,NonconstIterator>,
#endif
          boost::iterator<typename Traits::iterator_category, 
              typename Traits::value_type, typename Traits::difference_type,
              typename Traits::pointer, typename Traits::reference>
#ifdef BOOST_RELOPS_AMBIGUITY_BUG
>
#endif
{
    typedef iterator_adaptor<Iterator, Policies, Traits,NonconstIterator> Self;
public:
    typedef typename Traits::difference_type difference_type;
    typedef typename Traits::value_type value_type;
    typedef typename Traits::pointer pointer;
    typedef typename Traits::reference reference;
    typedef typename Traits::iterator_category iterator_category;
    typedef Iterator iterator_type;

    iterator_adaptor() { }

    iterator_adaptor(const iterator_type& iter, const Policies& p = Policies())
        : m_iter_p(iter, p) {}

#ifdef BOOST_MSVC6_MEMBER_TEMPLATES
    template <class MutableIterator, class OtherTraits>
    iterator_adaptor(const iterator_adaptor<MutableIterator, Policies, OtherTraits, NonconstIterator>& rhs)
        : m_iter_p(rhs.iter(), rhs.policies()) {}
    
    template <class MutableIterator, class OtherTraits>
    Self& operator=(const iterator_adaptor<MutableIterator, Policies, OtherTraits, NonconstIterator>& rhs)
    { 
      iter() = rhs.iter(); 
      policies() = rhs.policies();
      return *this; 
    }
#else
    template <class OtherTraits>
    iterator_adaptor(const iterator_adaptor<NonconstIterator, Policies, OtherTraits, NonconstIterator>& rhs)
        : m_iter_p(rhs.iter(), rhs.policies()) {}
    
    template <class OtherTraits>
    Self& operator=(const iterator_adaptor<NonconstIterator, Policies, OtherTraits, NonconstIterator>& rhs)
    { 
      iter() = rhs.iter(); 
      policies() = rhs.policies();
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

    pointer operator->() const
        { return &*this; }

#ifdef _MSC_VER
# pragma warning(pop)
#endif

    reference operator[](difference_type n)
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
        policies().decrement(iter());
        return *this;
    }
    
    Self operator--(int) { Self tmp(*this); --*this; return tmp; }

    Self& operator+=(difference_type n) {
        policies().advance(iter(), n);
        return *this;
    }
  
    Self& operator-=(difference_type n) {
        policies().advance(iter(), -n);
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

template <class Iterator, class Policies, class Traits, class NonconstIterator>
iterator_adaptor<Iterator,Policies,Traits,NonconstIterator>
operator-(iterator_adaptor<Iterator,Policies,Traits,NonconstIterator> p, const typename Traits::difference_type x)
{
    return p -= x;
}

template <class Iterator, class Policies, class Traits, class NonconstIterator>
iterator_adaptor<Iterator,Policies,Traits,NonconstIterator>
operator+(iterator_adaptor<Iterator,Policies,Traits,NonconstIterator> p, const typename Traits::difference_type x)
{
    return p += x;
}

template <class Iterator, class Policies, class Traits, class NonconstIterator>
iterator_adaptor<Iterator,Policies,Traits,NonconstIterator>
operator+(const typename Traits::difference_type x, iterator_adaptor<Iterator,Policies,Traits,NonconstIterator> p)
{
    return p += x;
}

template <class Iterator1, class Iterator2, class Policies, class Traits1, class Traits2, class NonconstIterator>
typename Traits1::difference_type operator-(
    const iterator_adaptor<Iterator1,Policies,Traits1,NonconstIterator>& x,
    const iterator_adaptor<Iterator2,Policies,Traits2,NonconstIterator>& y )
{
    typedef typename Traits1::difference_type difference_type;
    return x.policies().distance(type<difference_type>(), y.iter(), x.iter());
}

#ifndef BOOST_RELOPS_AMBIGUITY_BUG
template <class Iterator1, class Iterator2, class Policies, class Traits1, class Traits2, class NonconstIterator>
inline bool 
operator==(const iterator_adaptor<Iterator1,Policies,Traits1,NonconstIterator>& x, const iterator_adaptor<Iterator2,Policies,Traits2,NonconstIterator>& y) {
    return x.policies().equal(x.iter(), y.iter());
}

template <class Iterator1, class Iterator2, class Policies, class Traits1, class Traits2, class NonconstIterator>
inline bool 
operator<(const iterator_adaptor<Iterator1,Policies,Traits1,NonconstIterator>& x, const iterator_adaptor<Iterator2,Policies,Traits2,NonconstIterator>& y) {
    return x.policies().less(x.iter(), y.iter());
}

template <class Iterator1, class Iterator2, class Policies, class Traits1, class Traits2, class NonconstIterator>
inline bool 
operator>(const iterator_adaptor<Iterator1,Policies,Traits1,NonconstIterator>& x,
          const iterator_adaptor<Iterator2,Policies,Traits2,NonconstIterator>& y) { 
    return x.policies().less(y.iter(), x.iter());
}

template <class Iterator1, class Iterator2, class Policies, class Traits1, class Traits2, class NonconstIterator>
inline bool 
operator>=(const iterator_adaptor<Iterator1,Policies,Traits1,NonconstIterator>& x, const iterator_adaptor<Iterator2,Policies,Traits2,NonconstIterator>& y) {
    return !x.policies().less(x.iter(), y.iter());
}

template <class Iterator1, class Iterator2, class Policies, class Traits1, class Traits2, class NonconstIterator>
inline bool 
operator<=(const iterator_adaptor<Iterator1,Policies,Traits1,NonconstIterator>& x,
           const iterator_adaptor<Iterator2,Policies,Traits2,NonconstIterator>& y) {
    return !x.policies().less(y.iter(), x.iter());
}

template <class Iterator1, class Iterator2, class Policies, class Traits1, class Traits2, class NonconstIterator>
inline bool 
operator!=(const iterator_adaptor<Iterator1,Policies,Traits1,NonconstIterator>& x, 
           const iterator_adaptor<Iterator2,Policies,Traits2,NonconstIterator>& y) {
    return !x.policies().equal(x.iter(), y.iter());
}
#endif

//=============================================================================
// iterator_adaptors - A type generator that simplifies creating
//   mutable/const pairs of iterator adaptors.

template <class Iterator, class ConstIterator, 
#ifdef BOOST_NO_STD_ITERATOR_TRAITS
          class Traits, 
          class ConstTraits, 
#else
          class Traits = std::iterator_traits<Iterator>, 
          class ConstTraits = std::iterator_traits<ConstIterator>, 
#endif
          class Policies = default_iterator_policies>
class iterator_adaptors
{
public:
    typedef iterator_adaptor<Iterator, Policies, Traits, Iterator> iterator;
    typedef iterator_adaptor<ConstIterator, Policies, ConstTraits, Iterator> 
      const_iterator;
};


//=============================================================================
// Transform Iterator Adaptor

template <class AdaptableUnaryFunction>
struct transform_iterator_policies : public default_iterator_policies
{
    transform_iterator_policies() { }
    transform_iterator_policies(const AdaptableUnaryFunction& f) : m_f(f) { }
    
    template <class Reference, class Iterator>
    Reference dereference(type<Reference>, const Iterator& x) const
        { return m_f(*x); }

    AdaptableUnaryFunction m_f;
};

template <class AdaptableUnaryFunction, class IteratorTraits>
struct transform_iterator_traits {
    typedef typename AdaptableUnaryFunction::result_type value_type;
    typedef value_type reference;
    typedef value_type* pointer;
    typedef typename IteratorTraits::difference_type difference_type;
    typedef typename IteratorTraits::iterator_category iterator_category;
};
  
template <class AdaptableUnaryFunction,
          class Iterator,
#ifndef BOOST_NO_STD_ITERATOR_TRAITS
          class Traits = std::iterator_traits<Iterator>
#else
          class Traits
#endif
         >
struct transform_iterator
{
    typedef transform_iterator_traits<AdaptableUnaryFunction,Traits>
      TransTraits;
    typedef iterator_adaptor<Iterator, 
      transform_iterator_policies<AdaptableUnaryFunction>, TransTraits, 
      Iterator> type;
};


//=============================================================================
// Indirect Iterators Adaptor

// Tried implementing this with transform_iterator, but that required
// using boost::remove_ref, which is not compiler portable.

struct indirect_iterator_policies : public default_iterator_policies
{
    template <class Reference, class Iterator>
    Reference dereference(type<Reference>, const Iterator& x) const
        { return **x; }
};

template <class IndirectIterator,
#ifdef BOOST_NO_STD_ITERATOR_TRAITS
          class IndirectTraits,
          class Traits
#else
          class IndirectTraits = std::iterator_traits<IndirectIterator>,
          class Traits = 
            std::iterator_traits<typename IndirectTraits::value_type>
#endif
       >
struct indirect_traits
{
    typedef typename IndirectTraits::difference_type difference_type;
    typedef typename Traits::value_type value_type;
    typedef typename Traits::pointer pointer;
    typedef typename Traits::reference reference;
    typedef typename IndirectTraits::iterator_category iterator_category;
};

template <class IndirectIterator, class ConstIndirectIterator,
#ifdef BOOST_NO_STD_ITERATOR_TRAITS
          class IndirectTraits,
          class ConstIndirectTraits,
          class Traits
#else
          class IndirectTraits = 
              std::iterator_traits<IndirectIterator>,
          class ConstIndirectTraits = 
              std::iterator_traits<ConstIndirectIterator>,
          class Traits =
              std::iterator_traits<typename IndirectTraits::value_type>
#endif
           >
struct indirect_iterators
{
    typedef typename IndirectTraits::value_type Iterator;
    typedef typename Traits::value_type ValueType;
    typedef iterator_adaptors<IndirectIterator, ConstIndirectIterator,
        indirect_traits<IndirectIterator, IndirectTraits, Traits>,
        indirect_traits<ConstIndirectIterator, ConstIndirectTraits, Traits>,
        indirect_iterator_policies
        > Adaptors;
    typedef typename Adaptors::iterator iterator;
    typedef typename Adaptors::const_iterator const_iterator;
};


//=============================================================================
// Reverse Iterators Adaptor

struct reverse_iterator_policies
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
  
template <class Iterator, class ConstIterator,
#ifndef BOOST_NO_STD_ITERATOR_TRAITS
          class Traits = std::iterator_traits<Iterator>, 
          class ConstTraits = std::iterator_traits<ConstIterator>
#else
          class Traits,
          class ConstTraits
#endif
         >
struct reverse_iterators
{
    typedef iterator_adaptors<Iterator,ConstIterator,Traits,ConstTraits,
        reverse_iterator_policies> Adaptor;
    typedef typename Adaptor::iterator iterator;
    typedef typename Adaptor::const_iterator const_iterator;
};

} // namespace boost

#endif

