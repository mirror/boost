::

  template <class UnaryFunction,
            class Iterator, 
            class Reference = use_default, 
            class Value = use_default>
  class transform_iterator
    : public iterator_adaptor</* see discussion */>
  {
    friend class iterator_core_access;
  public:
    transform_iterator();
    transform_iterator(Iterator const& x, UnaryFunction f);

    template<class OtherIterator, class R2, class V2>
    transform_iterator(
          transform_iterator<UnaryFunction, OtherIterator, R2, V2> const& t
        , typename enable_if_convertible<OtherIterator, Iterator>::type* = 0 // exposition
    );

    UnaryFunction functor() const;
  private:
    typename transform_iterator::value_type dereference() const;
    UnaryFunction m_f;
  };


``transform_iterator`` requirements
...................................

The type ``UnaryFunction`` must be Assignable, Copy Constructible, and
the expression ``f(*i)`` must be valid where ``f`` is an object of
type ``UnaryFunction``, ``i`` is an object of type ``Iterator``, and
where the type of ``f(*i)`` must be
``result_of<UnaryFunction(iterator_traits<Iterator>::reference)>::type``.

The type ``Iterator`` must at least model Readable Iterator.  The
resulting ``transform_iterator`` models the most refined of the
following options that is also modeled by ``Iterator``.

  * Writable Lvalue Iterator if ``result_of<UnaryFunction(iterator_traits<Iterator>::reference)>::type`` is a non-const reference. 

  * Readable Lvalue Iterator if ``result_of<UnaryFunction(iterator_traits<Iterator>::reference)>::type`` is a const
    reference.

  * Readable Iterator otherwise. 


The ``transform_iterator`` models the traversal
concept that is modeled by ``Iterator``.

The ``reference`` type of ``transform_iterator`` is
``result_of<UnaryFunction(iterator_traits<Iterator>::reference)>::type``.
The ``value_type`` is ``remove_cv<remove_reference<reference> >::type``.

``transform_iterator`` public operations
........................................


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

``UnaryFunction functor() const;``

:Returns: ``m_f``

``transform_iterator`` private operations
.........................................

``typename transform_iterator::value_type dereference() const;``

:Returns: ``m_f(transform_iterator::dereference());``

