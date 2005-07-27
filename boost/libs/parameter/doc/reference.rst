+++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++
 The Boost Parameter Library Reference Documentation |(logo)|__
+++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++

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

Preliminaries
=============

In this reference, all identifiers will be written as if the
namespace alias ::

  namespace parameter = boost::parameter;

is in force: we'll write ``parameter::xxx`` instead of
``boost::parameter::xxx``.

Terminology
===========

.. _keyword:
.. |keyword| replace:: `keyword`_

keyword
  The name of a function parameter.

.. _keyword tag type:
.. |keyword tag type| replace:: `keyword tag type`_

keyword tag type
  A type of the form ``parameter::keyword<K>`` used to uniquely
  identify a function parameter.   Typically ``K`` will be a type
  whose name is the same as that of the parameter.

.. _tag type:
.. |tag type| replace:: `tag type`_

tag type
  Shorthand for “\ |keyword tag type|.”

.. _keyword object:
.. |keyword object| replace:: `keyword object`_

keyword object
  An object whose type is a tag type.

.. _tagged reference:
.. |tagged reference| replace:: `tagged reference`_

tagged reference
  An object that 
  * contains a reference to its *value*, and
  * whose type is associated with a |keyword tag type|.

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
  A |tagged reference| whose *value* computes a default
  argument value when invoked with no arguments.

Concepts
========

|ArgumentPack|
--------------

An |ArgumentPack| is conceptually a collection of |tagged
reference|\ s to the actual arguments passed to a function.

Requirements
~~~~~~~~~~~~

Unless otherwise specified, no use of an |ArgumentPack| throws
an exceptions.

In the table below, 

* ``A`` is a model of |ArgumentPack|
* ``x`` is an instance of ``A``
* ``u`` is a |keyword object| of type ``K``
* ``v`` is a |tagged default| with |tag type| ``L`` and *value* of type ``D``
* ``w`` is a |tagged lazy default| with |tag type| ``M`` and *value* of type ``E const``
* ``z`` is an |ArgumentPack| containing a single element (as created by ``keyword::operator=``)

and no exceptions are thrown other than those propagated from the
invocation of ``w``\ 's *value*.

+----------+-----------------------------+------------------+--------------------------------------+
|Expression| Type                        |Requirements      |Semantics/Notes                       |
+==========+=============================+==================+======================================+
|``x[u]``  |``binding<A,K>::type``       |``x`` contains an |Returns *b*\ 's *value* (by           |
|          |                             |element *b* whose |reference).                           |
|          |                             |keyword is ``K``  |                                      |
+----------+-----------------------------+------------------+--------------------------------------+
|``x[u]``  |``binding<A,L,D>::type``     |*none*            |If ``x`` contains an element *b* whose|
|          |                             |                  |keyword is the same as ``u``\ 's,     |
|          |                             |                  |returns *b*\ 's *value* (by           |
|          |                             |                  |reference).  Otherwise, returns ``u``\|
|          |                             |                  |'s *value*.                           |
+----------+-----------------------------+------------------+--------------------------------------+
|``x[w]``  |``lazy_binding<A,M,E>::type``|*none*            |If ``x`` contains an element *b* whose|
|          |                             |                  |keyword is the same as ``w``\ 's,     |
|          |                             |                  |returns *b*\ 's *value* (by           |
|          |                             |                  |reference).  Otherwise, invokes ``w``\|
|          |                             |                  |'s *value* and returns the result.    |
+----------+-----------------------------+------------------+--------------------------------------+
|``x, z``  |Model of |ArgumentPack|      |*none*            |Returns an |ArgumentPack|_ containing |
|          |                             |                  |all the elements of both ``x`` and    |
|          |                             |                  |``z``.                                |
+----------+-----------------------------+------------------+--------------------------------------+


.. class:: reference


//////////////////////////////////////////////////////////////////////////////

.. _parameterspec:

|ParameterSpec|
---------------

Used to describe type restrictions and positional meaning in a parameter
set.

Models of this concept with special meaning are:

* :class:`required`
* :class:`optional`


.. daniel: maybe this shouldn't be here...

  Any other type will be treated as a *keyword Tag*.


Other Stuff
===========

