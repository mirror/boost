::

  template <class Predicate, class Iterator>
  class filter_iterator
      : public iterator_adaptor<
            filter_iterator<Predicate, Iterator>, Iterator
          , use_default
          , /* see details */
        >
  {
   public:
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

   private: // as-if specification
      void increment()
      {
          ++(this->base_reference());
          satisfy_predicate();
      }

      void satisfy_predicate()
      {
          while (this->base() != this->m_end && !this->m_predicate(*this->base()))
              ++(this->base_reference());
      }

      Predicate m_predicate;
      Iterator m_end;
  };


``filter_iterator`` requirements
--------------------------------

The base ``Iterator`` parameter must be a model of Readable
Iterator and Single Pass Iterator. The resulting
``filter_iterator`` will be a model of Forward Traversal Iterator
if ``Iterator`` is, otherwise the ``filter_iterator`` will be a
model of Single Pass Iterator. The access category of the
``filter_iterator`` will be the same as the access category of
``Iterator``.

.. Thomas is going to try implementing filter_iterator so that
   it will be bidirectional if the underlying iterator is. -JGS


The ``Predicate`` must be Assignable, Copy Constructible, and the
expression ``p(x)`` must be valid where ``p`` is an object of type
``Predicate``, ``x`` is an object of type
``iterator_traits<Iterator>::value_type``, and where the type of
``p(x)`` must be convertible to ``bool``.



``filter_iterator`` operations
------------------------------

``filter_iterator();``

:Requires: ``Predicate`` and ``Iterator`` must be Default Constructible.
:Returns: a ``filter_iterator`` whose
    predicate is a default constructed ``Predicate`` and
    whose ``end`` is a default constructed ``Iterator``.


``filter_iterator(Predicate f, Iterator x, Iterator end = Iterator());``

:Returns: A ``filter_iterator`` at position ``x`` that filters according
    to predicate ``f`` and that will not increment past ``end``.


``filter_iterator(Iterator x, Iterator end = Iterator());``

:Requires: ``Predicate`` must be Default Constructible.
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
:Returns: A copy of iterator ``t``. 


``Predicate predicate() const;``

:Returns: A copy of the predicate object used to construct ``*this``.


``Iterator end() const;``

:Returns: The object ``end`` used to construct ``*this``.

