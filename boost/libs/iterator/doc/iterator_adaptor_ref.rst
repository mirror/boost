.. parsed-literal::
  
  bool
  template <
      class Derived
    , class Base
    , class Value      = use_default
    , unsigned Access  = use_default_access
    , class Traversal  = use_default
    , class Reference  = use_default
    , class Difference = use_default
  >
  class iterator_adaptor 
    : public iterator_facade<Derived, /* see details__ ...\*/>
  {
      friend class iterator_core_access;
   public:
      iterator_adaptor();
      explicit iterator_adaptor(Base iter);
      Base base() const;
   protected:
      Base const& base_reference() const;
      Base& base_reference();
   private: // Core iterator interface for iterator_facade.  
      typename iterator_adaptor::reference dereference() const;

      template <
      class OtherDerived, class OtherIterator, class V, class C, class R, class D
      >   
      bool equal(iterator_adaptor<OtherDerived, OtherIterator, V, C, R, D> const& x) const;
  
      void advance(typename iterator_adaptor::difference_type n);
      void increment();
      void decrement();

      template <
          class OtherDerived, class OtherIterator, class V, class C, class R, class D
      >   
      typename iterator_adaptor::difference_type distance_to(
          iterator_adaptor<OtherDerived, OtherIterator, V, C, R, D> const& y) const;

   private:
      Base m_iterator;
  };

__ :

``iterator_adaptor`` requirements
---------------------------------

The ``Derived`` template parameter must be a derived class of
``iterator_adaptor``. The ``Base`` type must implement the
expressions involving ``m_iterator`` in the specifications of those
private member functions of ``iterator_adaptor`` that are not
redefined by the ``Derived`` class and that are needed to model the
concept corresponding to
``iterator_traits<Derived>::iterator_category`` according to the
requirements of ``iterator_facade``.  The rest of the template
parameters specify the types for the member typedefs in
``iterator_facade``.  The following pseudo-code specifies the
traits types for ``iterator_adaptor``.

::

   if (Value != use_default)
        value_type = remove_cv<Value>::type;
   else
        value_type = iterator_traits<Base>::value_type;


   if (Traversal != use_default)
       traversal_category = Traversal
   else
       traversal_category = traversal_category< Base >::type

   iterator_category = iterator_tag<
                            access_category
                          , traversal_category
                        >

   if (Access != use_default)
   {
      access_category = Access
   }
   else
   {
      access_category
        = access_category< Base >::value

      if (is_const<Value>)
          access_category &= ~writable_iterator;
   }

   iterator_category = iterator_tag<
                            access_category
                          , traversal_category
                        >

   if (Reference != use_default)
       reference = Reference
   else if (Value != use_default)
       reference = Value&
   else
       reference = iterator_traits<Base>::reference


``iterator_adaptor`` public operations
--------------------------------------

``iterator_adaptor();``

:Requires: The ``Base`` type must be Default Constructible.
:Returns: An instance of ``iterator_adaptor`` with 
    ``m_iterator`` default constructed.


``explicit iterator_adaptor(Base iter);``

:Returns: An instance of ``iterator_adaptor`` with
    ``m_iterator`` copy constructed from ``iter``.

``Base base() const;``

:Returns: ``m_iterator``


``iterator_adaptor`` protected member functions
-----------------------------------------------

``Base const& base_reference() const;``

:Returns: A const reference to ``m_iterator``.


``Base& base_reference();``

:Returns: A non-const reference to ``m_iterator``.


``iterator_adaptor`` private member functions
---------------------------------------------

``typename iterator_adaptor::reference dereference() const;``

:Returns: ``*m_iterator``

::

  template <
  class OtherDerived, class OtherIterator, class V, class C, class R, class D
  >   
  bool equal(iterator_adaptor<OtherDerived, OtherIterator, V, C, R, D> const& x) const;

:Returns: ``m_iterator == x.base()``


``void advance(typename iterator_adaptor::difference_type n);``

:Effects: ``m_iterator += n;``

``void increment();``

:Effects: ``++m_iterator;``

``void decrement();``

:Effects: ``--m_iterator;``

::

  template <
      class OtherDerived, class OtherIterator, class V, class C, class R, class D
  >   
  typename iterator_adaptor::difference_type distance_to(
      iterator_adaptor<OtherDerived, OtherIterator, V, C, R, D> const& y) const;

:Returns: ``y.base() - m_iterator``