That heading will be replaced by many others.

.. class:: reference


//////////////////////////////////////////////////////////////////////////////



class template :class:`keyword`
------------------------------------

**Defined in**
    `boost/parameter/keyword.hpp`__

__ ../../../../boost/parameter/keyword.hpp

.. dwa:

    1. You never defined IndexExpression

    2. You should use cross-linking to the concept definitions,
       thus, |IndexExpression|_

    3. A class template doesn't model any concept we use other than
       Metafunction.  Maybe specializations model IndexExpression,
       or something.

.. parsed-literal::

    template <class Tag>
    struct keyword
    {
        template <class T>
        *unspecified model of* |ArgumentPack|_ `operator=`_\(T& value) const;

        template <class T>
        *unspecified model of* |ArgumentPack|_ `operator=`_\(T const& value) const;

        template <class T>
        *unspecified tagged default* `operator|`_\(T& default\_) const;

        template <class T>
        *unspecified tagged default* `operator|`_\(T const& default\_) const;

        template <class F>
         *unspecified tagged lazy default* `operator||`_\(F const&) const;
    };


.. dwa:

   We don't have a convention of using a raw concept name,
   formatted as a concept, as the return value of a function.  If
   we're going to start doing this, don't we need to explain it
   somewhere?


.. comment .. _keyword object:

Keyword objects
~~~~~~~~~~~~~~~

.. comment .. |keyword-object| replace:: `keyword object`_

Keyword objects are instances of a ``keyword<>`` specialization.

operator=
~~~~~~~~~

.. parsed-literal::

    template <class T> *unspecified model of* |ArgumentPack|_ operator=(T& value) const;
    template <class T> *unspecified model of* |ArgumentPack|_ operator=(T const& value) const;

**Requires**
    Nothing.

**Throws**
    Nothing

**Returns**
    A model of |ArgumentPack|_, holding ``value`` (by reference),
    and tagged with ``Tag``.

.. dwa:

     1. We don't have a convention of writing "*cv* reference to."
        I know what you mean, but if we're going to start doing
        this we need to explain the convention somewhere.

     2. It's not a cv reference to value, since value itself is a
        reference.  You can only reference an object.  So this
        should be, perhaps, "holding value" or if you think that's
        not explicit enough, "holding a reference equivalent to
        value."  That deals with the cv issue.


operator|
~~~~~~~~~

.. parsed-literal::

    template <class T> *unspecified tagged default* operator|(T& x) const;
    template <class T> *unspecified tagged default* operator|(T const& x) const;

**Throws**
    Nothing

**Returns**
    An object holding x (by reference) as a default for keyword ``Tag``,
    and suitable for use in an ArgumentPack's index operator.

.. old:
    An object that holds ``x`` as a default for the
    keyword tag ``Tag``.

.. daniel:
    A model of |KeywordDefaultExpression|_ that, when used to
    index an |ArgumentPack|_ that does not contain an appropriate
    parameter, gives ``x``.

.. daniel:

    An object that models KeywordDefaultExpression, that when used as
    an argument to ``ArgumentPack::operator[]`` which doesn't contain
    a parameter specified with ``Tag`` returns a reference to ``default_``.

.. dwa: 

   Maybe:

      An object that holds ``default_`` as a default for the
      keyword tag ``Tag``.


   This description would oblige us to explain the
   terminology "...holds as a default for keyword tag..." in the
   definition of KeywordDefaultExpression and associated concepts.

   I changed ``default_`` to ``x`` because it is difficult to read
   a sentence that uses the word "default" and the identifier
   ``default_`` .  We're just using a generic ``T`` anyhow.

operator||
~~~~~~~~~~

.. parsed-literal::

    template <class F> *unspecified tagged lazy default* operator||(F const& fn) const;

**Throws**
    Nothing

.. dwa: You have to define "function object."  Plain function
   pointers are legal where result_of is supported, FYI.

