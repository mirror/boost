
::

    template <class Predicate, class Iterator>
    filter_iterator<Predicate,Iterator>
    make_filter_iterator(Predicate f, Iterator x, Iterator end = Iterator());

:Returns: An instance of ``filter_iterator<Predicate,Iterator>`` 
    where ``m_iter`` is either the first position in the range ``[x,end)`` such that
    ``f(*this->base()) == true`` or else ``m_iter == end``.
    The member ``m_pred`` is constructed from ``f`` and ``m_end`` from ``end``.

::

    template <class Predicate, class Iterator>
    filter_iterator<Predicate,Iterator>
    make_filter_iterator(Iterator x, Iterator end = Iterator());

:Returns: An instance of ``filter_iterator<Predicate,Iterator>`` 
    where ``m_iter`` is either the first position in the range ``[x,end)``
    such that ``f(*this->base()) == true``, where ``f`` is a default
    constructed ``Predicate``, or else ``m_iter == end``.
    The member ``m_pred`` is default constructed and  ``m_end`` 
    is constructed from ``end``.
