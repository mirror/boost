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
      Iterator base() const;
      reference operator*() const;
      filter_iterator& operator++();
  private:
      Predicate m_pred; // exposition only
      Iterator m_iter;  // exposition only
      Iterator m_end;   // exposition only
  };


If ``iterator_traits<Iterator>::reference`` is a reference to
``iterator_traits<Iterator>::value_type`` and
``iterator_traversal<Iterator>::type`` is convertible to
``forward_traversal_tag`` then the ``iterator_category`` member is a
type convertible to ``forward_iterator_tag``.  Otherwise
``iterator_category`` is a type convertible to
``input_iterator_tag``.

.. In that last case, I think the implementation produces a tag
   convertible to both input and output, which seems wrong. -JGS


``filter_iterator`` requirements
................................

The ``Predicate`` argument must be Assignable, Copy Constructible, and
the expression ``p(x)`` must be valid where ``p`` is an object of type
``Predicate``, ``x`` is an object of type
``iterator_traits<Iterator>::value_type``, and where the type of
``p(x)`` must be convertible to ``bool``.

The ``Iterator`` argument shall meet the requirements of Readable
Iterator and Single Pass Iterator or it shall meet the requirements of
Input Iterator.



``filter_iterator`` models
..........................

The concepts that ``filter_iterator`` models are dependent on which
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


``filter_iterator`` operations
..............................

In addition to those operations required by the concepts that
``filter_iterator`` models, ``filter_iterator`` provides the following
operations.


``filter_iterator();``

:Requires: ``Predicate`` and ``Iterator`` must be Default Constructible.
:Returns: a ``filter_iterator`` whose``m_pred``,  ``m_iter``, and ``m_end`` 
  members are a default constructed.


``filter_iterator(Predicate f, Iterator x, Iterator end = Iterator());``

:Returns: A ``filter_iterator`` where ``m_iter`` is either
    the first position in the range ``[x,end)`` such that ``f(*m_iter) == true`` 
    or else``m_iter == end``. The member ``m_pred`` is constructed from
    ``f`` and ``m_end`` from ``end``.



``filter_iterator(Iterator x, Iterator end = Iterator());``

:Requires: ``Predicate`` must be Default Constructible and
  ``Predicate`` is a class type (not a function pointer).
:Returns: A ``filter_iterator`` where ``m_iter`` is either
    the first position in the range ``[x,end)`` such that ``m_pred(*m_iter) == true`` 
    or else``m_iter == end``. The member ``m_pred`` is default constructed.


::

    template <class OtherIterator>
    filter_iterator(
        filter_iterator<Predicate, OtherIterator> const& t
        , typename enable_if_convertible<OtherIterator, Iterator>::type* = 0 // exposition
        );``

:Requires: ``OtherIterator`` is implicitly convertible to ``Iterator``.
:Returns: A filter iterator whose members are copied from ``t``.


``Predicate predicate() const;``

:Returns: ``m_pred``


``Iterator end() const;``

:Returns: ``m_end``


``Iterator base() const;``

:Returns: ``m_iterator``



``reference operator*() const;``

:Returns: ``*m_iter``


``filter_iterator& operator++();``

:Effects: Increments ``m_iter`` and then continues to
  increment ``m_iter`` until either ``m_iter == m_end``
  or ``m_pred(*m_iter) == true``.
:Returns: ``*this``  
