+++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++
 The Boost Parameter Library Reference Documentation |(logo)|__
+++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++

.. |(logo)| image:: ../../../../boost.png
   :alt: Boost

__ ../../../../index.htm

:Authors:       David Abrahams, Daniel Wallin
:Contact:       dave@boost-consulting.com, dalwan01@student.umu.se
:organization:  `Boost Consulting`_
:date:          $Date: 2005/07/15 18:43:59 $

:copyright:     Copyright David Abrahams, Daniel Wallin
                2005. Distributed under the Boost Software License,
                Version 1.0. (See accompanying file LICENSE_1_0.txt
                or copy at http://www.boost.org/LICENSE_1_0.txt)

.. _`Boost Consulting`: http://www.boost-consulting.com

.. contents::
    :depth: 1

//////////////////////////////////////////////////////////////////////////////

.. role:: class
    :class: class

.. role:: concept
    :class: concept

.. role:: function
    :class: function

.. |ArgumentPack| replace:: :concept:`ArgumentPack`
.. |KeywordExpression| replace:: :concept:`KeywordExpression`
.. |KeywordDefaultExpression| replace:: :concept:`KeywordDefaultExpression`
.. |ParameterSpec| replace:: :concept:`ParameterSpec`


.. class:: reference

class template :class:`keyword`
------------------------------------

**Defined in**
    `boost/parameter/keyword.hpp`__

__ ../../../../boost/parameter/keyword.hpp

**Models**
    :concept:`IndexExpression`

.. parsed-literal::

    template <class Tag>
    struct keyword
    {
        template <class T>
        |ArgumentPack| `operator=`_\(T& value) const;

        template <class T>
        |ArgumentPack| `operator=`_\(T const& value) const;

        template <class T>
        |ArgumentPack| `operator|`_\(T& default\_) const;

        template <class T>
        |KeywordDefaultExpression| `operator|`_\(T const& default\_) const;

        template <class F>
        |KeywordDefaultExpression| `operator||`_\(F const&) const;
    };


operator=
~~~~~~~~~

.. parsed-literal::

    template <class T> |ArgumentPack| operator=(T& value) const;
    template <class T> |ArgumentPack| operator=(T const& value) const;

**Requires**
    Nothing.

**Throws**
    Nothing

**Returns**
    A model of |ArgumentPack|, holding a *cv* reference to ``value``,
    tagged with ``Tag``.


operator|
~~~~~~~~~

.. parsed-literal::

    template <class T> |KeywordDefaultExpression| operator|(T& default\_) const;
    template <class T> |KeywordDefaultExpression| operator|(T const& default\_) const;

**Throws**
    Nothing

**Returns**
    An object that models KeywordDefaultExpression, that when used as
    an argument to ``ArgumentPack::operator[]`` which doesn't contain
    a parameter specified with ``Tag`` returns a reference to ``default_``.


operator||
~~~~~~~~~~

.. parsed-literal::

    template <class F> |KeywordDefaultExpression| operator||(F const& fn) const;

**Throws**
    Nothing

**Requires**
    ``F`` is a nullary function object.

    **On compilers that support partial specialization:**

    +---------------------------------+-----------------------------------------------------+
    | Expression                      | Requirement                                         |
    +=================================+=====================================================+
    | ``boost::result_of<F()>::type`` | :concept:`CopyConstructible`                        |
    +---------------------------------+-----------------------------------------------------+
    | ``fn()``                        | Convertible to ``boost::result_of<F()>::type``      |
    +---------------------------------+-----------------------------------------------------+

    **On compilers that doesn't support partial specialization:**

    +------------------------------+-----------------------------------------------------+
    | Expression                   | Requirement                                         |
    +==============================+=====================================================+
    | ``F::result_type``           | :concept:`CopyConstructible`                        |
    +------------------------------+-----------------------------------------------------+
    | ``fn()``                     | Convertible to ``F::result_type``                   |
    +------------------------------+-----------------------------------------------------+

**Returns**
    An object that models |KeywordDefaultExpression|, that when used as
    an argument to ``ArgumentPack::operator[]`` which doesn't contain
    a parameter specified with ``Tag`` evaluates and returns ``fn()``.


//////////////////////////////////////////////////////////////////////////////

.. class:: reference

class template :class:`parameters`
---------------------------------------------------

**Defined in**
    `boost/parameter/parameters.hpp`__

__ ../../../../boost/parameter/parameters.hpp

.. parsed-literal::

    template <class P0, class P1, …, class PN>
    struct parameters
    {
        template <class T0, class T1, …, class TN>
        struct `restrict`_
        {
            typedef … type;
        };

        template <class A0>
        |ArgumentPack| `operator()`_\(A0 const& a0) const;

        template <class A0, class A1>
        |ArgumentPack| `operator()`_\(A0 const& a0, A1 const& a1) const;

        template <class A0, class A1, …, class AN>
        |ArgumentPack| `operator()`_\(A0 const& a0, A1 const& a1, …, AN const& aN) const;
    };


Template Parameter Semantics
~~~~~~~~~~~~~~~~~~~~~~~~~~~~

``<P0, …, PN>`` are models of |ParameterSpec|.


restrict
~~~~~~~~

Used to remove a function from overload resolution using SFINAE.

.. parsed-literal::

        template <class T0, class T1, …, class TN> struct restrict { typedef … type; };

**Returns**
    If the supplied argument types ``<T0, …, TN>`` fulfill the requirments of the
    specified |ParameterSpec|'s, ``restrict<T0, …, TN>::type`` exists and is constructible 
    from ``parameters<P0, …, PN>``. Otherwise ``restrict<T0, …, TN>::type`` doesn't exist.


operator()
~~~~~~~~~~

.. parsed-literal::

    template <class A0> |ArgumentPack| operator()(A0 const& a0) const;
    template <class A0, class A1> |ArgumentPack| operator()(A0 const& a0, A1 const& a1) const;
    …

**Throws**
    Nothing

**Returns**
    A composite |ArgumentPack| containing all arguments ``<A0, …, AN>``.
    If ``Ax`` is not a model of |ArgumentPack|, it is transformed into one
    by tagging the argument with the |ParameterSpec| ``Px`` in it's position.


//////////////////////////////////////////////////////////////////////////////

.. class:: reference

class templates :class:`optional`, :class:`required`
----------------------------------------------------

**Models**
    |ParameterSpec|

**Defined in**
    `boost/parameter/parameters.hpp`__

__ ../../../../boost/parameter/parameters.hpp

.. parsed-literal::

    template <class Tag, class Predicate = *unspecified*>
    struct optional;

    template <class Tag, class Predicate = *unspecified*>
    struct required;


//////////////////////////////////////////////////////////////////////////////

.. class:: reference

class template :class:`binding`
-------------------------------------------------------------

**Defined in**
    `boost/parameter/binding.hpp`__

__ ../../../../boost/parameter/binding.hpp

A metafunction that, given an :concept:`ArgumentTuple`, returns the reference
type of the parameter identified by ``Keyword``.  If no such parameter has been
specified, returns ``Default``.

.. parsed-literal::

    template <class Parameters, class Keyword, class Default = *unspecified*>
    struct binding
    {
        typedef … type;
    };


.. class:: reference


//////////////////////////////////////////////////////////////////////////////

class template :class:`lazy_binding`
------------------------------------------------------------------

**Defined in**
    `boost/parameter/binding.hpp`__

__ ../../../../boost/parameter/binding.hpp

A metafunction that, given an |ArgumentPack|, returns the reference
type of the parameter identified by ``Keyword``.  If no such parameter has been
specified, returns the type returned by invoking ``DefaultFn``.

.. parsed-literal::

    template <class Parameters, class Keyword, class DefaultFn>
    struct lazy_binding
    {
        typedef … type;
    };

Requirements 
~~~~~~~~~~~~ 

``DefaultFn`` is a nullary function object. The type returned by invoking this
function is determined by ``boost::result_of<DefaultFn()>::type`` on compilers
that support partial specialization. On less compliant compilers a nested
``DefaultFn::result_type`` is used instead.


.. class:: reference


//////////////////////////////////////////////////////////////////////////////

concept |KeywordExpression|, |KeywordDefaultExpression|
---------------------------------------------------------------------

Models of these concepts are used as indices in a |ArgumentPack|.


.. class:: reference


//////////////////////////////////////////////////////////////////////////////

concept |ArgumentPack|
-------------------------------

.. Rename this?

Models of this concept are containers of parameters where each parameter
is tagged with a keyword.

Requirements
~~~~~~~~~~~~

* ``x`` and ``z`` are objects that model |ArgumentPack|.
* ``z`` is a *singular* |ArgumentPack| as created by ``keyword::operator``.
* ``y`` is a model if :concept:`KeywordExpression`.
* ``u`` is a model if :concept:`KeywordDefaultExpression`.
* ``X`` is the type of ``x``.
* ``K`` is the tag type used in ``y`` and ``u``.
* ``D`` is the type of the default value in ``u``.

+------------+---------------------------+------------------------------+------------------------------------------------------+
| Expression | Type                      | Requirements                 | Semantics/Notes                                      |
+============+===========================+==============================+======================================================+
| ``x[y]``   | binding<X, K>::type       | An argument tagged           | Returns the bound argument tagged with ``K``.        |
|            |                           | with ``K`` exists            |                                                      |
|            |                           | in ``x``.                    |                                                      |
+------------+---------------------------+------------------------------+------------------------------------------------------+
| ``x[u]``   | binding<X, K, D>::type    | \-                           | Returns the bound argument tagged with ``K``         |
|            |                           |                              | if such an argument exists. Otherwise returns        |
|            |                           |                              | the default value of ``u``.                          |
|            |                           |                              |                                                      |
|            |                           |                              | If ``u`` has a *lazy default*, this may throw        |
|            |                           |                              | whatever the default value function of ``u`` throws  |
|            |                           |                              | when ``x`` does not contain an argument tagged with  |
|            |                           |                              | ``K``.                                               |
+------------+---------------------------+------------------------------+------------------------------------------------------+
| ``x, z``   | Model of |ArgumentPack|   | \-                           | Returns a composite |ArgumentPack| that              |
|            |                           |                              | contains bindings to all arguments bound in ``x``    |
|            |                           |                              | and ``z``.                                           |
+------------+---------------------------+------------------------------+------------------------------------------------------+



.. class:: reference


//////////////////////////////////////////////////////////////////////////////

concept |ParameterSpec|
-----------------------

Models of this concept with special meaning are:

* :class:`required`
* :class:`optional`

Any other type will be treated as a *keyword Tag*.


.. class:: reference


//////////////////////////////////////////////////////////////////////////////

macro ``BOOST_PARAMETER_KEYWORD``
---------------------------------

**Defined in**
    `boost/parameter/keyword.hpp`__

__ ../../../../boost/parameter/keyword.hpp

Macro used to define keyword objects.

.. parsed-literal::

    BOOST_PARAMETER_KEYWORD(tag_namespace, name)

Requirements
~~~~~~~~~~~~

* ``tag_namespace`` is the namespace where the tag-types will be placed.
* ``name`` is the name that will be used for the keyword.


.. class:: reference


//////////////////////////////////////////////////////////////////////////////


macro ``BOOST_PARAMETER_FUN``
-----------------------------

**Defined in**
    `boost/parameter/macros.hpp`__

__ ../../../../boost/parameter/macros.hpp

.. parsed-literal::

    BOOST_PARAMETER_FUN(ret, name, lo, hi, parameters)

Requirements
~~~~~~~~~~~~

* ``ret`` is the return type of the function.
* ``name`` is the name of the function.
* ``lo``, ``hi`` defines the range of arities for the function.
* ``parameters`` is the name of the ``parameters<>`` instance
  used for the function.

