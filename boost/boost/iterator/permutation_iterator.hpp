// (C) Copyright Toon Knapen    2001.
// (C) Copyright David Abrahams 2003.
// (C) Copyright Roland Richter 2003.
// Permission to copy, use, modify, sell and distribute this software
// is granted provided this copyright notice appears in all copies.
// This software is provided "as is" without express or implied
// warranty, and with no claim as to its suitability for any purpose.

#ifndef BOOST_PERMUTATION_ITERATOR_HPP
#define BOOST_PERMUTATION_ITERATOR_HPP

#include <iterator>

#include <boost/iterator/iterator_adaptor.hpp>


namespace boost
{

template< class ElementIterator
        , class IndexIterator
        , class ValueT        = use_default
        , class CategoryT     = use_default
        , class ReferenceT    = use_default
        , class DifferenceT   = use_default >
class permutation_iterator
  : public iterator_adaptor< 
             permutation_iterator<ElementIterator, IndexIterator, ValueT, CategoryT, ReferenceT, DifferenceT>
           , ElementIterator, ValueT, CategoryT, ReferenceT, DifferenceT >
{
  typedef iterator_adaptor< 
            permutation_iterator<ElementIterator, IndexIterator, ValueT, CategoryT, ReferenceT, DifferenceT>
          , ElementIterator, ValueT, CategoryT, ReferenceT, DifferenceT > super_t;

  friend class iterator_core_access;

public:
  permutation_iterator() : order_it_() {}

  explicit permutation_iterator(ElementIterator x, IndexIterator y) 
      : super_t(x), order_it_(y) {}

  template<class OtherElementIterator, class OtherIndexIterator, class V, class C, class R, class D >
  permutation_iterator(
      permutation_iterator<OtherElementIterator, OtherIndexIterator, V, C, R, D> const& r
      , typename enable_if_convertible<OtherElementIterator, ElementIterator>::type* = 0
      , typename enable_if_convertible<OtherIndexIterator, IndexIterator>::type* = 0
      )
      : super_t(r.base())
  {}

private:
    typename super_t::reference dereference() const
        { return *(this->base() + *this->order_it_); }
  
    void increment() { ++this->order_it_; }
    void decrement() { --this->order_it_; }

    void advance(typename super_t::difference_type n)
    {
      std::advance( order_it_, n );
    }

    template<class OtherElementIterator, class OtherIndexIterator, class V, class C, class R, class D >
    typename super_t::difference_type
    distance_to( permutation_iterator<OtherElementIterator, OtherIndexIterator, V, C, R, D> const& y ) const
    {
      return std::distance( this->order_it_, y.order_it_ );
    }

    template<class OtherElementIterator, class OtherIndexIterator, class V, class C, class R, class D >
    bool
    equal( permutation_iterator<OtherElementIterator, OtherIndexIterator, V, C, R, D> const& y ) const
    {
      return( y.order_it_ == this->order_it_ );
    }

    IndexIterator order_it_;
};


template <class ElementIterator, class IndexIterator>
permutation_iterator<ElementIterator, IndexIterator> 
make_permutation_iterator( ElementIterator e, IndexIterator i )
{
    return permutation_iterator<ElementIterator, IndexIterator>( e, i );
}


} // namespace boost

#endif
