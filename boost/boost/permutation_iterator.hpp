// (C) Copyright Toon Knapen 2001. Permission to copy, use,
// modify, sell and distribute this software is granted provided this
// copyright notice appears in all copies. This software is provided
// "as is" without express or implied warranty, and with no claim as
// to its suitability for any purpose.
//

#include <boost/iterator_adaptors.hpp>

namespace boost {

  template < typename OrderIt >
  struct permutation_iterator_policies : public default_iterator_policies
  {
    permutation_iterator_policies() {}

    permutation_iterator_policies(OrderIt order_it) 
      : order_it_( order_it ) 
    {}

    template <class IteratorAdaptor>
    typename IteratorAdaptor::reference dereference(const IteratorAdaptor& x) const
    { return *(x.base() + *order_it_); }

    template <class IteratorAdaptor>
    void increment(IteratorAdaptor& x)
    { ++order_it_; }

    template <class IteratorAdaptor>
    void decrement(IteratorAdaptor& x)
    { --order_it_; }

    template <class IteratorAdaptor, class DifferenceType>
    void advance(IteratorAdaptor& x, DifferenceType n)
    { std::advance( order_it_, n ); }

    template <class IteratorAdaptor1, class IteratorAdaptor2>
    typename IteratorAdaptor1::difference_type
    distance(const IteratorAdaptor1& x, const IteratorAdaptor2& y) const
    { return std::distance( x.policies().order_it_, y.policies().order_it_ ); }

    template <class IteratorAdaptor1, class IteratorAdaptor2>
    bool equal(const IteratorAdaptor1& x, const IteratorAdaptor2& y) const
    { return x.policies().order_it_ == y.policies().order_it_; }
  
    OrderIt order_it_;
  };

  /// generate an iterator that will access the elements
  /// behind the random-access iterator RAIt in the
  /// order specified by the OrderIt iterator.
  /// preconditions:
  /// The OrderIt::value_type will be used in iterator arithmetic
  template < typename RAIt, typename OrderIt >
  struct permutation_iterator_generator
  {
    typedef boost::iterator_adaptor
    < RAIt,
      permutation_iterator_policies< OrderIt > 
    > type;
  };

  template < class OrderIt, class RAIt >
  inline typename permutation_iterator_generator< RAIt, OrderIt >::type
  make_permutation_iterator(RAIt base, OrderIt order)
  {
    typedef typename permutation_iterator_generator< RAIt, OrderIt >::type result_t;
    return result_t( base, order );
  }

} // namespace boost
