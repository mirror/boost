++++++++++++++++++++++
 New Iterator Concepts
++++++++++++++++++++++

:Author: David Abrahams, Jeremy Siek, Thomas Witt
:Contact: dave@boost-consulting.com, jsiek@osl.iu.edu, witt@ive.uni-hannover.de
:organization: `Boost Consulting`_, Indiana University `Open Systems Lab`_, University of Hanover `Institute for Transport Railway Operation and Construction`_
:date: $Date$
:Number: **This document is a revised version of the official** N1477=03-0060 
:copyright: Copyright Dave Abrahams, Jeremy Siek, and Thomas Witt 2003. All rights reserved

.. _`Boost Consulting`: http://www.boost-consulting.com
.. _`Open Systems Lab`: http://www.osl.iu.edu
.. _`Institute for Transport Railway Operation and Construction`: http://www.ive.uni-hannover.de

:Abstract: We propose a new system of iterator concepts that treat
           access and positioning independently. This allows the
           concepts to more closely match the requirements
           of algorithms and provides better categorizations
           of iterators that are used in practice. This proposal
           is a revision of paper n1297_.
          
.. contents:: Table of Contents

.. _n1297: http://anubis.dkuug.dk/jtc1/sc22/wg21/docs/papers/2001/n1297.html

============
 Motivation
============

The standard iterator categories and requirements are flawed because
they use a single hierarchy of concepts to address two orthogonal
issues: *iterator traversal* and *value access*. As a result, many
algorithms with requirements expressed in terms of the iterator
categories are too strict. Also, many real-world iterators can not be
accurately categorized.  A proxy-based iterator with random-access
traversal, for example, may only legally have a category of "input
iterator", so generic algorithms are unable to take advantage of its
random-access capabilities.  The current iterator concept hierarchy is
geared towards iterator traversal (hence the category names), while
requirements that address value access sneak in at various places. The
following table gives a summary of the current value access
requirements in the iterator categories.

+------------------------+-----------------------------------------------------+
|Output Iterator         |``*i = a``                                           |
+------------------------+-----------------------------------------------------+
|Input Iterator          |``*i`` is convertible to ``T``                       |
+------------------------+-----------------------------------------------------+
|Forward Iterator        |``*i`` is ``T&`` (or ``const T&`` once `issue 200`_  |
|                        |is resolved)                                         |
+------------------------+-----------------------------------------------------+
|Random Access Iterator  |``i[n]`` is convertible to ``T`` (also ``i[n] = t``  |
|                        |is required for mutable iterators once `issue 299`_  |
|                        |is resolved)                                         |
+------------------------+-----------------------------------------------------+

.. _issue 200: http://anubis.dkuug.dk/JTC1/SC22/WG21/docs/lwg-active.html#200
.. _issue 299: http://anubis.dkuug.dk/JTC1/SC22/WG21/docs/lwg-active.html#299


Because iterator traversal and value access are mixed together in a
single hierarchy, many useful iterators can not be appropriately
categorized. For example, ``vector<bool>::iterator`` is almost a
random access iterator, but the return type is not ``bool&`` (see
`issue 96`_ and Herb Sutter's paper J16/99-0008 = WG21
N1185). Therefore, the iterators of ``vector<bool>`` only meet the
requirements of input iterator and output iterator. This is so
nonintuitive that at least one implementation erroneously assigns
``random_access_iterator_tag`` as its ``iterator_category``. 

.. _issue 96: http://anubis.dkuug.dk/JTC1/SC22/WG21/docs/lwg-active.html#96

Another difficult-to-categorize iterator is the transform iterator, an
adaptor which applies a unary function object to the dereferenced
value of the some underlying iterator (see `transform_iterator`_).
For unary functions such as ``times``, the return type of
``operator*`` clearly needs to be the ``result_type`` of the function
object, which is typically not a reference.  Because random access
iterators are required to return lvalues from ``operator*``, if you
wrap ``int*`` with a transform iterator, you do not get a random
access iterator as might be expected, but an input iterator.

.. _`transform_iterator`: http://www.boost.org/libs/utility/transform_iterator.htm

