::

  template <class Iterator>
  class reverse_iterator
  {
  public:
    typedef iterator_traits<Iterator>::value_type value_type;
    typedef iterator_traits<Iterator>::reference reference;
    typedef iterator_traits<Iterator>::pointer pointer;
    typedef iterator_traits<Iterator>::difference_type difference_type;
    typedef /* see below */ iterator_category;

    reverse_iterator() {}
    explicit reverse_iterator(Iterator x) ;

    template<class OtherIterator>
    reverse_iterator(
        reverse_iterator<OtherIterator> const& r
      , typename enable_if_convertible<OtherIterator, Iterator>::type* = 0 // exposition
    );
    Iterator base() const;
    reference operator*() const;
    reverse_iterator& operator++();
    reverse_iterator& operator--();
  private:
    Iterator m_iterator; // exposition
  };


The ``iterator_category`` member is a type convertible to the iterator
tag given by the following algorithm.  Let ``T`` be
``iterator_traits<Iterator>::value_type``, ``R`` be
``iterator_traits<Iterator>::reference``, and ``C`` be
``traveral_category<Iterator>::type``.

::

    if (R is a reference to T) then
        if (C is convertible to random_access_traversal_tag) then
            random_access_iterator_tag
        else
            bidirectional_iterator_tag
    else
        input_iterator_tag



``reverse_iterator`` requirements
.................................

``Iterator`` must be a model of Bidirectional Traversal Iterator
and Readable Iterator.


``reverse_iterator`` models
...........................

A specialization of ``reverse_iterator`` models the same standard
traversal and access iterator concepts modeled by its ``Iterator``
argument.  In addition, it models the old iterator concepts
specified in the following table:

+---------------------------------------+-----------------------------------+
| If ``I`` models                       |then ``reverse_iterator<I>`` models|
+=======================================+===================================+
| Readable Lvalue Iterator,             | Bidirectional Iterator            |
| Bidirectional Traversal Iterator      |                                   |
+---------------------------------------+-----------------------------------+
| Writable Lvalue Iterator,             | Mutable Bidirectional Iterator    |
| Bidirectional Traversal Iterator      |                                   |
+---------------------------------------+-----------------------------------+
| Readable Lvalue Iterator,             | Random Access Iterator            |
| Random Access Traversal Iterator      |                                   |
+---------------------------------------+-----------------------------------+
| Writable Lvalue Iterator,             | Mutable Random Access Iterator    |
| Random Access Traversal Iterator      |                                   |
+---------------------------------------+-----------------------------------+


``reverse_iterator`` operations
...............................

In addition to the operations required by the concepts modeled by
``reverse_iterator``, ``reverse_iterator`` provides the following
operations.



``reverse_iterator();``

:Requires: ``Iterator`` must be Default Constructible.
:Returns: An instance of ``reverse_iterator`` with ``m_iterator`` 
  default constructed.

``explicit reverse_iterator(Iterator x);``

:Returns: An instance of ``reverse_iterator`` with a
  ``m_iterator`` constructed from ``x``.


::

    template<class OtherIterator>
    reverse_iterator(
        reverse_iterator<OtherIterator> const& r
      , typename enable_if_convertible<OtherIterator, Iterator>::type* = 0 // exposition
    );

:Requires: ``OtherIterator`` is implicitly convertible to ``Iterator``.
:Returns: An instance of ``reverse_iterator`` that is a copy of ``r``.




``Iterator base() const;``

:Returns: ``m_iterator``


``reference operator*() const;``

:Effects: 

::

    Iterator tmp = m_iterator;
    return *--tmp;


``reverse_iterator& operator++();``

:Effects: ``--m_iterator``
:Returns: ``*this``


``reverse_iterator& operator--();``

:Effects: ``++m_iterator``
:Returns: ``*this``
