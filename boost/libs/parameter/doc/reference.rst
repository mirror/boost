+++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++
 The Boost Parameter Library Reference Documentation 
+++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++

|(logo)|__

.. |(logo)| image:: ../../../../boost.png
   :alt: Boost

__ ../../../../index.htm

:Authors:       David Abrahams, Daniel Wallin
:Contact:       dave@boost-consulting.com, dalwan01@student.umu.se
:organization:  `Boost Consulting`_
:date:          $Date: 2005/07/17 19:53:01 $

:copyright:     Copyright David Abrahams, Daniel Wallin
                2005. Distributed under the Boost Software License,
                Version 1.0. (See accompanying file LICENSE_1_0.txt
                or copy at http://www.boost.org/LICENSE_1_0.txt)

.. _`Boost Consulting`: http://www.boost-consulting.com

//////////////////////////////////////////////////////////////////////////////

.. contents::
    :depth: 2

//////////////////////////////////////////////////////////////////////////////

.. role:: class
    :class: class

.. role:: concept
    :class: concept

.. role:: function
    :class: function

.. |ArgumentPack| replace:: :concept:`ArgumentPack`
.. |ParameterSpec| replace:: :concept:`ParameterSpec`


.. class:: reference

.. role:: large
   :class: doublesize

.. section-numbering::
    :depth: 2

Preliminaries
=============

This section covers some basic information you'll need to know in
order to understand this reference

Namespaces
----------

In this document, all identifiers will be written as if the
namespace alias ::

  namespace parameter = boost::parameter;

is in force: we'll write ``parameter::xxx`` instead of
``boost::parameter::xxx``.

Exceptions
----------

No operation described in this document
throws an exception unless otherwise specified.

Typography
----------

Names written in :concept:`sans serif type` represent concepts_.

In code blocks, *italic type* represents unspecified text that
satisfies the requirements given in the detailed description that
follows the code block.

//////////////////////////////////////////////////////////////////////////////

Terminology
===========

.. |kw| replace:: keyword
.. _kw:

keyword
  The name of a function parameter.

.. _keyword tag type:
.. |keyword tag type| replace:: `keyword tag type`_

keyword tag type
  A type used to uniquely identify a function parameter.  Typically
  its name will be the same as that of the parameter.

.. _tag type:
.. |tag type| replace:: `tag type`_

tag type
  Shorthand for “\ |keyword tag type|.”

.. _keyword object:
.. |keyword object| replace:: `keyword object`_

keyword object
  An instance of ``parameter::``\ |keyword|_ ``<T>`` for some |tag
  type| ``T``.

.. _tagged reference:
.. |tagged reference| replace:: `tagged reference`_

tagged reference
  An object whose type is associated with a |keyword tag type| (the
  object's *keyword*), and that holds a reference (to the object's
  *value*).

  As a shorthand, a “tagged reference to ``x``\ ” means a tagged
  reference whose *value* is ``x``.

.. _tagged default:
.. |tagged default| replace:: `tagged default`_

tagged default 
  A |tagged reference| whose *value* represents the value of a
  default argument. 

.. _tagged lazy default:
.. |tagged lazy default| replace:: `tagged lazy default`_

tagged lazy default 
  A |tagged reference| whose *value*, when invoked with no
  arguments, computes a default argument value.


//////////////////////////////////////////////////////////////////////////////

Concepts
========

This section describes the generic type concepts_ used by the Parameter library. 

.. _concepts: ../../../../more/generic_programming.html#concept

|ArgumentPack|
--------------

An |ArgumentPack| is a collection of |tagged reference|\ s to the
actual arguments passed to a function.

Requirements
............

In the table below, 

* ``A`` is a model of |ArgumentPack|
* ``x`` is an instance of ``A``
* ``u`` is a |keyword object| of type ``K``
* ``v`` is a |tagged default| with |tag type| ``L`` and *value* of type ``D``
* ``w`` is a |tagged lazy default| with |tag type| ``M`` and *value* of type ``E const``
* ``z`` is an |ArgumentPack| containing a single element (as created by |keyword|_\ ``<…>::operator=``)

Any exceptions are thrown from the invocation of ``w``\ 's *value*
will be propagated to the caller.

+----------+----------------------------------------+------------------+--------------------------------------+
|Expression| Type                                   |Requirements      |Semantics/Notes                       |
+==========+========================================+==================+======================================+
|``x[u]``  |``parameter::binding<A,K>::type``       |``x`` contains an |Returns *b*\ 's *value* (by           |
|          |                                        |element *b* whose |reference).                           |
|          |                                        ||kw|_ is ``K``    |                                      |
+----------+----------------------------------------+------------------+--------------------------------------+
|``x[u]``  |``prameter::binding<A,L,D>::type``      |*none*            |If ``x`` contains an element *b* whose|
|          |                                        |                  ||kw|_ is the same as ``u``\ 's,       |
|          |                                        |                  |returns *b*\ 's *value* (by           |
|          |                                        |                  |reference).  Otherwise, returns ``u``\|
|          |                                        |                  |'s *value*.                           |
+----------+----------------------------------------+------------------+--------------------------------------+
|``x[w]``  |``parameter::lazy_binding<A,M,E>::type``|*none*            |If ``x`` contains an element *b* whose|
|          |                                        |                  ||kw|_ is the same as ``w``\ 's,       |
|          |                                        |                  |returns *b*\ 's *value* (by           |
|          |                                        |                  |reference).  Otherwise, invokes ``w``\|
|          |                                        |                  |'s *value* and returns the result.    |
+----------+----------------------------------------+------------------+--------------------------------------+
|``x, z``  |Model of |ArgumentPack|                 |*none*            |Returns an |ArgumentPack|_ containing |
|          |                                        |                  |all the elements of both ``x`` and    |
|          |                                        |                  |``z``.                                |
+----------+----------------------------------------+------------------+--------------------------------------+


