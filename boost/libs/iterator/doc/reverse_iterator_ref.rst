::

  template <class Iterator>
  class reverse_iterator :
    public iterator_adaptor< reverse_iterator<Iterator>, Iterator >
  {
    friend class iterator_core_access;
  public:
    reverse_iterator() {}
    explicit reverse_iterator(Iterator x) ;

    template<class OtherIterator>
    reverse_iterator(
        reverse_iterator<OtherIterator> const& r
      , typename enable_if_convertible<OtherIterator, Iterator>::type* = 0 // exposition
    );

  private: // as-if specification
    typename reverse_iterator::reference dereference() const { return *prior(this->base()); }

    void increment() { --this->base_reference(); }
    void decrement() { ++this->base_reference(); }

    void advance(typename reverse_iterator::difference_type n)
    {
        this->base_reference() += -n;
    }

    template <class OtherIterator>
    typename reverse_iterator::difference_type
    distance_to(reverse_iterator<OtherIterator> const& y) const
    {
        return this->base_reference() - y.base();
    }

  };


``reverse_iterator`` requirements
.................................

The base ``Iterator`` must be a model of Bidirectional Traversal
Iterator. The resulting ``reverse_iterator`` will be a model of the
most refined standard traversal and access concepts that are modeled
by ``Iterator``.


``reverse_iterator();``

:Requires: ``Iterator`` must be Default Constructible.
:Returns: An instance of ``reverse_iterator`` with a
  default constructed base object.

``explicit reverse_iterator(Iterator x);``

:Returns: An instance of ``reverse_iterator`` with a
  base object copy constructed from ``x``.


::

    template<class OtherIterator>
    reverse_iterator(
        reverse_iterator<OtherIterator> const& r
      , typename enable_if_convertible<OtherIterator, Iterator>::type* = 0 // exposition
    );

:Requires: ``OtherIterator`` is implicitly convertible to ``Iterator``.
:Returns: An instance of ``reverse_iterator`` that is a copy of ``r``.
