
::

    template <class Predicate, class Iterator>
    filter_iterator<Predicate,Iterator>
    make_filter_iterator(Predicate f, Iterator x, Iterator end = Iterator());

:Returns: An instance of ``filter_iterator<Predicate,Iterator>`` at
    the first position in the range ``[x,end)`` such that
    ``f(*this->base()) == true`` or else at position ``end``.

::

    template <class Predicate, class Iterator>
    filter_iterator<Predicate,Iterator>
    make_filter_iterator(Iterator x, Iterator end = Iterator());

:Returns: An instance of ``filter_iterator<Predicate,Iterator>`` at
    the first position in the range ``[x,end)``
    such that ``f(*this->base()) == true``, where ``f`` is a default
    constructed ``Predicate``, or else at position ``end``.