.. class:: reference


.. _parameterspec:

|ParameterSpec|
---------------

A |ParameterSpec| describes the type requirements for arguments
corresponding to a given |kw|_ and indicates whether the argument
is optional or required.  It takes one of the following forms; in
each case ``T`` is the |ParameterSpec|\ 's  |keyword tag type|:

+------------------------+--------------------------------------+------------------------+
|Type                    |Requirements on Argument Type ``A``   |Argument is Required?   |
+========================+======================================+========================+
|``parameter::``\        |*none*                                |no                      |
||keyword|_\ ``<T>``     |                                      |                        |
+------------------------+--------------------------------------+------------------------+
|``parameter::``\        |``mpl::apply<F,A>::type::value`` is   |no                      |
||optional|_\ ``<T,F>``  |``true``.                             |                        |
+------------------------+--------------------------------------+------------------------+
|``parameter::``\        |``mpl::apply<F,A>::type::value`` is   |yes                     |
||required|_\ ``<T,F>``  |``true``.                             |                        |
+------------------------+--------------------------------------+------------------------+

The information in a |ParameterSpec| is used to `limit`__ the
arguments that will be matched by `forwarding functions`_.  

__ index.html#controlling-overload-resolution

.. _forwarding functions: index.html#forwarding-functions


//////////////////////////////////////////////////////////////////////////////

Class Templates
===============

.. |keyword| replace:: ``keyword``
.. _keyword:

``keyword``
-----------

**Defined in**
    `boost/parameter/keyword.hpp`__

__ ../../../../boost/parameter/keyword.hpp

.. parsed-literal::

    template <class Tag>
    struct keyword
    {
        template <class T>
        |ArgumentPack|_ `operator=`_\(T& value) const;

        template <class T>
        |ArgumentPack|_ `operator=`_\(T const& value) const;

        template <class T>
        *tagged default* `operator|`_\(T& x) const;

        template <class T>
        *tagged default* `operator|`_\(T const& x) const;

        template <class F>
        *tagged lazy default* `operator||`_\(F const&) const;
    };


``operator=``
.............

.. parsed-literal::

    template <class T> |ArgumentPack|_ operator=(T& value) const;
    template <class T> |ArgumentPack|_ operator=(T const& value) const;

:Requires: nothing

:Returns:
    an |ArgumentPack|_  containing a single |tagged reference| to
    ``value`` with |kw|_ ``Tag`` 

operator|
.........

.. parsed-literal::

    template <class T> *tagged default* operator|(T& x) const;
    template <class T> *tagged default* operator|(T const& x) const;

:Returns: a |tagged default| with *value* ``x`` and |kw|_ ``Tag``.

operator||
..........

.. parsed-literal::

    template <class F> *tagged lazy default* operator||(F const& g) const;

:Requires: ``g()`` is well-formed.  If |BOOST_NO_RESULT_OF|_ is
  not ``#defined``, its type must be
  ``boost::result_of<F()>::type``.  Otherwise, it must be
  ``F::result_type``.

.. |BOOST_NO_RESULT_OF| replace:: ``BOOST_NO_RESULT_OF``
.. _BOOST_NO_RESULT_OF: ../../../utility/utility.htm#BOOST_NO_RESULT_OF
 
:Returns: a |tagged lazy default| with *value* ``g`` and |kw|_ ``Tag``.


.. class:: reference

.. _parameters:

``parameters``
--------------

**Defined in**
    `boost/parameter/parameters.hpp`__

__ ../../../../boost/parameter/parameters.hpp

.. parsed-literal::

    template <class P0, class P1, …, class PN>
    struct parameters
    {
        template <class T0, class T1, …, class TN>
        struct `match`_
        {
            typedef … type;
        };

        template <class A0>
        *unspecified model of* |ArgumentPack| `operator()`_\(A0 const& a0) const;

        template <class A0, class A1>
        *unspecified model of* |ArgumentPack| `operator()`_\(A0 const& a0, A1 const& a1) const;

        template <class A0, class A1, …, class AN>
        *unspecified model of* |ArgumentPack| `operator()`_\(A0 const& a0, A1 const& a1, …, AN const& aN) const;
    };


Template Parameter Semantics
............................

