.. Version 1.3 of this ReStructuredText document corresponds to
   n1530_, the paper accepted by the LWG for TR1.

.. Copyright David Abrahams, Jeremy Siek, and Thomas Witt 2003. All
   rights reserved


.. parsed-literal::

  template <
      class Derived
    , class Value
    , class CategoryOrTraversal
    , class Reference  = Value&
    , class Difference = ptrdiff_t
  >
  class iterator_facade {
  public:
      typedef remove_const<Value>::type value_type;
      typedef Reference reference;
      typedef Value* pointer;
      typedef Difference difference_type;
      typedef /* see below__ \*/ iterator_category;

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
  template <class Dr1, class V1, class TC1, class R1, class D1,
            class Dr2, class V2, class TC2, class R2, class D2>
  typename enable_if_interoperable<Dr1, Dr2, bool>::type // exposition
  operator ==(iterator_facade<Dr1, V1, TC1, R1, D1> const& lhs,
              iterator_facade<Dr2, V2, TC2, R2, D2> const& rhs);

  template <class Dr1, class V1, class TC1, class R1, class D1,
            class Dr2, class V2, class TC2, class R2, class D2>
  typename enable_if_interoperable<Dr1, Dr2, bool>::type
  operator !=(iterator_facade<Dr1, V1, TC1, R1, D1> const& lhs,
              iterator_facade<Dr2, V2, TC2, R2, D2> const& rhs);

  template <class Dr1, class V1, class TC1, class R1, class D1,
            class Dr2, class V2, class TC2, class R2, class D2>
  typename enable_if_interoperable<Dr1, Dr2, bool>::type
  operator <(iterator_facade<Dr1, V1, TC1, R1, D1> const& lhs,
             iterator_facade<Dr2, V2, TC2, R2, D2> const& rhs);

  template <class Dr1, class V1, class TC1, class R1, class D1,
            class Dr2, class V2, class TC2, class R2, class D2>
  typename enable_if_interoperable<Dr1, Dr2, bool>::type
  operator <=(iterator_facade<Dr1, V1, TC1, R1, D1> const& lhs,
              iterator_facade<Dr2, V2, TC2, R2, D2> const& rhs);

  template <class Dr1, class V1, class TC1, class R1, class D1,
            class Dr2, class V2, class TC2, class R2, class D2>
  typename enable_if_interoperable<Dr1, Dr2, bool>::type
  operator >(iterator_facade<Dr1, V1, TC1, R1, D1> const& lhs,
             iterator_facade<Dr2, V2, TC2, R2, D2> const& rhs);

  template <class Dr1, class V1, class TC1, class R1, class D1,
            class Dr2, class V2, class TC2, class R2, class D2>
  typename enable_if_interoperable<Dr1, Dr2, bool>::type
  operator >=(iterator_facade<Dr1, V1, TC1, R1, D1> const& lhs,
              iterator_facade<Dr2, V2, TC2, R2, D2> const& rhs);

  template <class Dr1, class V1, class TC1, class R1, class D1,
            class Dr2, class V2, class TC2, class R2, class D2>
  typename enable_if_interoperable<Dr1, Dr2, bool>::type
  operator >=(iterator_facade<Dr1, V1, TC1, R1, D1> const& lhs,
              iterator_facade<Dr2, V2, TC2, R2, D2> const& rhs);

  // Iterator difference
  template <class Dr1, class V1, class TC1, class R1, class D1,
            class Dr2, class V2, class TC2, class R2, class D2>
  typename enable_if_interoperable<Dr1, Dr2, bool>::type
  operator -(iterator_facade<Dr1, V1, TC1, R1, D1> const& lhs,
             iterator_facade<Dr2, V2, TC2, R2, D2> const& rhs);

  // Iterator addition
  template <class Derived, class V, class TC, class R, class D>
  Derived operator+ (iterator_facade<Derived, V, TC, R, D> const&,
                     typename Derived::difference_type n)


__ `facade iterator category`_

__ `operator arrow`_

__ brackets_

The ``enable_if_interoperable`` template used above is for exposition
purposes.  The member operators should be only be in an overload set
provided the derived types ``Dr1`` and ``Dr2`` are interoperable, 
meaning that at least one of the types is convertible to the other.  The
``enable_if_interoperable`` approach uses SFINAE to take the operators
out of the overload set when the types are not interoperable.  
The operators should behave *as-if* ``enable_if_interoperable``
were defined to be::

  template <bool, typename> enable_if_interoperable_impl
  {};

  template <typename T> enable_if_interoperable_impl<true,T>
  { typedef T type; };

  template<typename Dr1, typename Dr2, typename T>
  struct enable_if_interoperable
    : enable_if_interoperable_impl<
          is_convertible<Dr1,Dr2>::value || is_convertible<Dr2,Dr1>::value
        , T
      >
  {};


``iterator_facade`` usage
.........................

The following table describes the typical valid expressions on
``iterator_facade``\ 's ``Derived`` parameter, depending on the
iterator concept(s) it will model.  The operations in the first
column must be made accessible to member functions of class
``iterator_core_access``.

In the table below, ``F`` is ``iterator_facade<X,V,C,R,D>``, ``a`` is an
object of type ``X``, ``b`` and ``c`` are objects of type ``const X``,
``n`` is an object of ``F::difference_type``, ``y`` is a constant
object of a single pass iterator type interoperable with ``X``, and ``z``
is a constant object of a random access traversal iterator type
interoperable with ``X``.

+--------------------+----------------------+-------------------------------------+---------------------------+
|Expression          |Return Type           |Assertion/Note                       |Used to implement Iterator |
|                    |                      |                                     |Concept(s)                 |
+====================+======================+=====================================+===========================+
|``c.dereference()`` |``F::reference``      |                                     |Readable Iterator, Writable|
|                    |                      |                                     |Iterator                   |
+--------------------+----------------------+-------------------------------------+---------------------------+
|``c.equal(b)``      |convertible to bool   |true iff ``b`` and ``c`` are         |Single Pass Iterator       |
|                    |                      |equivalent.                          |                           |
+--------------------+----------------------+-------------------------------------+---------------------------+
|``c.equal(y)``      |convertible to bool   |true iff ``c`` and ``y`` refer to the|Single Pass Iterator       |
|                    |                      |same position.  Implements ``c == y``|                           |
|                    |                      |and ``c != y``.                      |                           |
+--------------------+----------------------+-------------------------------------+---------------------------+
|``a.advance(n)``    |unused                |                                     |Random Access Traversal    |
|                    |                      |                                     |Iterator                   |
+--------------------+----------------------+-------------------------------------+---------------------------+
|``a.increment()``   |unused                |                                     |Incrementable Iterator     |
+--------------------+----------------------+-------------------------------------+---------------------------+
|``a.decrement()``   |unused                |                                     |Bidirectional Traversal    |
|                    |                      |                                     |Iterator                   |
+--------------------+----------------------+-------------------------------------+---------------------------+
|``c.distance_to(b)``|convertible to        |equivalent to ``distance(c, b)``     |Random Access Traversal    |
|                    |``F::difference_type``|                                     |Iterator                   |
+--------------------+----------------------+-------------------------------------+---------------------------+
|``c.distance_to(z)``|convertible to        |equivalent to ``distance(c, z)``.    |Random Access Traversal    |
|                    |``F::difference_type``|Implements ``c - z``, ``c < z``, ``c |Iterator                   |
|                    |                      |<= z``, ``c > z``, and ``c >= c``.   |                           |
+--------------------+----------------------+-------------------------------------+---------------------------+

.. _facade iterator category:

``iterator_facade`` iterator category
.....................................

The ``iterator_category`` member of ``iterator_facade<X,V,R,C,D>``
is a type which satisfies the following conditions:

   * if ``C`` is convertible to ``std::input_iterator_tag`` or
     ``C`` is convertible to ``std::output_iterator_tag``,
     ``iterator_category`` is the same as ``C``.  

   * Otherwise, if ``C`` is not convertible to
     ``incrementable_traversal_tag``, the program is ill-formed 

   * Otherwise:

     - ``iterator_category`` is convertible to the iterator
       category tag or tags given by the following algorithm, and
       not to any more-derived iterator category tag or tags::

         if (R is a reference type
             && C is convertible to forward_traversal_tag)
         {
             if (C is convertible to random_access_traversal_tag)
                 return random_access_iterator_tag
             else if (C is convertible to bidirectional_traversal_tag)
                 return bidirectional_iterator_tag
             else
                 return forward_traversal_tag
         }
         else
         {
             if (C is convertible to single_pass_traversal_tag
                 && R is convertible to V)
             {
                 if (V is const)
                     return input_iterator_tag
                 else
                     return input_iterator_tag and output_iterator_tag
             }
             else
                 return output_iterator_tag
         }

     - ``iterator_traversal<X>::type`` is convertible to the most
       derived traversal tag type to which ``C`` is also
       convertible, and not to any more-derived traversal tag type.


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

:Returns: If ``reference`` is a reference type, an object
  of type ``pointer`` equal to::

    &static_cast<Derived const*>(this)->dereference()

  Otherwise returns an object of unspecified type such that, 
  ``(*static_cast<Derived const*>(this))->m`` is equivalent to ``(w = **static_cast<Derived const*>(this),
  w.m)`` for some temporary object ``w`` of type ``value_type``.

.. _brackets:

*unspecified* ``operator[](difference_type n) const;``

:Returns: an object convertible to ``reference`` and holding a copy
     *p* of ``*static_cast<Derived const*>(this) + n`` such that, for a constant object ``v`` of type
     ``value_type``, ``(*static_cast<Derived const*>(this))[n] = v`` is equivalent
     to ``p = v``.



``Derived& operator++();``

:Effects: 

  ::

    static_cast<Derived*>(this)->increment();
    return *static_cast<Derived*>(this);

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
      return static_cast<Derived*>(this);


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
      return static_cast<Derived*>(this);


``Derived& operator-=(difference_type n);``

:Effects:
 
  ::

      static_cast<Derived*>(this)->advance(-n);
      return static_cast<Derived*>(this);


``Derived operator-(difference_type n) const;``

:Effects:

  ::

   Derived tmp(static_cast<Derived const*>(this));
   return tmp -= n;



