::

  template <
      class Iterator
    , class Value = use_default
    , class CategoryOrTraversal = use_default
    , class Reference = use_default
    , class Difference = use_default
  >
  class indirect_iterator
  {
   public:
      typedef /* see below */ value_type;
      typedef /* see below */ reference;
      typedef /* see below */ pointer;
      typedef /* see below */ difference_type;
      typedef /* see below */ iterator_category;

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
  };


The member types of ``indirect_iterator`` are defined according to the
following pseudo-code.  We use the abbreviation
``V=iterator_traits<Iterator>::value_type``.::

  if (Value is use_default) then
      typedef iterator_traits<V>::value_type value_type;
  else
      typedef remove_const<Value>::type value_type;

  if (Reference is use_default) then
      if (Value is use_default) then
          typedef iterator_traits<V>::reference reference;
      else
          typedef Value& reference;
  else
      typedef Reference reference;

  if (Value is use_default) then
      typedef ?? pointer;
  else
      typedef Value* pointer;

  if (Difference is use_default)
      typedef iterator_traits<Iterator>::difference_type difference_type;
  else
      typedef Difference difference_type;


The member ``indirect_iterator::iterator_category`` is a type that
satisfies the requirements of the concepts modeled by the indirect
iterator as specified in the models section.


``indirect_iterator`` requirements
..................................

The ``Iterator`` argument shall meet the requirements of Readable
Iterator. The ``CategoryOrTraversal`` argument shall be one of the
standard iterator tags or ``use_default``. If ``CategoryOrTraversal``
is an iterator tag, the template parameter ``Iterator`` argument shall
meet the traversal requirements corresponding to the iterator tag.

The expression ``*v``, where ``v`` is an object of type
``iterator_traits<Iterator>::value_type``, must be a valid expression
and must be convertible to ``indirect_iterator::reference``.  Also
``indirect_iterator::reference`` must be convertible to
``indirect_iterator::value``.  There are further requirements on the
``iterator_traits<Iterator>::value_type`` if the ``Value`` parameter
is not ``use_default``, as implied by the algorithm for deducing the
default for the ``value_type`` member.


``indirect_iterator`` models
............................

If ``CategoryOrTraversal`` is a standard iterator tag,
``indirect_iterator`` is a model of the iterator concept corresponding
to the tag, otherwise ``indirect_iterator`` satisfies the requirements
of the most refined standard traversal concept that is satisfied by
the ``Iterator`` argument.

``indirect_iterator`` models Readable Iterator.  If
``indirect_iterator::reference(*v) = t`` is a valid expression (where
``t`` is an object of type ``indirect_iterator::value_type``) then
``indirect_iterator`` models Writable Iterator. If
``indirect_iterator::reference`` is a reference then
``indirect_iterator`` models Lvalue Iterator.


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


