::

  template <
      class Iterator
    , class Value = use_default
    , unsigned Access  = use_default_access
    , class Traversal  = use_default
    , class Reference = use_default
    , class Difference = use_default
  >
  class indirect_iterator
    : public iterator_adaptor</* see discussion */>
  {
      friend class iterator_core_access;
   public:
      indirect_iterator();
      indirect_iterator(Iterator x);
      template <
          class Iterator2, class Value2, unsigned Access2, class Traversal2
        , class Reference2, class Difference2
      >
      indirect_iterator(
          indirect_iterator<
               Iterator2, Value2, Access2, Traversal2, Reference2, Difference2
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

The ``value_type`` of the ``Iterator`` template parameter should
itself be dereferenceable. The return type of the ``operator*`` for
the ``value_type`` must be the same type as the ``Reference`` template
parameter. The ``Value`` template parameter will be the ``value_type``
for the ``indirect_iterator``, unless ``Value`` is const. If ``Value``
is ``const X``, then ``value_type`` will be *non-* ``const X``.  The
default for ``Value`` is

::

  iterator_traits< iterator_traits<Iterator>::value_type >::value_type

If the default is used for ``Value``, then there must be a valid
specialization of ``iterator_traits`` for the value type of the base
iterator.

The ``Reference`` parameter will be the ``reference`` type of the
``indirect_iterator``. The default is ``Value&``.

The ``Access`` and ``Traversal`` parameters are passed unchanged to
the corresponding parameters of the ``iterator_adaptor`` base
class, and  the ``Iterator`` parameter is passed unchanged as the
``Base`` parameter to the ``iterator_adaptor`` base class.

The indirect iterator will model the most refined standard traversal
concept that is modeled by the ``Iterator`` type.  The indirect
iterator will model the most refined standard access concept that is
modeled by the value type of ``Iterator``.


``indirect_iterator`` operations
................................

``indirect_iterator();``

:Requires: ``Iterator`` must be Default Constructible.
:Returns: An instance of ``indirect_iterator`` with
    a default constructed base object.


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
:Returns: An instance of ``indirect_iterator`` that is a copy of ``y``.