A third example is found in the vertex and edge iterators of the
`Boost Graph Library`_. These iterators return vertex and edge
descriptors, which are lightweight handles created on-the-fly. They
must be returned by-value. As a result, their current standard
iterator category is ``input_iterator_tag``, which means that,
strictly speaking, you could not use these iterators with algorithms
like ``min_element()``. As a temporary solution, the concept
`Multi-Pass Input Iterator`_ was introduced to describe the vertex and
edge descriptors, but as the design notes for the concept suggest, a
better solution is needed.

.. _Boost Graph Library: http://www.boost.org/libs/graph/doc/table_of_contents.html
.. _Multi-Pass Input Iterator: http://www.boost.org/libs/utility/MultiPassInputIterator.html

In short, there are many useful iterators that do not fit into the
current standard iterator categories. As a result, the following bad
things happen:

- Iterators are often mis-categorized. 

- Algorithm requirements are more strict than necessary, because they
  cannot separate the need for random access or bidirectional
  traversal from the need for a true reference return type.


========================
 Impact on the Standard
========================

The new iterator concepts are backward-compatible with the old
iterator requirements, and old iterators are forward-compatible with
the new iterator concepts. That is to say, iterators that satisfy the
old requirements also satisfy appropriate concepts in the new system,
and iterators modeling the new concepts will automatically satisfy the
appropriate old requirements.

.. I think we need to say something about the resolution to allow
   convertibility to any of the old-style tags as a TR issue (hope it
   made it). -DWA

.. Hmm, not sure I understand. Are you talking about whether a
   standards conforming input iterator is allowed to have
   a tag that is not input_iterator_tag but that
   is convertible to input_iterator_tag? -JGS

The algorithms in the standard library benefit from the new iterator
concepts because the new concepts provide a more accurate way to
express their type requirements. The result is algorithms that are
usable in more situations and have fewer type requirements. The
following lists the proposed changes to the type requirements of
algorithms.

Forward Iterator -> Forward Traversal Iterator and Readable Iterator

  ``find_end, adjacent_find, search, search_n, rotate_copy, lower_bound, upper_bound, equal_range, binary_search, min_element, max_element``

Forward Iterator (1) -> Single Pass Iterator and Readable Iterator
Forward Iterator (2) -> Forward Traversal Iterator and Readable Iterator

  ``find_first_of``

Forward Iterator -> Readable Iterator and Writable Iterator

  ``iter_swap``

Forward Iterator -> Single Pass Iterator and Writable Iterator

  ``fill, generate``

Forward Iterator -> Forward Traversal Iterator and Swappable Iterator

  ``rotate``

Forward Iterator (1) -> Swappable Iterator and Single Pass Iterator
Forward Iterator (2) -> Swappable Iterator and  Incrementable Iterator

  ``swap_ranges``

Forward Iterator -> Forward Traversal Iterator and Readable Iterator and Writable Iterator
  ``remove, remove_if, unique``

Forward Iterator -> Single Pass Iterator and Readable Iterator and Writable Iterator

  ``replace, replace_if``

Bidirectional Iterator -> Bidirectional Traversal Iterator and Swappable Iterator
  ``reverse``

Bidirectional Iterator -> Bidirectional Traversal Iterator and Readable and Swappable Iterator
  ``partition``

Bidirectional Iterator (1) -> Bidirectional Traversal Iterator and Readable Iterator, 
Bidirectional Iterator (2) -> Bidirectional Traversal Iterator and Writable Iterator

  ``copy_backwards``

Bidirectional Iterator -> Bidirectional Traversal Iterator and Swappable Iterator and Readable Iterator
  ``next_permutation, prev_permutation``

Bidirectional Iterator -> Bidirectional Traversal Iterator and Readable Iterator and Writable Iterator
  ``stable_partition, inplace_merge``

Bidirectional Iterator -> Bidirectional Traversal Iterator and Readable Iterator
  ``reverse_copy``

Random Access Iterator -> Random Access Traversal Iterator and Readable and Swappable Iterator
  ``random_shuffle, sort, stable_sort, partial_sort, nth_element, push_heap, pop_heap
  make_heap, sort_heap``

