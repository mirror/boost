.. parsed-literal::

  template <
      class Derived
    , class Value
    , unsigned AccessCategory
    , class TraversalCategory
    , class Reference  = /* see below__ \*/
    , class Difference = ptrdiff_t
  >
  class iterator_facade {
  public:
      typedef remove_cv<Value>::type value_type;
      typedef Reference reference;
      typedef /* see `description of operator->`__ \*/ pointer;
      typedef Difference difference_type;
      typedef iterator_tag<AccessCategory, TraversalCategory> iterator_category;

      reference operator\*() const;
      /* see below__ \*/ operator->() const;
      /* see below__ \*/ operator[](difference_type n) const;
      Derived& operator++();
      Derived operator++(int);
      Derived& operator--();
      Derived operator--(int);
      Derived& operator+=(difference_type n);
      Derived& operator-=(difference_type n);
      Derived operator-(difference_type n) const;
  };

  // Comparison operators
  template <class Dr1, class V1, class AC1, class TC1, class R1, class D1,
            class Dr2, class V2, class AC2, class TC2, class R2, class D2>
  typename enable_if_interoperable<Dr1, Dr2, bool>::type // exposition
  operator ==(iterator_facade<Dr1, V1, AC1, TC1, R1, D1> const& lhs,
              iterator_facade<Dr2, V2, AC2, TC2, R2, D2> const& rhs);

  template <class Dr1, class V1, class AC1, class TC1, class R1, class D1,
            class Dr2, class V2, class AC2, class TC2, class R2, class D2>
  typename enable_if_interoperable<Dr1, Dr2, bool>::type
  operator !=(iterator_facade<Dr1, V1, AC1, TC1, R1, D1> const& lhs,
              iterator_facade<Dr2, V2, AC2, TC2, R2, D2> const& rhs);

  template <class Dr1, class V1, class AC1, class TC1, class R1, class D1,
            class Dr2, class V2, class AC2, class TC2, class R2, class D2>
  typename enable_if_interoperable<Dr1, Dr2, bool>::type
  operator <(iterator_facade<Dr1, V1, AC1, TC1, R1, D1> const& lhs,
             iterator_facade<Dr2, V2, AC2, TC2, R2, D2> const& rhs);

  template <class Dr1, class V1, class AC1, class TC1, class R1, class D1,
            class Dr2, class V2, class AC2, class TC2, class R2, class D2>
  typename enable_if_interoperable<Dr1, Dr2, bool>::type
  operator <=(iterator_facade<Dr1, V1, AC1, TC1, R1, D1> const& lhs,
              iterator_facade<Dr2, V2, AC2, TC2, R2, D2> const& rhs);

  template <class Dr1, class V1, class AC1, class TC1, class R1, class D1,
            class Dr2, class V2, class AC2, class TC2, class R2, class D2>
  typename enable_if_interoperable<Dr1, Dr2, bool>::type
  operator >(iterator_facade<Dr1, V1, AC1, TC1, R1, D1> const& lhs,
             iterator_facade<Dr2, V2, AC2, TC2, R2, D2> const& rhs);

  template <class Dr1, class V1, class AC1, class TC1, class R1, class D1,
            class Dr2, class V2, class AC2, class TC2, class R2, class D2>
  typename enable_if_interoperable<Dr1, Dr2, bool>::type
  operator >=(iterator_facade<Dr1, V1, AC1, TC1, R1, D1> const& lhs,
              iterator_facade<Dr2, V2, AC2, TC2, R2, D2> const& rhs);

  template <class Dr1, class V1, class AC1, class TC1, class R1, class D1,
            class Dr2, class V2, class AC2, class TC2, class R2, class D2>
  typename enable_if_interoperable<Dr1, Dr2, bool>::type
  operator >=(iterator_facade<Dr1, V1, AC1, TC1, R1, D1> const& lhs,
              iterator_facade<Dr2, V2, AC2, TC2, R2, D2> const& rhs);

  // Iterator difference
  template <class Dr1, class V1, class AC1, class TC1, class R1, class D1,
            class Dr2, class V2, class AC2, class TC2, class R2, class D2>
  typename enable_if_interoperable<Dr1, Dr2, bool>::type
  operator -(iterator_facade<Dr1, V1, AC1, TC1, R1, D1> const& lhs,
             iterator_facade<Dr2, V2, AC2, TC2, R2, D2> const& rhs);

  // Iterator addition
  template <class Derived, class V, class AC, class TC, class R, class D>
  Derived operator+ (iterator_facade<Derived, V, AC, TC, R, D> const&,
                     typename Derived::difference_type n)


__ `iterator facade requirements`_

__ `operator arrow`_

__ `operator arrow`_

__ brackets_

[*Note:* The ``enable_if_interoperable`` template used above is for exposition
purposes. The member operators should be only be in an overload set
provided the derived types ``Dr1`` and ``Dr2`` are interoperable, by
which we mean they are convertible to each other.  The
``enable_if_interoperable`` approach uses SFINAE to take the operators
out of the overload set when the types are not interoperable.]


.. we need a new label here because the presence of markup in the
   title prevents an automatic link from being generated

.. _iterator facade requirements:

``iterator_facade`` requirements
................................

Some of the constraints on template parameters to
``iterator_facade`` are expressed in terms of resulting nested
types and should be viewed in the context of their impact on
``iterator_traits<Derived>``.

The ``Derived`` template parameter must be a class derived from
``iterator_facade``.

The nested ``::value_type`` type will be the same as
``remove_cv<Value>::type``, so the ``Value`` parameter must be
an (optionally ``const``\ -qualified) non-reference type.