**Requires**
    ``F`` is a nullary function object.

    In the next two tables, ``fn`` is an object of type ``F``.

    **On compilers that support boost::result_of, as indicated by BOOST_NO_RESULT_OF:**

    +---------------------------------+-----------------------------------------------------+
    | Expression                      | Requirement                                         |
    +=================================+=====================================================+
    | ``boost::result_of<F()>::type`` | \-                                                  |
    +---------------------------------+-----------------------------------------------------+
    | ``fn()``                        | Convertible to ``boost::result_of<F()>::type``      |
    +---------------------------------+-----------------------------------------------------+

    **On compilers that don't support boost::result_of, as indicated by BOOST_NO_RESULT_OF:**

    +------------------------------+-----------------------------------------------------+
    | Expression                   | Requirement                                         |
    +==============================+=====================================================+
    | ``F::result_type``           | \-                                                  |
    +------------------------------+-----------------------------------------------------+
    | ``fn()``                     | Convertible to ``F::result_type``                   |
    +------------------------------+-----------------------------------------------------+


.. dwa: I don't think the CopyConstructible requirement is correct.
   What if the result is a reference?  If it's not a reference, and
   there are no implicit conversions, it's surely got to be copy
   constructible so f can return it.  So are you sure you want to
   require CopyConstructible just so you can handle the actual
   return type not being an exact match?

**Returns**
    An object holding x (by reference) as a lazy default for keyword
    ``Tag``, and suitable for use in an ArgumentPack's index operator.


.. old:
    An object that holds a reference to ``fn`` as a `lazy default`_
    for the keyword tag ``Tag``.


.. daniel:
    A model of |KeywordDefaultExpression|_ that, when used to
    index an |ArgumentPack|_ which does not contain an appropriate
    parameter, gives the result of ``fn``.

.. daniel:
    An object that models |KeywordDefaultExpression|_, that when used as
    an argument to ``ArgumentPack::operator[]`` which doesn't contain
    a parameter specified with ``Tag`` evaluates and returns ``fn()``.

.. dwa:

      An object that holds a reference to ``fn`` as a lazy default
      for the keyword tag ``Tag``.

   This description would oblige us to explain "lazy default."

//////////////////////////////////////////////////////////////////////////////

.. class:: reference

.. _parameters:

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
~~~~~~~~~~~~~~~~~~~~~~~~~~~~

``<P0, …, PN>`` are models of |ParameterSpec|_. If ``Px`` is not an
instance of either ``optional`` or ``required``, it is treated as a
keyword tag with the same meaning as ``optional<Px>``.

``<P0, …, PN>`` determine the positional meaning of the parameters,
and the type requirements for passed arguments.


match
~~~~~

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
~~~~~~~~~~

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


//////////////////////////////////////////////////////////////////////////////

.. class:: reference

.. _optional:
.. _required:

class templates :class:`optional`, :class:`required`
----------------------------------------------------

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

The default value of ``Predicate`` is an unspecified metafunction that returns
``mpl::true_`` for any argument.


//////////////////////////////////////////////////////////////////////////////

.. class:: reference

.. _binding:

class template :class:`binding`
-------------------------------------------------------------

**Defined in**
    `boost/parameter/binding.hpp`__

__ ../../../../boost/parameter/binding.hpp

A metafunction that, given an |ArgumentPack|_, returns the reference
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


.. _lazy_binding:

class template :class:`lazy_binding`
------------------------------------------------------------------

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
~~~~~~~~~~~~ 

``DefaultFn`` is a nullary function object. The type returned by invoking this
function is determined by ``boost::result_of<DefaultFn()>::type`` on compilers
that support partial specialization. On less compliant compilers a nested
``DefaultFn::result_type`` is used instead.


.. class:: reference


//////////////////////////////////////////////////////////////////////////////

.. _boost_parameter_keyword:

macro ``BOOST_PARAMETER_KEYWORD``
---------------------------------

**Defined in**
    `boost/parameter/keyword.hpp`__

__ ../../../../boost/parameter/keyword.hpp

Macro used to define `keyword objects`__.

__ `keyword object`_

.. parsed-literal::

    BOOST_PARAMETER_KEYWORD(tag_namespace, name)

Requirements
~~~~~~~~~~~~

* ``tag_namespace`` is the namespace where the tag-types will be placed.
* ``name`` is the name that will be used for the keyword.


.. class:: reference


//////////////////////////////////////////////////////////////////////////////

.. _boost_parameter_fun:

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