Input Iterator (2) -> Incrementable Iterator and Readable Iterator
  ``equal``

Input Iterator (2) -> Incrementable Iterator and Readable Iterator
  ``transform``

========
 Design
========

The iterator requirements are be separated into two hierarchies. One
set of concepts handles the syntax and semantics of value access:

- Readable Iterator
- Writable Iterator
- Swappable Iterator
- Readable Lvalue Iterator
- Writable Lvalue Iterator

The refinement relationships among these iterator concepts are given
in the following diagram.

.. image:: access.png

The access concepts describe requirements related to ``operator*`` and
``operator->``, including the ``value_type``, ``reference``, and
``pointer`` associated types.

The other set of concepts handles traversal:

- Incrementable Iterator
- Single Pass Iterator
- Forward Traversal Iterator
- Bidirectional Traversal Iterator
- Random Access Traversal Iterator

The refinement relationships for the traversal concepts are in the
following diagram.

.. image:: traversal.png

In addition to the iterator movement operators, such as
``operator++``, the traversal concepts also include requirements on
position comparison such as ``operator==`` and ``operator<``.  The
reason for the fine grain slicing of the concepts into the
Incrementable and Single Pass is to provide concepts that are exact
matches with the original input and output iterator requirements.

The relationship between the new iterator concepts and the old are
given in the following diagram.

.. image:: oldeqnew.png

Like the old iterator requirements, we provide tags for purposes of
dispatching. There are two hierarchies of tags, one for the access
concepts and one for the traversal concepts. We provide an access
mechanism for mapping iterator types to these new tags. Our design
reuses ``iterator_traits<Iter>::iterator_category`` as the access
mechanism. To enable this, a pair of access and traversal tags are
combined into a single type using the following `iterator_tag` class.

::

  template <class AccessTag, class TraversalTag>
  struct iterator_tag : /* appropriate old category or categories */
  {
    typedef AccessTag access;
    typedef TraversalTag traversal;
  };

The ``iterator_tag`` class template is derived from the appropriate
iterator tag or tags from the old requirements based on the new-style
tags passed as template parameters. The algorithm for determining the
old tag or tags from the new tags picks the least-refined old concepts
that include all of the requirements of the access and traversal
concepts (that is, the closest fit), if any such category exists.  For
example, a the category tag for a Readable Single Pass Iterator will
always be derived from ``input_iterator_tag``, while the category tag
for a Single Pass Iterator that is both Readable and Writable will be
derived from both ``input_iterator_tag`` and ``output_iterator_tag``.

We also provide two helper classes that make it convenient to obtain
the access and traversal tags of an iterator. These helper classes
work both for iterators whose ``iterator_category`` is
``iterator_tag`` and also for iterators using the original iterator
categories.

::

  template <class Iterator> struct access_category { typedef ... type; };
  template <class Iterator> struct traversal_category { typedef ... type; };


The most difficult design decision concerned the ``operator[]``. The
direct approach for specifying ``operator[]`` would have a return type
of ``reference``; the same as ``operator*``. However, going in this
direction would mean that an iterator satisfying the old Random Access
Iterator requirements would not necessarily be a model of Readable or
Writable Lvalue Iterator.  Instead we have chosen a design that
matches the preferred resolution of `issue 299`_: ``operator[]`` is
only required to return something convertible to the ``value_type``
(for a Readable Iterator), and is required to support assignment
``i[n] = t`` (for a Writable Iterator).


===============
 Proposed Text
===============

Addition to [lib.iterator.requirements]
=======================================

Iterator Value Access Concepts [lib.iterator.value.access]
++++++++++++++++++++++++++++++++++++++++++++++++++++++++++

In the tables below, ``X`` is an iterator type, ``a`` is a constant
object of type ``X``, ``T`` is
``std::iterator_traits<X>::value_type``, and ``v`` is a constant
object of type ``T``.

.. _Readable Iterator:

Readable Iterators [lib.readable.iterators]
-------------------------------------------