``AccessCategory`` must be an unsigned value which uses no more
bits than the greatest value of ``iterator_access``.

The nested ``::reference`` will be the same as the ``Reference``
parameter; it must be a suitable reference type for the resulting
iterator.  The default for the ``Reference`` parameter is
``Value&``.

The following table describes the other requirements on the
``Derived`` parameter.  Depending on the resulting iterator's
``iterator_category``, a subset of the expressions listed in the table
are required to be valid.  The operations in the first column must be
accessible to member functions of class ``iterator_core_access``.

In the table below, ``X`` is the derived iterator type, ``a`` is an
object of type ``X``, ``b`` and ``c`` are objects of type ``const X``,
``n`` is an object of ``X::difference_type``, ``y`` is a constant
object of a single pass iterator type interoperable with X, and ``z``
is a constant object of a random access traversal iterator type
interoperable with ``X``.

+--------------------+-------------------+-------------------------------------+---------------------------+
|Expression          |Return Type        |Assertion/Note                       |Required to implement      |
|                    |                   |                                     |Iterator Concept(s)        |
+====================+===================+=====================================+===========================+
|``c.dereference()`` |``X::reference``   |                                     |Readable Iterator, Writable|
|                    |                   |                                     |Iterator                   |
+--------------------+-------------------+-------------------------------------+---------------------------+
|``c.equal(b)``      |convertible to bool|true iff ``b`` and ``c`` are         |Single Pass Iterator       |
|                    |                   |equivalent.                          |                           |
+--------------------+-------------------+-------------------------------------+---------------------------+
|``c.equal(y)``      |convertible to bool|true iff ``c`` and ``y`` refer to the|Single Pass Iterator       |
|                    |                   |same position.  Implements ``c == y``|                           |
|                    |                   |and ``c != y``.                      |                           |
+--------------------+-------------------+-------------------------------------+---------------------------+
|``a.advance(n)``    |unused             |                                     |Random Access Traversal    |
|                    |                   |                                     |Iterator                   |
+--------------------+-------------------+-------------------------------------+---------------------------+
|``a.increment()``   |unused             |                                     |Incrementable Iterator     |
+--------------------+-------------------+-------------------------------------+---------------------------+
|``a.decrement()``   |unused             |                                     |Bidirectional Traversal    |
|                    |                   |                                     |Iterator                   |
+--------------------+-------------------+-------------------------------------+---------------------------+
|``c.distance_to(b)``|convertible to     |equivalent to ``distance(c, b)``     |Random Access Traversal    |
|                    |X::difference_type |                                     |Iterator                   |
+--------------------+-------------------+-------------------------------------+---------------------------+
|``c.distance_to(z)``|convertible to     |equivalent to ``distance(c, z)``.    |Random Access Traversal    |
|                    |X::difference_type |Implements ``c - z``, ``c < z``, ``c |Iterator                   |
|                    |                   |<= z``, ``c > z``, and ``c >= c``.   |                           |
+--------------------+-------------------+-------------------------------------+---------------------------+

.. We should explain more about how the
   functions in the interface of iterator_facade
   are there conditionally. -JGS


``iterator_facade`` operations
..............................

The operations in this section are described in terms of operations on
the core interface of ``Derived`` which may be inaccessible
(i.e. private).  The implementation should access these operations
through member functions of class ``iterator_core_access``.

``reference operator*() const;``

:Returns: ``static_cast<Derived const*>(this)->dereference()``

``operator->() const;`` (see below__)

__ `operator arrow`_

:Returns: If ``X::reference`` is a reference type, returns an object
  of type ``X::pointer`` equal to::

    &static_cast<Derived const*>(this)->dereference()

  Otherwise returns an object of unspecified type such that, given an
  object ``a`` of type ``X``, ``a->m`` is equivalent to ``(w = *a,
  w.m)`` for some temporary object ``w`` of type ``X::value_type``.

  The type ``X::pointer`` is ``Value*`` if
  ``is_writable_iterator<X>::value`` is ``true``, and
  ``Value const*`` otherwise.


.. _brackets:

*unspecified* ``operator[](difference_type n) const;``

:Returns: an object convertible to ``X::reference`` and holding a copy
     *p* of ``a+n`` such that, for a constant object ``v`` of type
     ``X::value_type``, ``X::reference(a[n] = v)`` is equivalent
     to ``p = v``.



``Derived& operator++();``

:Effects: 

  ::

    static_cast<Derived*>(this)->increment();
    return *this;

.. I realize that the committee is moving away from specifying things
   like this in terms of code, but I worried about the imprecision of
   saying that a core interface function is invoked without describing
   the downcast.  An alternative to what I did would be to mention it
   above where we talk about accessibility.


``Derived operator++(int);``

:Effects:

  ::

    Derived tmp(static_cast<Derived const*>(this));
    ++*this;
    return tmp;


``Derived& operator--();``

:Effects:

   ::

      static_cast<Derived*>(this)->decrement();
      return *this;


``Derived operator--(int);``

:Effects:

  ::

    Derived tmp(static_cast<Derived const*>(this));
    --*this;
    return tmp;


``Derived& operator+=(difference_type n);``

:Effects:

  ::

      static_cast<Derived*>(this)->advance(n);
      return *this;


``Derived& operator-=(difference_type n);``

:Effects:

   ::

      static_cast<Derived*>(this)->advance(-n);
      return *this;


``Derived operator-(difference_type n) const;``

:Effects: 

   Derived tmp(static_cast<Derived const*>(this));
   return tmp -= n;

:Returns: ``static_cast<Derived const*>(this)->advance(-n);``


