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

``indirect_iterator`` requirements
..................................

The following requirements are placed on the type
``iterator_traits<Iterator>::value_type``. Let ``i`` be an object of
type ``iterator_traits<Iterator>::value_type``.  Then ``*i`` must be a
valid expression, and the type of ``*i`` must be the same as the
``Reference`` template parameter.

The ``Value`` template parameter will be the ``value_type`` for the
``indirect_iterator``, unless ``Value`` is cv-qualified. If ``Value``
is cv-qualified then ``value_type`` will be non-qualified version of
the type.  The default for ``Value`` is

::

  iterator_traits< iterator_traits<Iterator>::value_type >::value_type

If the default is used for ``Value``, then there must be a valid
specialization of ``iterator_traits`` for the value type of the base
iterator.

.. THE ABOVE IS NO LONGER IN SYNC WITH THE CODE. -Jeremy


The indirect iterator will model the most refined standard traversal
concept that is modeled by the ``Iterator`` type and that refines the
traversal category specified in the ``CategoryOrTraversal`` parameter.
The indirect iterator will model the most refined standard access
concept that is modeled by the value type of ``Iterator``.


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