A class or built-in type ``X`` models the *Readable Iterator* concept
for the value type ``T`` if the following expressions are valid and
respect the stated semantics. ``U`` is the type of any specified
member of type ``T``.

 +-------------------------------------------------------------------------------------------------------------------+
 |Readable Iterator Requirements (in addition to CopyConstructible)                                                  |
 +--------------------------------------+----------------------------------+-----------------------------------------+
 |Expression                            |Return Type                       |Assertion/Note/Precondition/Postcondition|
 +======================================+==================================+=========================================+
 |``iterator_traits<X>::value_type``    |``T``                             |Any non-reference, non-cv-qualified type |
 +--------------------------------------+----------------------------------+-----------------------------------------+
 |``iterator_traits<X>::reference``     |Convertible to                    |                                         |
 |                                      |``iterator_traits<X>::value_type``|                                         |
 +--------------------------------------+----------------------------------+-----------------------------------------+
 |``access_category<X>::type``          |Convertible to                    |                                         |
 |                                      |``readable_iterator_tag``         |                                         |
 +--------------------------------------+----------------------------------+-----------------------------------------+
 |``*a``                                |``iterator_traits<X>::reference`` |pre: ``a`` is dereferenceable. If ``a == |
 |                                      |                                  |b`` then ``*a`` is equivalent to ``*b``  |
 +--------------------------------------+----------------------------------+-----------------------------------------+
 |``a->m``                              |``U&``                            |pre: ``(*a).m`` is well-defined.         |
 |                                      |                                  |Equivalent to ``(*a).m``                 |
 +--------------------------------------+----------------------------------+-----------------------------------------+


.. _Writable Iterator:

Writable Iterators [lib.writable.iterators]
-------------------------------------------

A class or built-in type ``X`` models the *Writable Iterator* concept
if the following expressions are valid and respect the stated
semantics.  In addition, a model of *Writable Iterator* must include
in its documentation the *set of value types* that it allows for
output.

 +---------------------------------------------------------------------------------------------+
 |Writable Iterator Requirements (in addition to CopyConstructible)                            |
 +--------------------------------------+-------------------------+----------------------------+
 |Expression                            |Return Type              |Precondition                |
 +======================================+=========================+============================+
 |``access_category<X>::type``          |Convertible to           |                            |
 |                                      |``writable_iterator_tag``|                            |
 +--------------------------------------+-------------------------+----------------------------+
 |``*a = o``                            |                         | pre: The type of ``o``     |
 |                                      |                         | is in the set of           |
 |                                      |                         | value types of ``X``       |
 +--------------------------------------+-------------------------+----------------------------+

   

Swappable Iterators [lib.swappable.iterators]
---------------------------------------------

A class or built-in type ``X`` models the *Swappable Iterator* concept
if the following expressions are valid and respect the stated
semantics.

 +------------------------------------------------------------------------------------------------+
 |Swappable Iterator Requirements (in addition to CopyConstructible)                              |
 +------------------------------------+-------------+---------------------------------------------+
 |Expression                          |Return Type  |Postcondition                                |
 +====================================+=============+=============================================+
 |``iter_swap(a, b)``                 |``void``     |post: the pointed to values are exchanged    |
 +------------------------------------+-------------+---------------------------------------------+

[*Note:* An iterator that is a model of the *Readable* and *Writable Iterator* concepts
  is also a model of *Swappable Iterator*.  *--end note*]


Readable Lvalue Iterators [lib.readable.lvalue.iterators]
---------------------------------------------------------

The *Readable Lvalue Iterator* concept adds the requirement that the
``reference`` type be a reference to the value type of the iterator.

 +----------------------------------------------------------------------------------------------------------+
 |Readable Lvalue Iterator Requirements (in addition to Readable Iterator)                                  |
 +------------------------------------+---------------------------------+-----------------------------------+
 |Expression                          |Return Type                      |Assertion                          |
 +====================================+=================================+===================================+
 |``iterator_traits<X>::reference``   |``T&``                           |``T`` is *cv*                      |
 |                                    |                                 |``iterator_traits<X>::value_type`` |
 |                                    |                                 |where *cv* is an optional          |
 |                                    |                                 |cv-qualification                   |
 +------------------------------------+---------------------------------+-----------------------------------+
 |``access_category<X>::type``        |Convertible to                   |                                   |
 |                                    |``readable_lvalue_iterator_tag`` |                                   |
 +------------------------------------+---------------------------------+-----------------------------------+


