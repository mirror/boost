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

In this document, all unqualified identifiers should be assumed to
be defined in namespace ``boost::parameter`` unless otherwise
specified.

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

The special character β represents the value of |BOOST_PARAMETER_MAX_ARITY|_.

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

.. _positional:
.. |positional| replace:: `positional`_

positional argument
  An argument passed with no explicit |kw|.  Its parameter is
  determined in the usual C++ way: by position with respect to a
  parameter list.

.. _tag type:
.. |tag type| replace:: `tag type`_

tag type
  Shorthand for “\ |keyword tag type|.”

.. _keyword object:
.. |keyword object| replace:: `keyword object`_

keyword object
  An instance of |keyword|_ ``<T>`` for some |tag
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

.. _intended argument type:
.. |intended argument type| replace:: `intended argument type`_

intended argument type
  The *intended argument type* of a single-element |ArgumentPack|_ is the
  type of its element's *value*.  The intended argument type of any other
  type ``X`` is ``X`` itself.

.. Note::

   In this reference, we will use concept names (and other names)
   to describe both types and objects, depending on context.  So
   for example, “an |ArgumentPack|_\ ” can refer to a type that
   models |ArgumentPack|_ *or* an object of such a type. 

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

.. table:: |ArgumentPack| requirements

   +----------+-----------------------------+------------------+--------------------------------------+
   |Expression| Type                        |Requirements      |Semantics/Notes                       |
   +==========+=============================+==================+======================================+
   |``x[u]``  |``binding<A,K>::type``       |``x`` contains an |Returns *b*\ 's *value* (by           |
   |          |                             |element *b* whose |reference).                           |
   |          |                             ||kw|_ is ``K``    |                                      |
   +----------+-----------------------------+------------------+--------------------------------------+
   |``x[u]``  |``binding<A,L,D>::type``     |*none*            |If ``x`` contains an element *b* whose|
   |          |                             |                  ||kw|_ is the same as ``u``\ 's,       |
   |          |                             |                  |returns *b*\ 's *value* (by           |
   |          |                             |                  |reference).  Otherwise, returns ``u``\|
   |          |                             |                  |'s *value*.                           |
   +----------+-----------------------------+------------------+--------------------------------------+
   |``x[w]``  |``lazy_binding<A,M,E>::type``|*none*            |If ``x`` contains an element *b* whose|
   |          |                             |                  ||kw|_ is the same as ``w``\ 's,       |
   |          |                             |                  |returns *b*\ 's *value* (by           |
   |          |                             |                  |reference).  Otherwise, invokes ``w``\|
   |          |                             |                  |'s *value* and returns the result.    |
   +----------+-----------------------------+------------------+--------------------------------------+
   |``x, z``  |Model of |ArgumentPack|      |*none*            |Returns an |ArgumentPack|_ containing |
   |          |                             |                  |all the elements of both ``x`` and    |
   |          |                             |                  |``z``.                                |
   +----------+-----------------------------+------------------+--------------------------------------+



.. _parameterspec:

|ParameterSpec|
---------------

A |ParameterSpec| describes the type requirements for arguments
corresponding to a given |kw|_ and indicates whether the argument
is optional or required.  The table below details the allowed forms
and describes their condition for satisfaction by an actual
argument type. In each row,

.. _conditions:

* ``K`` is the |ParameterSpec|\ 's |keyword tag type|
* ``A`` is an |intended argument type| associated with ``K``, if any
* ``F`` is a unary `MPL lambda expression`_

.. _`MPL lambda expression`: ../../../mpl/doc/refmanual/lambda-expression.html

.. table:: |ParameterSpec| allowed forms and conditions of satisfaction

   +----------------------+--------------+--------------------------------+
   |Type                  |``A`` required|Condition ``A`` must satisfy    |
   +======================+==============+================================+
   ||keyword|_\ ``<K>``   |no            |*n/a*                           |
   +----------------------+--------------+--------------------------------+
   ||optional|_\ ``<K,F>``|no            |``mpl::apply<F,A>::type::value``|
   |                      |              |is ``true``.                    |
   +----------------------+--------------+--------------------------------+
   ||required|_\ ``<K,F>``|yes           |``mpl::apply<F,A>::type::value``|
   |                      |              |is ``true``.                    |
   +----------------------+--------------+--------------------------------+

The information in a |ParameterSpec| is used to `limit`__ the
arguments that will be matched by `forwarding functions`_.  

__ overloadcontrol_
.. _overloadcontrol: index.html#controlling-overload-resolution
.. _forwarding functions: index.html#forwarding-functions


//////////////////////////////////////////////////////////////////////////////

Class Templates
===============

.. |keyword| replace:: ``keyword``
.. _keyword:

``keyword``
-----------

The type of every |keyword object| is a specialization of |keyword|.

:Defined in: `boost/parameter/keyword.hpp`__

__ ../../../../boost/parameter/keyword.hpp

.. parsed-literal::

    template <class Tag>
    struct keyword
    {
        template <class T> |ArgumentPack|_ `operator=`_\(T& value) const;
        template <class T> |ArgumentPack|_ `operator=`_\(T const& value) const;

        template <class T> *tagged default* `operator|`_\(T& x) const;
        template <class T> *tagged default* `operator|`_\(T const& x) const;

        template <class F> *tagged lazy default* `operator||`_\(F const&) const;
    };


