::

  template <
      class Incrementable
    , class CategoryOrTraversal = use_default
    , class Difference = use_default
  >
  class counting_iterator
  {
   public:
      typedef Incrementable value_type;
      typedef const Incrementable& reference;
      typedef const Incrementable* pointer;
      typedef /* see below */ difference_type;
      typedef /* see below */ iterator_category;

      counting_iterator();
      counting_iterator(counting_iterator const& rhs);
      explicit counting_iterator(Incrementable x);
      Incrementable base() const;
      reference operator*() const;
      counting_iterator& operator++();
      counting_iterator& operator--();
   private:
      Incrementable m_inc; // exposition
    };


If the ``Difference`` argument is ``use_default`` then the
``difference_type`` member is an implementation defined signed
integral type. Otherwise ``difference_type`` is ``Difference``.

If ``CategoryOrTraversal`` is not ``use_default`` then the member
``iterator_category`` is ``CategoryOrTraversal``.  Otherwise, if
``Incrementable`` is a numeric type then ``iterator_category`` is a
type convertible to ``random_access_iterator_tag``. If
``Incrementable`` is not a numeric type then ``iterator_category`` is
``iterator_traversal<Incrementable>::type``.


[*Note:* implementers are encouraged to provide an implementation of
  ``operator-`` and a ``difference_type`` that avoids overflows in
  the cases when the ``Incrementable`` type is a numeric type.]


``counting_iterator`` requirements
..................................

The ``Incrementable`` type must be Default Constructible, Copy
Constructible, and Assignable. 

If ``iterator_category`` is convertible to ``forward_iterator_tag`` or
``forward_traversal_tag`` then the following expressions must be valid::

    Incrementable i, j;
    ++i         // pre-increment
    i == j      // operator equal


If ``iterator_category`` is convertible to
``bidirectional_iterator_tag`` or ``bidirectional_traversal_tag`` then
pre-decrement is required::

    --i

If ``iterator_category`` is convertible to
``random_access_iterator_tag`` or ``random_access_traversal_tag`` then
these additional expressions are also required::

    counting_iterator::difference_type n;
    i += n
    n = i - j
    i < j



``counting_iterator`` models
............................

``counting_iterator`` models Readable Lvalue Iterator. In addition,
``counting_iterator`` models the concepts corresponding to the
iterator tags that ``counting_iterator::iterator_category`` is
convertible to.


``counting_iterator`` operations
................................

In addition to the operations required by the concepts modeled by
``counting_iterator``, ``counting_iterator`` provides the following
operations.


``counting_iterator();``

:Effects: Default construct the member ``m_inc``.


``counting_iterator(counting_iterator const& rhs);``

:Effects: Construct member ``m_inc`` from ``rhs.m_inc``.



``explicit counting_iterator(Incrementable x);``

:Effects: Construct member ``m_inc`` from ``x``.


``reference operator*() const;``

:Returns: ``m_inc``


``counting_iterator& operator++();``

:Effects: ``++m_inc``
:Returns: ``*this``


``counting_iterator& operator--();``

:Effects: ``--m_inc``
:Returns: ``*this``  


``Incrementable base() const;``

:Returns: ``m_inc``