Writable Lvalue Iterators [lib.writable.lvalue.iterators]
---------------------------------------------------------

The *Writable Lvalue Iterator* concept adds the requirement that the
``reference`` type be a non-const reference to the value type of the
iterator.


 +--------------------------------------------------------------------------------------+                                             
 |   Writable Lvalue Iterator Requirements (in addition to Readable Lvalue Iterator)    |                                             
 +--------------------------------------+-----------------------------------------------+
 | Expression                           | Return Type                                   |
 +======================================+===============================================+
 |``iterator_traits<X>::reference``     |``iterator_traits<X>::value_type&``            |
 +--------------------------------------+-----------------------------------------------+
 |``access_category<X>::type``          |Convertible to ``writable_lvalue_iterator_tag``|
 |                                      |                                               |
 +--------------------------------------+-----------------------------------------------+


Iterator Traversal Concepts [lib.iterator.traversal]
++++++++++++++++++++++++++++++++++++++++++++++++++++

In the tables below, ``X`` is an iterator type, ``a`` and ``b`` are
constant objects of type ``X``, ``r`` and ``s`` are mutable objects of
type ``X``, ``T`` is ``std::iterator_traits<X>::value_type``, and
``v`` is a constant object of type ``T``.


Incrementable Iterators [lib.incrementable.iterators]
-----------------------------------------------------

A class or built-in type ``X`` models the *Incrementable Iterator*
concept if the following expressions are valid and respect the stated
semantics.


 +-------------------------------------------------------------------------------------------------------------------------+
 |Incrementable Iterator Requirements (in addition to Assignable, Copy Constructible)                                      |
 +--------------------------------+---------------------------------------------+------------------------------------------+
 |Expression                      |Return Type                                  |Assertion/Semantics                       |
 +================================+=============================================+==========================================+
 |``++r``                         |``X&``                                       |``&r == &++r``                            |
 +--------------------------------+---------------------------------------------+------------------------------------------+
 |``r++``                         |``X``                                        |``{ X tmp = r; ++r; return tmp; }``       |
 +--------------------------------+---------------------------------------------+------------------------------------------+
 |``traversal_category<X>::type`` |Convertible to ``incrementable_iterator_tag``|                                          |
 +--------------------------------+---------------------------------------------+------------------------------------------+


Single Pass Iterators [lib.single.pass.iterators]
-------------------------------------------------

A class or built-in type ``X`` models the *Single Pass Iterator*
concept if the following expressions are valid and respect the stated
semantics.


 +--------------------------------------------------------------------------------------------------------+
 |Single Pass Iterator Requirements (in addition to Incrementable Iterator and Equality Comparable)       |
 +----------------------------------+----------------------------+----------------------------------------+
 |Expression                        |Return Type                 |Assertion/Semantics/Pre-/Post-condition |
 +==================================+============================+========================================+
 |``++r``                           |``X&``                      |pre: ``r`` is dereferenceable; post:    |
 |                                  |                            |``r`` is dereferenceable or ``r`` is    |
 |                                  |                            |past-the-end                            | 
 +----------------------------------+----------------------------+----------------------------------------+
 |``a == b``                        |convertible to ``bool``     |``==`` is an equivalence relation over  |
 |                                  |                            |its domain                              |
 +----------------------------------+----------------------------+----------------------------------------+
 |``a != b``                        |convertible to ``bool``     |``!(a == b)``                           |
 +----------------------------------+----------------------------+----------------------------------------+
 |``traversal_category<X>::type``   |Convertible to              |                                        |
 |                                  |``single_pass_iterator_tag``|                                        |
 +----------------------------------+----------------------------+----------------------------------------+


Forward Traversal Iterators [lib.forward.traversal.iterators]
-------------------------------------------------------------

