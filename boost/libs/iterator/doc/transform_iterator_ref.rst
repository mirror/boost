.. Version 1.3 of this document was accepted for TR1

::

  template <class UnaryFunction,
            class Iterator, 
            class Reference = use_default, 
            class Value = use_default>
  class transform_iterator
  {
  public:
    transform_iterator();
    transform_iterator(Iterator const& x, UnaryFunction f);

    template<class F2, class I2, class R2, class V2>
    transform_iterator(
          transform_iterator<F2, I2, R2, V2> const& t
        , typename enable_if_convertible<I2, Iterator>::type* = 0      // exposition
        , typename enable_if_convertible<F2, UnaryFunction>::type* = 0 // exposition
    );
    Iterator base() const;
    UnaryFunction functor() const;
    reference operator*() const;
    transform_iterator& operator++();
    transform_iterator& operator--();
  private:
    Iterator m_iterator; // exposition
    UnaryFunction m_f;   // exposition
  };


``transform_iterator`` requirements
...................................

The type ``UnaryFunction`` must be Assignable, Copy Constructible, and
the expression ``f(*i)`` must be valid where ``f`` is an object of
type ``UnaryFunction``, ``i`` is an object of type ``Iterator``, and
where the type of ``f(*i)`` must be
``result_of<UnaryFunction(iterator_traits<Iterator>::reference)>::type``.

The type ``Iterator`` must at least model Readable Iterator.  


``transform_iterator`` models
.............................

The resulting ``transform_iterator`` models the most refined of the
following options that is also modeled by ``Iterator``.

  * Writable Lvalue Iterator if ``result_of<UnaryFunction(iterator_traits<Iterator>::reference)>::type`` is a non-const reference. 

  * Readable Lvalue Iterator if ``result_of<UnaryFunction(iterator_traits<Iterator>::reference)>::type`` is a const
    reference.

  * Readable Iterator otherwise. 


The ``transform_iterator`` models the most refined standard traversal
concept that is modeled by ``Iterator``.

The ``reference`` type of ``transform_iterator`` is
``result_of<UnaryFunction(iterator_traits<Iterator>::reference)>::type``.
The ``value_type`` is ``remove_cv<remove_reference<reference> >::type``.


``transform_iterator`` operations
.................................

In addition to the operations required by the concepts modeled by
``transform_iterator``, ``transform_iterator`` provides the following
operations.


``transform_iterator();``

:Returns: An instance of ``transform_iterator`` with ``m_f``
  and ``m_iterator`` default constructed.


``transform_iterator(Iterator const& x, UnaryFunction f);``

:Returns: An instance of ``transform_iterator`` with ``m_f``
  initialized to ``f`` and ``m_iterator`` initialized to ``x``.


::

    template<class OtherIterator, class R2, class V2>
    transform_iterator(
          transform_iterator<UnaryFunction, OtherIterator, R2, V2> const& t
        , typename enable_if_convertible<OtherIterator, Iterator>::type* = 0 // exposition
    );

:Returns: An instance of ``transform_iterator`` that is a copy of ``t``.
:Requires: ``OtherIterator`` is implicitly convertible to ``Iterator``.


``Iterator base() const;``

:Returns: ``m_iterator``


``UnaryFunction functor() const;``

:Returns: ``m_f``


``reference operator*() const;``

:Returns: ``m_f(*m_iterator)``


``transform_iterator& operator++();``

:Effects: ``++m_iterator``
:Returns: ``*this``


``transform_iterator& operator--();``

:Effects: ``--m_iterator``
:Returns: ``*this``