.. |operator=| replace:: ``operator=``
.. _operator=:

``operator=``
  .. parsed-literal::

      template <class T> |ArgumentPack|_ operator=(T& value) const;
      template <class T> |ArgumentPack|_ operator=(T const& value) const;

  :Requires: nothing

  :Returns:
      an |ArgumentPack|_  containing a single |tagged reference| to
      ``value`` with |kw|_ ``Tag`` 

.. _operator|:

``operator|``
  .. parsed-literal::

      template <class T> *tagged default* operator|(T& x) const;
      template <class T> *tagged default* operator|(T const& x) const;

  :Returns: a |tagged default| with *value* ``x`` and |kw|_ ``Tag``.

.. _operator||:

operator||
  .. parsed-literal::

      template <class F> *tagged lazy default* operator||(F const& g) const;

  :Requires: ``g()`` is well-formed.  If |BOOST_NO_RESULT_OF|_ is
    not ``#defined``, its type must be
    ``boost::result_of<F()>::type``.  Otherwise, it must be
    ``F::result_type``.

  .. |BOOST_NO_RESULT_OF| replace:: ``BOOST_NO_RESULT_OF``
  .. _BOOST_NO_RESULT_OF: ../../../utility/utility.htm#BOOST_NO_RESULT_OF

  :Returns: a |tagged lazy default| with *value* ``g`` and |kw|_ ``Tag``.


.. _parameters:

``parameters``
--------------

Provides an interface for assembling the actual arguments to a
`forwarding function` into an |ArgumentPack|, in which any
|positional| arguments will be tagged according to the
corresponding template argument to ``parameters``.  

.. _forwarding function: `forwarding functions`_

:Defined in: `boost/parameter/parameters.hpp`__

__ ../../../../boost/parameter/parameters.hpp

.. parsed-literal::

    template <class P0 = *unspecified*, class P1 = *unspecified*, …class P\ β = *unspecified*>
    struct parameters
    {
        template <class A0, class A1 = *unspecified*, …class A\ β = *unspecified*>
        struct `match`_
        {
            typedef … type;
        };

        template <class A0>
        |ArgumentPack| `operator()`_\(A0 const& a0) const;

        template <class A0, class A1>
        |ArgumentPack| `operator()`_\(A0 const& a0, A1 const& a1) const;
           :large:`⋮`
        template <class A0, class A1, …class A\ β>
        |ArgumentPack| `operator()`_\(A0 const& a0, A1 const& a1, …A\ β const& a\ β) const;
    };


:Requires: ``P0``, ``P1``, … ``P``\ β are models of |ParameterSpec|_. 


.. Note::

  In this section, ``R``\ *i* and ``K``\ *i* are defined as
  follows, for any argument type ``A``\ *i*:


     | ``R``\ *i* is ``A``\ *i*\ 's |intended argument type|
     |
     |  if ``A``\ *i* is a result type of ``keyword<T>::``\ |operator=|_
     |  then 
     |      ``K``\ *i* is ``T``
     |  else 
     |      ``K``\ *i* is ``P``\ *i*\ 's |keyword tag type|.


.. _match:

``match``
  A |Metafunction|_ used to remove a `forwarding function`_ from overload resolution.

  :Returns: if ``P0``, ``P1``, …\ ``P``\ β are *satisfied* (see
    below), then ``parameters<P0,P1,…Pβ>``.  Otherwise,
    ``match<A0,A1,…Aβ>::type`` is not defined.

  ``P0``, ``P1``, …\ ``P``\ β are **satisfied** if, for
  every *j* in 0…β, either:

  * ``P``\ *j* is the *unspecified* default
  * **or**, ``P``\ *j* is a specialization of |keyword|_,

  * **or**, ``P``\ *j* is |optional|_ ``<X,F>`` and either

    - ``X`` is not ``K``\ *i* for any *i*,
    - **or** ``X`` is some ``K``\ *i*  and ``mpl::apply<F,R``\ *i*\
      ``>::type::value`` is ``true``

  * **or**, ``P``\ *j* is |required|_ ``<X,F>``, and

    - ``X`` is some ``K``\ *i*, **and**
    - ``mpl::apply<F,R``\ *i*\ ``>::type::value`` is ``true``

.. _operator():

``operator()``
  .. parsed-literal::

      template <class A0> |ArgumentPack|_ operator()(A0 const& a0) const;
         :large:`⋮`
      template <class A0, …class A\ β> |ArgumentPack| `operator()`_\(A0 const& a0, …A\ β const& a\ β) const;

  :Returns:
      An |ArgumentPack|_ containing, for each ``a``\ *i*,  

      - if ``a``\ *i*,  is a single-element |ArgumentPack|, its element
      - Otherwise, a |tagged reference| with |kw|_ ``K``\ *i* and *value* ``a``\ *i*


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

.. |BOOST_PARAMETER_MAX_ARITY| replace:: ``BOOST_PARAMETER_MAX_ARITY``