A class or built-in type ``X`` models the *Forward Traversal Iterator*
concept if the following expressions are valid and respect the stated
semantics.

 +------------------------------------------------------------------------------------------------------+
 |Forward Traversal Iterator Requirements (in addition to Single Pass Iterator)                         |
 +---------------------------------------+-------------------------------------+------------------------+
 |Expression                             |Return Type                          |Assertion/Note          |
 +=======================================+=====================================+========================+
 |``X u;``                               |``X&``                               |``note: u may have a    |
 |                                       |                                     |singular value.``       |
 +---------------------------------------+-------------------------------------+------------------------+
 |``++r``                                |``X&``                               |``r == s`` and ``r`` is |
 |                                       |                                     |dereferenceable implies |
 |                                       |                                     |``++r == ++s.``         |
 +---------------------------------------+-------------------------------------+------------------------+
 |``iterator_traits<X>::difference_type``|A signed integral type representing  |                        |
 |                                       |the distance between iterators       |                        |
 +---------------------------------------+-------------------------------------+------------------------+
 |``traversal_category<X>::type``        |Convertible to                       |                        |
 |                                       |``forward_traversal_iterator_tag``   |                        |
 +---------------------------------------+-------------------------------------+------------------------+


Bidirectional Traversal Iterators [lib.bidirectional.traversal.iterators]
-------------------------------------------------------------------------

A class or built-in type ``X`` models the *Bidirectional Traversal
Iterator* concept if the following expressions are valid and respect
the stated semantics.

 +----------------------------------------------------------------------------------------------------------------+
 |Bidirectional Traversal Iterator Requirements (in addition to Forward Traversal Iterator)                       |
 +-------------------------------+----------------------------------------+---------------------------------------+
 |Expression                     |Return Type                             |Assertion/Semantics/Pre-/Post-condition|
 +===============================+========================================+=======================================+
 |``--r``                        |``X&``                                  |pre: there exists ``s`` such that ``r  |
 |                               |                                        |== ++s``.  post: ``s`` is              |
 |                               |                                        |dereferenceable. ``--(++r) == r``.     |
 |                               |                                        |``--r == --s`` implies ``r == s``. ``&r|
 |                               |                                        |== &--r``.                             |
 +-------------------------------+----------------------------------------+---------------------------------------+
 |``r--``                        |convertible to ``const X&``             |``{ X tmp = r; --r; return tmp; }``    |
 |                               |                                        |                                       |
 |                               |                                        |                                       |
 +-------------------------------+----------------------------------------+---------------------------------------+
 |``traversal_category<X>::type``|Convertible to                          |                                       |
 |                               |``bidirectional_traversal_iterator_tag``|                                       |
 |                               |                                        |                                       |
 +-------------------------------+----------------------------------------+---------------------------------------+


Random Access Traversal Iterators [lib.random.access.traversal.iterators]
-------------------------------------------------------------------------

