::

  template <class Predicate, class Iterator>
  class filter_iterator
  {
   public:
      typedef iterator_traits<Iterator>::value_type value_type;
      typedef iterator_traits<Iterator>::reference reference;
      typedef iterator_traits<Iterator>::pointer pointer;
      typedef iterator_traits<Iterator>::difference_type difference_type;
      typedef /* see below */ iterator_category;

      filter_iterator();
      filter_iterator(Predicate f, Iterator x, Iterator end = Iterator());
      filter_iterator(Iterator x, Iterator end = Iterator());
      template<class OtherIterator>
      filter_iterator(
          filter_iterator<Predicate, OtherIterator> const& t
          , typename enable_if_convertible<OtherIterator, Iterator>::type* = 0 // exposition
          );
      Predicate predicate() const;
      Iterator end() const;
      reference operator*() const;
      filter_iterator& operator++();
  };


The ``iterator_category`` member is a type convertible to the tags
corresponding to each standard concept modeled by ``filter_iterator``,
as described in the models section.



``filter_iterator`` requirements
--------------------------------

The ``Predicate`` argument must be Assignable, Copy Constructible, and
the expression ``p(x)`` must be valid where ``p`` is an object of type
``Predicate``, ``x`` is an object of type
``iterator_traits<Iterator>::value_type``, and where the type of
``p(x)`` must be convertible to ``bool``.

The ``Iterator`` argument shall meet the requirements of Readable
Iterator and Single Pass Iterator or it shall meet the requirements of
Input Iterator.



``filter_iterator`` models
--------------------------

The concepts that ``filter_iterator`` models are dependent on what
concepts the ``Iterator`` argument models, as specified in the
following tables.

+-----------------------------+----------------------------------------------------------+
| If ``Iterator`` models      | then ``filter_iterator`` models                          |
+=============================+==========================================================+
| Single Pass Iterator        | Single Pass Iterator                                     |
+-----------------------------+----------------------------------------------------------+
| Forward Traversal Iterator  | Forward Traversal Iterator                               |
+-----------------------------+----------------------------------------------------------+

+--------------------------------+----------------------------------------------+
| If ``Iterator`` models         | then ``filter_iterator`` models              |
+================================+==============================================+
| Readable Iterator              | Readable Iterator                            |
+--------------------------------+----------------------------------------------+
| Writable Iterator              | Writable Iterator                            |
+--------------------------------+----------------------------------------------+
| Lvalue Iterator                | Lvalue Iterator                              |
+--------------------------------+----------------------------------------------+

+-------------------------------------------------------+---------------------------------+
| If ``Iterator`` models                                | then ``filter_iterator`` models |
+=======================================================+=================================+
| Readable Iterator, Single Pass Iterator               | Input Iterator                  |
+-------------------------------------------------------+---------------------------------+
| Readable Lvalue Iterator, Forward Traversal Iterator  | Forward Iterator                |
+-------------------------------------------------------+---------------------------------+
| Writable Lvalue Iterator, Forward Traversal Iterator  | Mutable Forward Iterator        |
+-------------------------------------------------------+---------------------------------+

+-----------------------------+----------------------------------------------------------+
| If ``Iterator`` models      | then ``filter_iterator`` models                          |
+=============================+==========================================================+
| Input Iterator              | Input Iterator, Readable Iterator, Single Pass Iterator  |
+-----------------------------+----------------------------------------------------------+
| Forward Iterator            | Forward Iterator, Readable Lvalue Iterator,              |
|                             | Forward Traversal Iterator                               |
+-----------------------------+----------------------------------------------------------+
| Mutable Forward Iterator    | Mutable Forward Iterator, Writable Lvalue Iterator,      |
|                             | Forward Traversal Iterator                               |
+-----------------------------+----------------------------------------------------------+



``filter_iterator`` operations
------------------------------

In addition to those operations required by the concepts that
``filter_iterator`` models, ``filter_iterator`` provides the following
operations.


``filter_iterator();``

:Requires: ``Predicate`` and ``Iterator`` must be Default Constructible.
:Returns: a ``filter_iterator`` whose
    predicate is a default constructed ``Predicate`` and
    whose ``end`` is a default constructed ``Iterator``.


``filter_iterator(Predicate f, Iterator x, Iterator end = Iterator());``

:Returns: A ``filter_iterator`` at the first position in the range ``[x,end)``
    such that ``f(*this->base()) == true`` or else at position ``end``.


``filter_iterator(Iterator x, Iterator end = Iterator());``

:Requires: ``Predicate`` must be Default Constructible.
:Returns: A ``filter_iterator`` at the first position in the range ``[x,end)``
    such that ``f(*this->base()) == true``, where ``f`` is a default
    constructed ``Predicate``, or else at position ``end``.


:Returns: A ``filter_iterator`` at position ``x`` that filters 
    according to a default constructed ``Predicate``
    and that will not increment past ``end``.


::

    template <class OtherIterator>
    filter_iterator(
        filter_iterator<Predicate, OtherIterator> const& t
        , typename enable_if_convertible<OtherIterator, Iterator>::type* = 0 // exposition
        );``

:Requires: ``OtherIterator`` is implicitly convertible to ``Iterator``.
:Returns: A filter iterator at the same position as iterator ``t`` 
  whose predicate and end are copies of ``t.predicate`` and ``t.end()`` . 


``Predicate predicate() const;``

:Returns: A copy of the predicate object used to construct ``*this``.


``Iterator end() const;``

:Returns: A copy of the object ``end`` used to construct ``*this``.



``reference operator*() const;``

:Returns: ``*(this->base())``


``filter_iterator& operator++();``

:Effects: Increments ``*this`` and then continues to
  increment ``*this`` until either ``this->base() == this->end()``
  or ``f(**this) == true``.
  