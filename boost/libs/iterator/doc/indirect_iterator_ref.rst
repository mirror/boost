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

      Iterator base() const;
      reference operator*() const;
      indirect_iterator& operator++();
      indirect_iterator& operator--();
  private:
     Iterator m_iterator; // exposition
  };


The member types of ``indirect_iterator`` are defined according to the
following pseudo-code.  We use the abbreviation
``V=iterator_traits<Iterator>::value_type``.::

  if (Value is use_default) then
      typedef remove_const<pointee<V>::type>::type value_type;
  else
      typedef remove_const<Value>::type value_type;

  if (Reference is use_default) then
      if (Value is use_default) then
          typedef indirect_reference<V>::type reference;
      else
          typedef Value& reference;
  else
      typedef Reference reference;

  if (Value is use_default) then 
      typedef pointee<V>::type* pointer;
  else 
      typedef Value* pointer;

  if (Difference is use_default)
      typedef iterator_traits<Iterator>::difference_type difference_type;
  else
      typedef Difference difference_type;

``iterator_category`` satisfies the following conditions, where
``R`` is ``reference`` and ``V`` is ``value_type``, and where: if
``CategoryOrTraversal`` is ``use_default``, ``C`` is
``iterator_traversal<Iterator>::type`` and otherwise ``C`` is
``CategoryOrTraversal``:

  .. include:: facade_iterator_category.rst

``indirect_iterator`` requirements
..................................

The expression ``*v``, where ``v`` is an object of type
``iterator_traits<Iterator>::value_type``, shall be valid
expression and convertible to ``reference``.  [Note: there are
further requirements on the
``iterator_traits<Iterator>::value_type`` if the ``Value``
parameter is not ``use_default``, as implied by the algorithm for
deducing the default for the ``value_type`` member.]


``indirect_iterator`` models
............................

If ``CategoryOrTraversal`` is a standard iterator tag,
``indirect_iterator`` is a model of the iterator concept
corresponding to the tag.  Otherwise, ``indirect_iterator``
satisfies the requirements of the most refined standard traversal
concept that is satisfied by the ``Iterator`` argument.

``indirect_iterator`` models Readable Iterator.  If
``indirect_iterator::reference(*v) = t`` is a valid expression (where
``t`` is an object of type ``indirect_iterator::value_type``) then
``indirect_iterator`` models Writable Iterator. If
``indirect_iterator::reference`` is a reference then
``indirect_iterator`` models Lvalue Iterator.


``indirect_iterator`` operations
................................

In addition to the operations required by the concepts modeled by
``indirect_iterator``, ``indirect_iterator`` provides the following
operations.


``indirect_iterator();``

:Requires: ``Iterator`` must be Default Constructible.
:Returns: An instance of ``indirect_iterator`` with 
   a default-constructed ``m_iterator``.


``indirect_iterator(Iterator x);``

:Returns: An instance of ``indirect_iterator`` with
    ``m_iterator`` copy constructed from ``x``.

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
    ``m_iterator`` subobject is constructed from ``y.base()``.


``Iterator base() const;``

:Returns: ``m_iterator``


``reference operator*() const;``

:Returns:  ``**m_iterator``


``indirect_iterator& operator++();``

:Effects: ``++m_iterator``
:Returns: ``*this``


``indirect_iterator& operator--();``

:Effects: ``--m_iterator``
:Returns: ``*this``
