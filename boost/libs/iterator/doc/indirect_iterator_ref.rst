::

  template <
      class Iterator
    , class Value = use_default
    , class CategoryOrTraversal = use_default
    , class Reference = use_default
    , class Difference = use_default
  >
  class indirect_iterator
    : public iterator_adaptor<
                 indirect_iterator<Iterator, Value, Access, Traversal, 
                                   Reference, Difference>,
                 Iterator,
                 /* Value = see below */,
                 CategoryOrTraversal,
                 Reference,
                 Difference>
  {
      friend class iterator_core_access;
   public:
      indirect_iterator();
      indirect_iterator(Iterator x);

      template <
          class Iterator2, class Value2, class Category2
        , class Reference2, class Difference2
      >
      indirect_iterator(
          indirect_iterator<
               Iterator2, Value2, Category2, Reference2, Difference2
          > const& y
        , typename enable_if_convertible<Iterator2, Iterator>::type* = 0 // exposition
      );
  private: // as-if specification
      typename indirect_iterator::reference dereference() const
      {
          return **this->base();
      }
  };

  template <class Dereferenceable>
  struct referent {
    typedef /* see below */ type;
  };


If ``Value`` is not ``use_default`` then the the argument for the
``iterator_adaptor`` base class' ``Value`` parameter is ``Value`` with
cv-qualifiers removed. If ``Value`` is ``use_default``, then the
argument for the ``iterator_adaptor`` base class' ``Value`` parameter
is computed as follows. We use the abbreviation
``V=iterator_traits<Iterator>::value_type`` and ``v`` is an object of
type ``V``.::

    if (*v returns a constant lvalue or an rvalue) then
        referent<V>::type
    else
        add_const<referent<V>::type>::type

The algorithm for the ``type`` member of ``referent`` traits class is
as follows::

    if (Dereferenceable is a class and has member element_type)
        Dereferenceable::element_type
    else
        iterator_traits<Dereferenceable>::value_type


``indirect_iterator`` requirements
..................................

The ``CategoryOrTraversal`` argument shall be one of the standard
iterator tags or ``use_default``. If ``CategoryOrTraversal`` is an
iterator tag, ``indirect_iterator`` satisfies the requirements
corresponding to the iterator tag. The template parameter ``Iterator``
argument shall meet the requirements corresponding to the iterator
tag.  If ``CategoryOrTraversal`` is ``use_default`` then the
``Iterator`` argument shall meet the requirements of Readable
Iterator. In this case, ``indirect_iterator`` satisfies the
requirements of the most refined standard traversal concept that is
satisfied by the ``Iterator`` argument.

The expression ``*i``, where ``i`` is an object of type
``iterator_traits<Iterator>::value_type``, must be a valid expression
and must be convertible to ``indirect_iterator::reference`` Also,
there are further requirements on the
``iterator_traits<Iterator>::value_type`` if the ``Value`` parameter
is not ``use_default``, as implied by the algorithm for deducing the
default.



``indirect_iterator`` operations
................................

``indirect_iterator();``

:Requires: ``Iterator`` must be Default Constructible.
:Returns: An instance of ``indirect_iterator`` with 
   a default-constructed ``iterator_adaptor`` subobject.


``indirect_iterator(Iterator x);``

:Returns: An instance of ``indirect_iterator`` with
    the ``iterator_adaptor`` subobject copy constructed from ``x``.

::

  template <
      class Iterator2, class Value2, unsigned Access, class Traversal
    , class Reference2, class Difference2
  >
  indirect_iterator(
      indirect_iterator<
           Iterator2, Value2, Access, Traversal, Reference2, Difference2
      > const& y
    , typename enable_if_convertible<Iterator2, Iterator>::type* = 0 // exposition
  );

:Requires: ``Iterator2`` is implicitly convertible to ``Iterator``.
:Returns: An instance of ``indirect_iterator`` whose 
    ``iterator_adaptor`` subobject is constructed from ``y.base()``.


