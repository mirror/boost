::

  template <class Iterator>
  class reverse_iterator
  {
  public:
    reverse_iterator() {}
    explicit reverse_iterator(Iterator x) ;

    template<class OtherIterator>
    reverse_iterator(
        reverse_iterator<OtherIterator> const& r
      , typename enable_if_convertible<OtherIterator, Iterator>::type* = 0 // exposition
    );
    reference operator*() const;
    reverse_iterator& operator++();
  private:
    Iterator current; // exposition
  };


``reverse_iterator`` requirements
---------------------------------

The base ``Iterator`` must be a model of Bidirectional Traversal
Iterator and Readable Iterator.


``reverse_iterator`` models
---------------------------

``reverse_iterator`` models Bidirectional Traversal Iterator and
Readable Iterator.  In addition, ``reverse_iterator`` models the same
standard iterator access concepts that the ``Iterator``
argument models.



``reverse_iterator`` operations
-------------------------------

``reverse_iterator();``

:Requires: ``Iterator`` must be Default Constructible.
:Returns: An instance of ``reverse_iterator`` with ``current`` 
  default constructed.

``explicit reverse_iterator(Iterator x);``

:Returns: An instance of ``reverse_iterator`` with a
  ``current`` constructed from ``x``.


::

    template<class OtherIterator>
    reverse_iterator(
        reverse_iterator<OtherIterator> const& r
      , typename enable_if_convertible<OtherIterator, Iterator>::type* = 0 // exposition
    );

:Requires: ``OtherIterator`` is implicitly convertible to ``Iterator``.
:Returns: An instance of ``reverse_iterator`` that is a copy of ``r``.


``reference operator*() const;``

:Effects: 

::

    Iterator tmp = current;
    return *--tmp;


``reverse_iterator& operator++();``

:Effects: ``--current``
:Returns: ``*this``