``<P0, …, PN>`` are models of |ParameterSpec|_. If ``Px`` is not an
instance of either ``optional`` or ``required``, it is treated as a
keyword tag with the same meaning as ``optional<Px>``.

``<P0, …, PN>`` determine the positional meaning of the parameters,
and the type requirements for passed arguments.


match
.....

Used to remove a function from overload resolution using SFINAE.

.. parsed-literal::

        template <class T0, class T1, …, class TN> struct restrict { typedef … type; };

**Returns**
    If the supplied argument types ``<T0, …, TN>`` fulfill the requirments of the
    specified |ParameterSpec|_'s, ``match<T0, …, TN>::type`` exists and is constructible
    from ``parameters<P0, …, PN>``. Otherwise ``restrict<T0, …, TN>::type`` doesn't exist.

    The algorithm that determines if the type requirements are fulfilled works
    like this::

        If Px is optional<K, P>
            If a bound argument Tx tagged with K exists in <T0, …, TN>
                return P<type of argument bound in Tx>::type
            Else
                return mpl::true_
        Else if Px is required<K, P>
            If a bound argument Tx tagged with K exists in <T0, …, TN>
                return P<type of argument bound in Tx>::type
            Else
                return mpl::false_
        Else
            return mpl::true_


operator()
..........

.. parsed-literal::

    template <class A0> *unspecified model of* |ArgumentPack|_ operator()(A0 const& a0) const;
    template <class A0, class A1> *unspecified model of* |ArgumentPack|_ operator()(A0 const& a0, A1 const& a1) const;
    …

**Throws**
    Nothing

**Returns**
    A composite |ArgumentPack|_ containing all arguments ``<A0, …, AN>``.
    If ``Ax`` is not a model of |ArgumentPack|_, it is transformed into one
    by tagging the argument with the |ParameterSpec|_ ``Px`` in it's position.



.. class:: reference

.. |optional| replace:: ``optional``
.. |required| replace:: ``required``

.. _optional:
.. _required:

``optional``, ``required``
--------------------------

**Specializations models**
    |ParameterSpec|_

**Defined in**
    `boost/parameter/parameters.hpp`__

__ ../../../../boost/parameter/parameters.hpp

.. parsed-literal::

    template <class Tag, class Predicate = *unspecified*>
    struct optional;

    template <class Tag, class Predicate = *unspecified*>
    struct required;

The default value of ``Predicate`` is an unspecified |Metafunction|_ that returns
``mpl::true_`` for any argument.

.. |Metafunction| replace:: :concept:`Metafunction`
.. _Metafunction: ../../../mpl/doc/refmanual/metafunction.html

//////////////////////////////////////////////////////////////////////////////

Metafunctions
=============



.. class:: reference

.. _binding:

``binding``
-----------

**Defined in**
    `boost/parameter/binding.hpp`__

__ ../../../../boost/parameter/binding.hpp

A |Metafunction|_ that, given an |ArgumentPack|_, returns the reference
type of the parameter identified by ``Keyword``.  If no such parameter has been
specified, returns ``Default``.

.. parsed-literal::

    template <class Parameters, class Keyword, class Default = *unspecified*>
    struct binding
    {
        typedef … type;
    };


.. class:: reference



.. _lazy_binding:

``lazy_binding``
----------------

**Defined in**
    `boost/parameter/binding.hpp`__

__ ../../../../boost/parameter/binding.hpp

A metafunction that, given an |ArgumentPack|_, returns the reference
type of the parameter identified by ``Keyword``.  If no such parameter has been
specified, returns the type returned by invoking ``DefaultFn``.

.. parsed-literal::

    template <class Parameters, class Keyword, class DefaultFn>
    struct lazy_binding
    {
        typedef … type;
    };

Requirements 
............ 

``DefaultFn`` is a nullary function object. The type returned by invoking this
function is determined by ``boost::result_of<DefaultFn()>::type`` on compilers
that support partial specialization. On less compliant compilers a nested
``DefaultFn::result_type`` is used instead.


.. class:: reference

//////////////////////////////////////////////////////////////////////////////

Macros
======



``BOOST_PARAMETER_KEYWORD``
---------------------------------

**Defined in**
    `boost/parameter/keyword.hpp`__

__ ../../../../boost/parameter/keyword.hpp

Macro used to define `keyword objects`__.

__ `keyword object`_

.. parsed-literal::

    BOOST_PARAMETER_KEYWORD(tag_namespace, name)

Requirements
............

* ``tag_namespace`` is the namespace where the tag-types will be placed.
* ``name`` is the name that will be used for the keyword.


.. class:: reference



``BOOST_PARAMETER_FUN``
-----------------------------

**Defined in**
    `boost/parameter/macros.hpp`__

__ ../../../../boost/parameter/macros.hpp

.. parsed-literal::

    BOOST_PARAMETER_FUN(ret, name, lo, hi, parameters)

``BOOST_PARAMETER_MAX_ARITY``
-----------------------------

Requirements
............

* ``ret`` is the return type of the function.
* ``name`` is the name of the function.
* ``lo``, ``hi`` defines the range of arities for the function.
* ``parameters`` is the name of the ``parameters<>`` instance
  used for the function.

