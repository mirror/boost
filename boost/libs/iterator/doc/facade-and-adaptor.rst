+++++++++++++++++++++++++++++
 Iterator Facade and Adaptor
+++++++++++++++++++++++++++++

:Author: David Abrahams, Jeremy Siek, Thomas Witt
:Contact: dave@boost-consulting.com, jsiek@osl.iu.edu, witt@ive.uni-hannover.de
:organization: `Boost Consulting`_, Indiana University `Open Systems
               Lab`_, University of Hanover `Institute for Transport
               Railway Operation and Construction`_
:date: $Date$
:Number: **This document is a revised version of the official** N1476=03-0059
:copyright: Copyright Dave Abrahams, Jeremy Siek, and Thomas Witt 2003. All rights reserved

.. _`Boost Consulting`: http://www.boost-consulting.com
.. _`Open Systems Lab`: http://www.osl.iu.edu
.. _`Institute for Transport Railway Operation and Construction`: http://www.ive.uni-hannover.de

:abstract: We propose a set of class templates that help programmers
           build standard-conforming iterators, both from scratch and
           by adapting other iterators.

.. contents:: Table of Contents

============
 Motivation
============

Iterators play an important role in modern C++ programming. The
iterator is the central abstraction of the algorithms of the Standard
Library, allowing algorithms to be re-used in in a wide variety of
contexts.  The C++ Standard Library contains a wide variety of useful
iterators. Every one of the standard containers comes with constant
and mutable iterators [#mutable]_, and also reverse versions of those
same iterators which traverse the container in the opposite direction.
The Standard also supplies ``istream_iterator`` and
``ostream_iterator`` for reading from and writing to streams,
``insert_iterator``, ``front_insert_iterator`` and
``back_insert_iterator`` for inserting elements into containers, and
``raw_storage_iterator`` for initializing raw memory [7].

Despite the many iterators supplied by the Standard Library, obvious
and useful iterators are missing, and creating new iterator types is
still a common task for C++ programmers.  The literature documents
several of these, for example line_iterator [3] and Constant_iterator
[9].  The iterator abstraction is so powerful that we expect
programmers will always need to invent new iterator types.

Although it is easy to create iterators that *almost* conform to the
standard, the iterator requirements contain subtleties which can make
creating an iterator which *actually* conforms quite difficult.
Further, the iterator interface is rich, containing many operators
that are technically redundant and tedious to implement.  To automate
the repetitive work of constructing iterators, we propose
``iterator_facade``, an iterator base class template which provides
the rich interface of standard iterators and delegates its
implementation to member functions of the derived class.  In addition
to reducing the amount of code necessary to create an iterator, the
``iterator_facade`` also provides compile-time error detection.
Iterator implementation mistakes that often go unnoticed are turned
into compile-time errors because the derived class implementation must
match the expectations of the ``iterator_facade``.

A common pattern of iterator construction is the adaptation of one
iterator to form a new one.  The functionality of an iterator is
composed of four orthogonal aspects: traversal, indirection, equality
comparison and distance measurement.  Adapting an old iterator to
create a new one often saves work because one can reuse one aspect of
functionality while redefining the other.  For example, the Standard
provides ``reverse_iterator``, which adapts any Bidirectional Iterator
by inverting its direction of traversal.  As with plain iterators,
iterator adaptors defined outside the Standard have become commonplace
in the literature:

* Checked iter[13] adds bounds-checking to an existing iterator.

* The iterators of the View Template Library[14], which adapts
  containers, are themselves adaptors over the underlying iterators.

* Smart iterators [5] adapt an iterator's dereferencing behavior by
  applying a function object to the object being referenced and
  returning the result.

* Custom iterators [4], in which a variety of adaptor types are enumerated.

* Compound iterators [1], which access a slice out of a container of containers.

* Several iterator adaptors from the MTL [12].  The MTL contains a
  strided iterator, where each call to ``operator++()`` moves the
  iterator ahead by some constant factor, and a scaled iterator, which
  multiplies the dereferenced value by some constant.

.. [#concept] We use the term concept to mean a set of requirements
   that a type must satisfy to be used with a particular template
   parameter.

.. [#mutable] The term mutable iterator refers to iterators over objects that
   can be changed by assigning to the dereferenced iterator, while
   constant iterator refers to iterators over objects that cannot be
   modified.

To fulfill the need for constructing adaptors, we propose the
``iterator_adaptor`` class template.  Instantiations of
``iterator_adaptor`` serve as a base classes for new iterators,
providing the default behavior of forwarding all operations to the
underlying iterator.  The user can selectively replace these features
in the derived iterator class.  This proposal also includes a number
of more specialized adaptors, such as the ``transform_iterator`` that
applies some user-specified function during the dereference of the
iterator.

========================
 Impact on the Standard
========================

This proposal is purely an addition to the C++ standard library.
However, note that this proposal relies on the proposal for New
Iterator Concepts.

========
 Design
========

Iterator Concepts
=================

This proposal is formulated in terms of the new ``iterator concepts``
as proposed in `n1477`_, since user-defined and especially adapted
iterators suffer from the well known categorization problems that are
inherent to the current iterator categories.

.. _`n1477`: http://anubis.dkuug.dk/JTC1/SC22/WG21/docs/papers/2003/n1477.html

This proposal does not strictly depend on proposal `n1477`_, as there
is a direct mapping between new and old categories. This proposal
could be reformulated using this mapping if `n1477`_ was not accepted.

Interoperability
================

The question of iterator interoperability is poorly addressed in the
current standard.  There are currently two defect reports that are
concerned with interoperability issues.

Issue `179`_ concerns the fact that mutable container iterator types
are only required to be convertible to the corresponding constant
iterator types, but objects of these types are not required to
interoperate in comparison or subtraction expressions.  This situation
is tedious in practice and out of line with the way built in types
work.  This proposal implements the proposed resolution to issue
`179`_, as most standard library implementations do nowadays. In other
words, if an iterator type A has an implicit or user defined
conversion to an iterator type B, the iterator types are interoperable
and the usual set of operators are available.

Issue `280`_ concerns the current lack of interoperability between
reverse iterator types. The proposed new reverse_iterator template
fixes the issues raised in 280. It provides the desired
interoperability without introducing unwanted overloads.

.. _`179`: http://anubis.dkuug.dk/jtc1/sc22/wg21/docs/lwg-defects.html#179
.. _`280`: http://anubis.dkuug.dk/jtc1/sc22/wg21/docs/lwg-active.html#280


Iterator Facade
===============

.. include:: iterator_facade_body.rst

Iterator Adaptor
================

.. include:: iterator_adaptor_body.rst

Specialized Adaptors
====================

This proposal also contains several examples of specialized adaptors
which were easily implemented using ``iterator_adaptor``:

* ``indirect_iterator``, which iterates over iterators, pointers,
  or smart pointers and applies an extra level of dereferencing.

* A new ``reverse_iterator``, which inverts the direction of a Base
  iterator's motion, while allowing adapted constant and mutable
  iterators to interact in the expected ways (unlike those in most
  implementations of C++98).

* ``transform_iterator``, which applies a user-defined function object
  to the underlying values when dereferenced.

* ``projection_iterator``, which is similar to ``transform_iterator``
  except that when dereferenced it returns a reference instead of
  a value.

* ``filter_iterator``, which provides a view of an iterator range in
  which some elements of the underlying range are skipped.

.. _counting_iterator:

* ``counting_iterator``, which adapts any incrementable type
  (e.g. integers, iterators) so that incrementing/decrementing the
  adapted iterator and dereferencing it produces successive values of
  the Base type.

* ``function_output_iterator``, which makes it easier to create custom
  output iterators.

Based on examples in the Boost library, users have generated many new
adaptors, among them a permutation adaptor which applies some
permutation to a random access iterator, and a strided adaptor, which
adapts a random access iterator by multiplying its unit of motion by a
constant factor.  In addition, the Boost Graph Library (BGL) uses
iterator adaptors to adapt other graph libraries, such as LEDA [10]
and Stanford GraphBase [8], to the BGL interface (which requires C++
Standard compliant iterators).

===============
 Proposed Text
===============


Header ``<iterator_helper>`` synopsis    [lib.iterator.helper.synopsis]
=======================================================================


::

  struct use_default;

  struct iterator_core_access { /* implementation detail */ };
  
  template <
      class Derived
    , class Value
    , class AccessCategory
    , class TraversalCategory
    , class Reference  = Value&
    , class Difference = ptrdiff_t
  >
  class iterator_facade;

  template <
      class Derived
    , class Base
    , class Value      = use_default
    , class Category   = use_default
    , class Reference  = use_default
    , class Difference = use_default
  >
  class iterator_adaptor;
  
  template <
      class Iterator
    , class Value = use_default
    , class Category = use_default
    , class Reference = use_default
    , class Difference = use_default
  >
  class indirect_iterator;
  
  template <class Iterator>
  class reverse_iterator;

  template <
      class UnaryFunction
    , class Iterator
    , class Reference = use_default
    , class Value = use_default
  >
  class transform_iterator;

  template <class Predicate, class Iterator>
  class filter_iterator;

  template <
      class Incrementable
    , class Category = use_default
    , class Difference = use_default
  >
  class counting_iterator

  template <class UnaryFunction>
  class function_output_iterator;



Iterator facade [lib.iterator.facade]
=====================================

..include:: iterator_facade_abstract.rst

Class template ``iterator_facade``
----------------------------------

..include:: iterator_facade_ref.rst

Iterator adaptor [lib.iterator.adaptor]
=======================================

The ``iterator_adaptor`` is a base class template derived from an
instantiation of ``iterator_facade``. The core interface functions
expected by ``iterator_facade`` are implemented in terms of the
``iterator_adaptor``\ 's ``Base`` template parameter. A class derived
from ``iterator_adaptor`` typically redefines some of the core
interface functions to adapt the behavior of the ``Base`` type.
Whether the derived class models any of the standard iterator concepts
depends on the operations supported by the ``Base`` type and which
core interface functions of ``iterator_facade`` are redefined in the
``Derived`` class.


Class template ``iterator_adaptor``
-----------------------------------

.. parsed-literal::
  
  template <
      class Derived
    , class Base
    , class Value      = use_default
    , class Category   = use_default
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
``iterator_adaptor``. The ``Base`` type must implement the expressions
involving ``m_iterator`` in the specifications of those private member
functions of ``iterator_adaptor`` that are not redefined by the
``Derived`` class and that are needed to model the concept
corresponding to the chosen ``Category`` according to the requirements
of ``iterator_facade``.  The rest of the template parameters specify
the types for the member typedefs in ``iterator_facade``.  The
following pseudo-code specifies the traits types for
``iterator_adaptor``.

::

    if (Value == use_default)
        value_type = iterator_traits<Base>::value_type;
    else 
        value_type = remove_cv<Value>::type;

    if (Reference == use_default) {
        if (Value == use_default)
            reference = iterator_traits<Base>::reference;
        else 
            reference = Value&;
    } else
        reference = Reference;

    if (Distance == use_default)
        difference_type = iterator_traits<Base>::difference_type;
    else
        difference_type = Distance;

    if (Category == use_default)
        iterator_category = iterator_tag< 
            access_category< 
                iterator< iterator_traits<Base>::iterator_category,
                          Value,
                          Distance,
                          Value*,
                          Reference > >,
            traversal_category<
                iterator< iterator_traits<Base>::iterator_category,
                          Value,
                          Distance,
                          Value*,
                          Reference > >
    else
        iterator_category = Category;


..  Replaced with new semantics --thw
    if (Category == use_default)
        iterator_category = iterator_traits<Base>::iterator_category;
    else
        iterator_category = Category;



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



Specialized adaptors [lib.iterator.special.adaptors]
====================================================

.. The requirements for all of these need to be written *much* more
   formally -DWA


[*Note:* The ``enable_if_convertible<X,Y>::type`` expression used in
this section is for exposition purposes. The converting constructors
for specialized adaptors should be only be in an overload set provided
that an object of type ``X`` is implicitly convertible to an object of
type ``Y``.  The ``enable_if_convertible`` approach uses SFINAE to
take the constructor out of the overload set when the types are not
implicitly convertible.]


Indirect iterator
-----------------

The indirect iterator adapts an iterator by applying an *extra*
dereference inside of ``operator*()``. For example, this iterator
adaptor makes it possible to view a container of pointers
(e.g. ``list<foo*>``) as if it were a container of the pointed-to type
(e.g. ``list<foo>``) .

.. At some point we should add the capability to handle
   iterators over smart pointers, which the impl handles. -JGS


Class template ``indirect_iterator``
....................................

::

  template <
      class Iterator
    , class Value = use_default
    , class Category = use_default
    , class Reference = use_default
    , class Difference = use_default
  >
  class indirect_iterator
    : public iterator_adaptor</* see discussion */>
  {
      friend class iterator_core_access;
   public:
      indirect_iterator();
      indirect_iterator(Iterator x);
      template <
          class Iterator2, class Value2, class Category2
        , class Reference2, class Difference2
      >
      indirect_iterator(
          indirect_iterator<
               Iterator2, Value2, Category2, Reference2, Difference2
          > const& y
        , typename enable_if_convertible<Iterator2, Iterator>::type* = 0 // exposition
      );
  private: // as-if specification
      typename indirect_iterator::reference dereference() const
      {
          return **this->base();
      }
  };

``indirect_iterator`` requirements
..................................

The ``value_type`` of the ``Iterator`` template parameter should
itself be dereferenceable. The return type of the ``operator*`` for
the ``value_type`` must be the same type as the ``Reference`` template
parameter. The ``Value`` template parameter will be the ``value_type``
for the ``indirect_iterator``, unless ``Value`` is const. If ``Value``
is ``const X``, then ``value_type`` will be *non-* ``const X``.  The
default for ``Value`` is

::

  iterator_traits< iterator_traits<Iterator>::value_type >::value_type

If the default is used for ``Value``, then there must be a valid
specialization of ``iterator_traits`` for the value type of the base
iterator.

The ``Reference`` parameter will be the ``reference`` type of the
``indirect_iterator``. The default is ``Value&``.

The ``Category`` parameter is the ``iterator_category`` type for the
``indirect_iterator``. The default is 
``iterator_traits<Iterator>::iterator_category``.

The indirect iterator will model the most refined standard traversal
concept that is modeled by the ``Iterator`` type.  The indirect
iterator will model the most refined standard access concept that is
modeled by the value type of ``Iterator``.


``indirect_iterator`` operations
................................

``indirect_iterator();``

:Requires: ``Iterator`` must be Default Constructible.
:Returns: An instance of ``indirect_iterator`` with
    a default constructed base object.


``indirect_iterator(Iterator x);``

:Returns: An instance of ``indirect_iterator`` with
    the ``iterator_adaptor`` subobject copy constructed from ``x``.

::

  template <
      class Iterator2, class Value2, class Category2
    , class Reference2, class Difference2
  >
  indirect_iterator(
      indirect_iterator<
           Iterator2, Value2, Category2, Reference2, Difference2
      > const& y
    , typename enable_if_convertible<Iterator2, Iterator>::type* = 0 // exposition
  );

:Requires: ``Iterator2`` is implicitly convertible to ``Iterator``.
:Returns: An instance of ``indirect_iterator`` that is a copy of ``y``.

Reverse iterator
----------------

.. I think we'd better strike the old reverse_iterator text from the standard, eh?

The reverse iterator adaptor flips the direction of a base iterator's
motion. Invoking ``operator++()`` moves the base iterator backward and
invoking ``operator--()`` moves the base iterator forward.

Class template ``reverse_iterator``
...................................

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


Transform iterator
------------------

The transform iterator adapts an iterator by applying some function
object to the result of dereferencing the iterator. In other words,
the ``operator*`` of the transform iterator first dereferences the
base iterator, passes the result of this to the function object, and
then returns the result.


Class template ``transform_iterator``
.....................................

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



Filter iterator
---------------

The filter iterator adaptor creates a view of an iterator range in
which some elements of the range are skipped over. A predicate
function object controls which elements are skipped. When the
predicate is applied to an element, if it returns ``true`` then the
element is retained and if it returns ``false`` then the element is
skipped over. When skipping over elements, it is necessary for the
filter adaptor to know when to stop so as to avoid going past the end
of the underlying range. Therefore the constructor of the filter
iterator takes two iterator parameters: the position for the filtered
iterator and the end of the range.



Class template ``filter_iterator``
..................................

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

The base ``Iterator`` parameter must be a model of Readable Iterator
and Single Pass Iterator. The resulting ``filter_iterator`` will be a
model of Forward Traversal Iterator if ``Iterator`` is, otherwise the
``filter_iterator`` will be a model of Single Pass Iterator. The
access category of the ``filter_iterator`` will be the most refined
standard access category that is modeled by ``Iterator``.

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


Counting iterator
-----------------

The counting iterator adaptor implements dereference by returning a
reference to the base object. The other operations are implemented by
the base ``m_iterator``, as per the inheritance from
``iterator_adaptor``.


Class template ``counting_iterator``
....................................

::

  template <class Incrementable, class Category = use_default, class Difference = use_default>
  class counting_iterator
    : public iterator_adaptor<
          counting_iterator<Incrementable, Category, Difference>
        , Incrementable
        , Incrementable
        , /* see details for category */
        , Incrementable const&
        , Incrementable const*
        , /* distance = Difference or a signed integral type */>
  {
      friend class iterator_core_access;
   public:
      counting_iterator();
      counting_iterator(counting_iterator const& rhs);
      counting_iterator(Incrementable x);
   private:
      typename counting_iterator::reference dereference() const
      {
          return this->base_reference();
      }
    };


[*Note:* implementers are encouraged to provide an implementation of
  ``distance_to`` and a ``difference_type`` that avoids overflows in
  the cases when the ``Incrementable`` type is a numeric type.]

``counting_iterator`` requirements
----------------------------------

The ``Incrementable`` type must be Default Constructible, Copy
Constructible, and Assignable.  The default distance is
an implementation defined signed integegral type.

The resulting ``counting_iterator`` models Readable Lvalue Iterator.

Furthermore, if you wish to create a counting iterator that is a Forward
Traversal Iterator, then the following expressions must be valid:
::

    Incrementable i, j;
    ++i         // pre-increment
    i == j      // operator equal

If you wish to create a counting iterator that is a 
Bidirectional Traversal Iterator, then pre-decrement is also required:
::

    --i

If you wish to create a counting iterator that is a Random Access
Traversal Iterator, then these additional expressions are also
required:
::

    counting_iterator::difference_type n;
    i += n
    n = i - j
    i < j




``counting_iterator`` operations
--------------------------------

``counting_iterator();``

:Returns: A default constructed instance of ``counting_iterator``.


``counting_iterator(counting_iterator const& rhs);``

:Returns: An instance of ``counting_iterator`` that is a copy of ``rhs``.



``counting_iterator(Incrementable x);``

:Returns: An instance of ``counting_iterator`` with its base
    object copy constructed from ``x``.


Function output iterator
------------------------

The function output iterator adaptor makes it easier to create custom
output iterators. The adaptor takes a unary function and creates a
model of Output Iterator. Each item assigned to the output iterator is
passed as an argument to the unary function.  The motivation for this
iterator is that creating a conforming output iterator is non-trivial,
particularly because the proper implementation usually requires a
proxy object.


Class template ``function_output_iterator``
...........................................

::

  template <class UnaryFunction>
  class function_output_iterator {
  public:
    typedef iterator_tag<
          writable_iterator_tag
        , incrementable_traversal_tag
    > iterator_category;
    typedef void                value_type;
    typedef void                difference_type;
    typedef void                pointer;
    typedef void                reference;

    explicit function_output_iterator(const UnaryFunction& f = UnaryFunction());

    struct output_proxy {
      output_proxy(UnaryFunction& f);
      template <class T> output_proxy& operator=(const T& value);
    };
    output_proxy operator*();
    function_output_iterator& operator++();
    function_output_iterator& operator++(int);
  };


``function_output_iterator`` requirements
-----------------------------------------

The ``UnaryFunction`` must be Assignable, Copy Constructible, and the
expression ``f(x)`` must be valid, where ``f`` is an object of type
``UnaryFunction`` and ``x`` is an object of a type accepted by ``f``.
The resulting ``function_output_iterator`` is a model of the Writable
and Incrementable Iterator concepts.


``function_output_iterator`` operations
---------------------------------------

``explicit function_output_iterator(const UnaryFunction& f = UnaryFunction());``

:Returns: An instance of ``function_output_iterator`` with
  ``f`` stored as a data member.


``output_proxy operator*();``

:Returns: An instance of ``output_proxy`` constructed with
  a copy of the unary function ``f``.
  

``function_output_iterator& operator++();``

:Returns: ``*this``


``function_output_iterator& operator++(int);``

:Returns: ``*this``


``function_output_iterator::output_proxy`` operations
-----------------------------------------------------

``output_proxy(UnaryFunction& f);``

:Returns: An instance of ``output_proxy`` with ``f`` stored as
    a data member.


``template <class T> output_proxy& operator=(const T& value);``

:Effects: 
  ::

      m_f(value); 
      return *this; 



..
 LocalWords:  Abrahams Siek Witt istream ostream iter MTL strided interoperate
 LocalWords:  CRTP metafunctions inlining lvalue JGS incrementable BGL LEDA cv
 LocalWords:  GraphBase struct ptrdiff UnaryFunction const int typename bool pp
 LocalWords:  lhs rhs SFINAE markup iff tmp OtherDerived OtherIterator DWA foo
 LocalWords:  dereferenceable subobject AdaptableUnaryFunction impl pre ifdef'd
 LocalWords:  OtherIncrementable Coplien
