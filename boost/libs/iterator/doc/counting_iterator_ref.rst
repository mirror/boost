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


If the ``Diference`` argument is ``use_default`` then the
``difference_type`` member is an implementation defined signed
integral type.

The member ``iterator_category`` is a type that satisfies the
requirements of the concepts modeled by the ``counting_iterator`` as
specified in the models section.


[*Note:* implementers are encouraged to provide an implementation of
  ``distance_to`` and a ``difference_type`` that avoids overflows in
  the cases when the ``Incrementable`` type is a numeric type.]

``counting_iterator`` requirements
..................................

The ``Incrementable`` type must be Default Constructible, Copy
Constructible, and Assignable. 


``counting_iterator`` models
............................

``counting_iterator`` models Readable Lvalue Iterator.

Furthermore, if you wish to create a counting iterator that is a
Forward Traversal Iterator and also Forward Iterator, then the
following expressions must be valid::

    Incrementable i, j;
    ++i         // pre-increment
    i == j      // operator equal

If you wish to create a counting iterator that is a Bidirectional
Traversal Iterator and also Bidirectional Iterator, then pre-decrement
is also required::

    --i

If you wish to create a counting iterator that is a Random Access
Traversal Iterator and also Random Access Iterator, then these
additional expressions are also required::

    counting_iterator::difference_type n;
    i += n
    n = i - j
    i < j




``counting_iterator`` operations
................................

In addition to the operations required by the concepts modeled by
``counting_iterator``, ``counting_iterator`` provides the following
operations.


``counting_iterator();``

:Returns: A default constructed instance of ``counting_iterator``.


``counting_iterator(counting_iterator const& rhs);``

:Returns: An instance of ``counting_iterator`` that is a copy of ``rhs``.



``explicit counting_iterator(Incrementable x);``

:Returns: An instance of ``counting_iterator`` with ``m_inc``
    constructed from ``x``.


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
