::

  template <class AdaptableUnaryFunction,
            class Iterator, 
            class Reference = use_default, 
            class Value = use_default>
  class transform_iterator
    : public iterator_adaptor</* see discussion */>
  {
    friend class iterator_core_access;
  public:
    transform_iterator();
    transform_iterator(Iterator const& x, AdaptableUnaryFunction f);

    template<class OtherIterator, class R2, class V2>
    transform_iterator(
          transform_iterator<AdaptableUnaryFunction, OtherIterator, R2, V2> const& t
        , typename enable_if_convertible<OtherIterator, Iterator>::type* = 0 // exposition
    );

    AdaptableUnaryFunction functor() const;
  private:
    typename transform_iterator::value_type dereference() const;
    AdaptableUnaryFunction m_f;
  };


``transform_iterator`` requirements
...................................

The type ``AdaptableUnaryFunction`` must be Assignable, Copy
Constructible, and the expression ``f(x)`` must be valid where ``f``
is an object of type ``AdaptableUnaryFunction``, ``x`` is an object of
type ``AdaptableUnaryFunction::argument_type``, and where the type of
``f(x)`` must be ``AdaptableUnaryFunction::result_type``.

The type ``Iterator`` must at least model Readable Iterator.  The
resulting ``transform_iterator`` models the most refined of the
following options that is also modeled by ``Iterator``.

  * Writable Lvalue Iterator if the ``result_type`` of the
    ``AdaptableUnaryFunction`` is a non-const reference. 

  * Readable Lvalue Iterator if the ``result_type`` is a const
    reference.

  * Readable Iterator otherwise. 


The ``transform_iterator`` models the most refined standard traversal
concept that is modeled by ``Iterator``.

The ``value_type`` of ``transform_iterator`` is
``remove_reference<result_type>::type``. The ``reference`` type is
``result_type``.


``transform_iterator`` public operations
........................................


``transform_iterator();``

:Returns: An instance of ``transform_iterator`` with ``m_f``
  and ``m_iterator`` default constructed.


``transform_iterator(Iterator const& x, AdaptableUnaryFunction f);``

:Returns: An instance of ``transform_iterator`` with ``m_f``
  initialized to ``f`` and ``m_iterator`` initialized to ``x``.


::

    template<class OtherIterator, class R2, class V2>
    transform_iterator(
          transform_iterator<AdaptableUnaryFunction, OtherIterator, R2, V2> const& t
        , typename enable_if_convertible<OtherIterator, Iterator>::type* = 0 // exposition
    );

:Returns: An instance of ``transform_iterator`` that is a copy of ``t``.
:Requires: ``OtherIterator`` is implicitly convertible to ``Iterator``.

``AdaptableUnaryFunction functor() const;``

:Returns: ``m_f``

``transform_iterator`` private operations
.........................................

``typename transform_iterator::value_type dereference() const;``

:Returns: ``m_f(transform_iterator::dereference());``

