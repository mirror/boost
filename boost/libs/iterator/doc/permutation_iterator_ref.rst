.. parsed-literal::

  template< class ElementIterator
	  , class IndexIterator
	  , class ValueT        = use_default
      , unsigned access     = use_default_access
	  , class Traversal     = use_default
	  , class ReferenceT    = use_default
	  , class DifferenceT   = use_default >
  class permutation_iterator
    : public iterator_adaptor<...>
  {
    typedef iterator_adaptor<...>
    friend class iterator_core_access;
  public:
    permutation_iterator();
    explicit permutation_iterator(ElementIterator x, IndexIterator y);

    template< class OEIter, class OIIter, class V, class C, class R, class D >
    permutation_iterator(
	permutation_iterator<OEIter, OIIter, V, C, R, D> const& r
	, typename enable_if_convertible<OEIter, ElementIterator>::type* = 0
	, typename enable_if_convertible<OIIter, IndexIterator>::type* = 0
	);
  };



``permutation_iterator`` requirements
-------------------------------------

``ElementIterator`` must be a model of RandomAccessIterator__.
``IndexIterator`` must at least be a model ForwardIterator__.  The
value type of the ``IndexIterator`` must be convertible to the
difference type of ``ElementIterator``.

__ http://www.sgi.com/tech/stl/RandomAccessIterator.html

__ http://www.sgi.com/tech/stl/ForwardIterator.html




``permutation_iterator`` operations
-----------------------------------

The permutation iterator implements the member functions and operators
required for the `Random Access Iterator`__ concept. However, the
permutation iterator can only meet the complexity guarantees of the
same concept as the IndexIterator. Thus for instance, although the
permutation iterator provides ``operator+=(distance)``, this operation
will take linear time in case the IndexIterator is a model of
ForwardIterator instead of amortized constant time.

__ http://www.sgi.com/tech/stl/RandomAccessIterator.html