A class or built-in type ``X`` models the *Random Access Traversal
Iterator* concept if the following expressions are valid and respect
the stated semantics.  In the table below, ``Distance`` is
``iterator_traits<X>::difference_type`` and ``n`` represents a
constant object of type ``Distance``.

 +------------------------------------------------------------------------------------------------------------------------------+
 |Random Access Traversal Iterator Requirements (in addition to Bidirectional Traversal Iterator)                               |
 +--------------------------------+----------------------------------------+----------------------+-----------------------------+
 | Expression                     |Return Type                             | Operational Semantics|   Assertion/Precondition    |
 +================================+========================================+======================+=============================+
 |``r += n``                      |``X&``                                  |::                    |                             |
 |                                |                                        |                      |                             |
 |                                |                                        | {                    |                             |
 |                                |                                        |   Distance m = n;    |                             |
 |                                |                                        |   if (m >= 0)        |                             |
 |                                |                                        |     while (m--)      |                             |
 |                                |                                        |       ++r;           |                             |
 |                                |                                        |   else               |                             |
 |                                |                                        |     while (m++)      |                             |
 |                                |                                        |       --r;           |                             |
 |                                |                                        |   return r;          |                             |
 |                                |                                        | }                    |                             |
 +--------------------------------+----------------------------------------+----------------------+-----------------------------+
 |      ``a + n``, ``n + a``      |``X``                                   |``{ X tmp = a; return |                             |
 |                                |                                        |tmp += n; }``         |                             |
 +--------------------------------+----------------------------------------+----------------------+-----------------------------+
 |``r -= n``                      |``X&``                                  |``return r += -n``    |                             |
 +--------------------------------+----------------------------------------+----------------------+-----------------------------+
 |``a - n``                       |``X``                                   |``{ X tmp = a; return |                             |
 |                                |                                        |tmp -= n; }``         |                             |
 +--------------------------------+----------------------------------------+----------------------+-----------------------------+
 |``b - a``                       |``Distance``                            |``a < b ?             |pre: there exists a value    |
 |                                |                                        |distance(a,b) :       |``n`` of ``Distance`` such   |
 |                                |                                        |-distance(b,a)``      |that ``a + n == b``.  ``b == |
 |                                |                                        |                      |a + (b - a)``.               |
 +--------------------------------+----------------------------------------+----------------------+-----------------------------+
 |``a[n]``                        |convertible to T                        |``*(a + n)``          |pre: a is a `readable        |
 |                                |                                        |                      |iterator`_                   |
 +--------------------------------+----------------------------------------+----------------------+-----------------------------+
 |``a[n] = v``                    |convertible to T                        |``*(a + n) = v``      |pre: a is a `writable        |
 |                                |                                        |                      |iterator`_                   |
 +--------------------------------+----------------------------------------+----------------------+-----------------------------+
 |``a < b``                       |convertible to ``bool``                 |``b - a > 0``         |``<`` is a total ordering    |
 |                                |                                        |                      |relation                     |
 +--------------------------------+----------------------------------------+----------------------+-----------------------------+
 |``a > b``                       |convertible to ``bool``                 |``b < a``             |``>`` is a total ordering    |
 |                                |                                        |                      |relation                     |
 +--------------------------------+----------------------------------------+----------------------+-----------------------------+
 |``a >= b``                      |convertible to ``bool``                 |``!(a < b)``          |                             |
 +--------------------------------+----------------------------------------+----------------------+-----------------------------+
 |``a <= b``                      |convertible to ``bool``                 |``!(a > b)``          |                             |
 +--------------------------------+----------------------------------------+----------------------+-----------------------------+
 |``traversal_category<X>::type`` |Convertible to                          |                      |                             |
 |                                |``random_access_traversal_iterator_tag``|                      |                             |
 +--------------------------------+----------------------------------------+----------------------+-----------------------------+



Addition to [lib.iterator.synopsis]
===================================

::

  // lib.iterator.traits, traits and tags
  template <class Iterator> struct access_category;
  template <class Iterator> struct traversal_category;

  template <class AccessTag, class TraversalTag>
  struct iterator_tag : /* appropriate old category or categories */ {
    typedef AccessTag access;
    typedef TraversalTag traversal;
  };

  struct readable_iterator_tag { };
  struct writable_iterator_tag { };
  struct swappable_iterator_tag { };
  struct readable_writable_iterator_tag
    : virtual readable_iterator_tag
    , virtual writable_iterator_tag
    , virtual swappable_iterator_tag { };
  struct readable_lvalue_iterator_tag { };
  struct writable_lvalue_iterator_tag
    : virtual public readable_writable_iterator_tag
    , virtual public readable_lvalue_iterator_tag { };

  struct incrementable_iterator_tag { };
  struct single_pass_iterator_tag : incrementable_iterator_tag { };
  struct forward_traversal_tag : single_pass_iterator_tag { };
  struct bidirectional_traversal_tag : forward_traversal_tag { };
  struct random_access_traversal_tag : bidirectional_traversal_tag { };

  struct null_category_tag { };
  struct input_output_iterator_tag : input_iterator_tag, output_iterator_tag {};

Addition to [lib.iterator.traits]
=================================

The ``iterator_tag`` class template is an iterator category tag that
encodes the access and traversal tags in addition to being compatible
with the original iterator tags. The ``iterator_tag`` class inherits
from one of the original iterator tags according to the following
pseudo-code.

::

    inherit-category(access-tag, traversal-tag) =
         if (access-tag is convertible to readable_lvalue_iterator_tag) {
             if (traversal-tag is convertible to random_access_traversal_tag)
                 return random_access_iterator_tag;
             else if (traversal-tag is convertible to bidirectional_traversal_tag)
                 return bidirectional_iterator_tag;
             else if (traversal-tag is convertible to forward_traversal_tag)
                 return forward_iterator_tag;
             else if (traversal-tag is convertible to single_pass_traversal_tag)
                 if (access-tag is convertible to writable_iterator_tag)
                     return input_output_iterator_tag;
                 else
                     return input_iterator_tag;
             else if (access-tag is convertible to writable_iterator_tag)
                 return output_iterator_tag;
             else
                 return null_category_tag;
         } else if (access-tag is convertible to readable_writable_iterator_tag
                    and traversal-tag is convertible to single_pass_iterator_tag)
             return input_output_iterator_tag;
         else if (access-tag is convertible to readable_iterator_tag
                  and traversal-tag is convertible to single_pass_iterator_tag)
             return input_iterator_tag;
         else if (access-tag is convertible to writable_iterator_tag
                  and traversal-tag is convertible to incrementable_iterator_tag)
             return output_iterator_tag;
         else
             return null_category_tag;
     

The ``access_category`` and ``traversal_category`` class templates are
traits classes. For iterators whose
``iterator_traits<Iter>::iterator_category`` type is ``iterator_tag``,
the ``access_category`` and ``traversal_category`` traits access the
``access`` and ``traversal`` member types within ``iterator_tag``.
For iterators whose ``iterator_traits<Iter>::iterator_category`` type
is not ``iterator_tag`` and instead is a tag convertible to one of the
original tags, the appropriate traversal and access tags is deduced.
The following pseudo-code describes the algorithm.

::

  access-category(Iterator) =
      cat = iterator_traits<Iterator>::iterator_category;
      if (cat == iterator_tag<Access,Traversal>)
          return Access;
      else if (cat is convertible to forward_iterator_tag) {
          if (iterator_traits<Iterator>::reference is a const reference)
              return readable_lvalue_iterator_tag;
          else
              return writable_lvalue_iterator_tag;
      } else if (cat is convertible to input_iterator_tag)
          return readable_iterator_tag;
      else if (cat is convertible to output_iterator_tag)
          return writable_iterator_tag;
      else
          return null_category_tag;

  traversal-category(Iterator) =
      cat = iterator_traits<Iterator>::iterator_category;
      if (cat == iterator_tag<Access,Traversal>)
          return Traversal;
      else if (cat is convertible to random_access_iterator_tag)
          return random_access_traversal_tag;
      else if (cat is convertible to bidirectional_iterator_tag)
          return bidirectional_traversal_tag;
      else if (cat is convertible to forward_iterator_tag)
          return forward_traversal_tag;
      else if (cat is convertible to input_iterator_tag)
          return single_pass_iterator_tag;
      else if (cat is convertible to output_iterator_tag)
          return incrementable_iterator_tag;
      else
          return null_category_tag;


The following specializations provide the access and traversal
category tags for pointer types.

::

  template <typename T>
  struct access_category<const T*>
  {
    typedef readable_lvalue_iterator_tag type;
  };
  template <typename T>
  struct access_category<T*>
  {
    typedef writable_lvalue_iterator_tag type;
  };

  template <typename T>
  struct traversal_category<T*>
  {
    typedef random_access_traversal_tag type;
  };



..
 LocalWords:  Abrahams Siek Witt const bool Sutter's WG int UL LI href Lvalue
 LocalWords:  ReadableIterator WritableIterator SwappableIterator cv pre iter
 LocalWords:  ConstantLvalueIterator MutableLvalueIterator CopyConstructible TR
 LocalWords:  ForwardTraversalIterator BidirectionalTraversalIterator lvalue
 LocalWords:  RandomAccessTraversalIterator dereferenceable Incrementable tmp
 LocalWords:  incrementable xxx min prev inplace png oldeqnew AccessTag struct
 LocalWords:  TraversalTag typename lvalues DWA Hmm JGS
