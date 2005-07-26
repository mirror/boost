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
    |KeywordExpression|_

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
        |ArgumentPack|_ `operator=`_\(T& value) const;

        template <class T>
        |ArgumentPack|_ `operator=`_\(T const& value) const;

        template <class T>
        |ArgumentPack|_ `operator|`_\(T& default\_) const;

        template <class T>
        |KeywordDefaultExpression|_ `operator|`_\(T const& default\_) const;

        template <class F>
        |KeywordDefaultExpression|_ `operator||`_\(F const&) const;
    };


.. dwa:

   We don't have a convention of using a raw concept name,
   formatted as a concept, as the return value of a function.  If
   we're going to start doing this, don't we need to explain it
   somewhere?

operator=
~~~~~~~~~

.. parsed-literal::

    template <class T> |ArgumentPack|_ operator=(T& value) const;
    template <class T> |ArgumentPack|_ operator=(T const& value) const;

**Requires**
    Nothing.

**Throws**
    Nothing

**Returns**
    A model of |ArgumentPack|_, holding ``value``, tagged with ``Tag``.

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

    template <class T> |KeywordDefaultExpression|_ operator|(T& default\_) const;
    template <class T> |KeywordDefaultExpression|_ operator|(T const& default\_) const;

**Throws**
    Nothing

**Returns**
    An object that holds ``default_`` as a default for the
    keyword tag ``Tag``.

.. daniel:
    A model of |KeywordDefaultExpression|_ that, when used to
    index an |ArgumentPack|_ that does not contain an appropriate
    parameter, gives ``default_``.

.. daniel:

    An object that models KeywordDefaultExpression, that when used as
    an argument to ``ArgumentPack::operator[]`` which doesn't contain
    a parameter specified with ``Tag`` returns a reference to ``default_``.

.. dwa: 

   1. First of all, there is no class called ArgumentPack that has
   an operator[].

   2. an operator[] can't contain a parameter

   3. "which" should be "that"

   4. You need a comma after ``Tag``.

   5. It's the *type*, not the object, that models the concept.
      If we're going to use this convention of using concept names
      in place of return types, we should document it once at the
      beginning and then we never have to say what the object's
      type models.

   6. An object doesn't return anything, even when used as an
      argument.

   7. "Specified with ``Tag``" is vague.  I don't think any
      reasonable definition you could come up with could be
      correct, since the ArgumentPack may hold a reference to an
      object associated *positionally* with Tag.

   Maybe:

      An object that holds ``default_`` as a default for the
      keyword tag ``Tag``.


   This description would oblige us to explain the
   terminology "...holds as a default for keyword tag..." in the
   definition of KeywordDefaultExpression and associated concepts:

operator||
~~~~~~~~~~

.. parsed-literal::

    template <class F> |KeywordDefaultExpression|_ operator||(F const& fn) const;

**Throws**
    Nothing

**Requires**
    ``F`` is a nullary function object.

In the next two tables, ``fn`` is an object of type ``F``.

.. dwa: You have to define "function object."  Plain function
   pointers are legal where result_of is supported, FYI.

    **On compilers that support boost::result_of, as indicated by BOOST_NO_RESULT_OF:**

.. dwa: This should be "on compilers that support result_of."
   Likewise below.  See the result_of docs for the BOOST_NO_RESULT_OF macro 

    +---------------------------------+-----------------------------------------------------+
    | Expression                      | Requirement                                         |
    +=================================+=====================================================+
    | ``boost::result_of<F()>::type`` | -                                                   |
    +---------------------------------+-----------------------------------------------------+
    | ``fn()``                        | Convertible to ``boost::result_of<F()>::type``      |
    +---------------------------------+-----------------------------------------------------+

.. You have to say what fn is.  The usual way is to say, "in the
   next two tables, fn is an object of type F."

    **On compilers that don't support boost::result_of, as indicated by BOOST_NO_RESULT_OF:**

    +------------------------------+-----------------------------------------------------+
    | Expression                   | Requirement                                         |
    +==============================+=====================================================+
    | ``F::result_type``           | -                                                   |
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
        |ArgumentPack| `operator()`_\(A0 const& a0) const;

        template <class A0, class A1>
        |ArgumentPack| `operator()`_\(A0 const& a0, A1 const& a1) const;

        template <class A0, class A1, …, class AN>
        |ArgumentPack| `operator()`_\(A0 const& a0, A1 const& a1, …, AN const& aN) const;
    };


Template Parameter Semantics
~~~~~~~~~~~~~~~~~~~~~~~~~~~~

``<P0, …, PN>`` are models of |ParameterSpec|_. If ``Px`` is not an
instance of either ``optional`` or ``required``, it is treated as a
keyword tag with the same meaning as ``optional<Px>``.


match
~~~~~

Used to remove a function from overload resolution using SFINAE.

.. parsed-literal::

        template <class T0, class T1, …, class TN> struct restrict { typedef … type; };

**Returns**
    If the supplied argument types ``<T0, …, TN>`` fulfill the requirments of the
    specified |ParameterSpec|_'s, ``match<T0, …, TN>::type`` exists and is constructible
    from ``parameters<P0, …, PN>``. Otherwise ``restrict<T0, …, TN>::type`` doesn't exist.


operator()
~~~~~~~~~~

.. parsed-literal::

    template <class A0> |ArgumentPack|_ operator()(A0 const& a0) const;
    template <class A0, class A1> |ArgumentPack|_ operator()(A0 const& a0, A1 const& a1) const;
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

**Models**
    |ParameterSpec|_

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

.. _keyworddefaultexpression:
.. _keywordexpression:

concept |KeywordExpression|, |KeywordDefaultExpression|
---------------------------------------------------------------------

Models of these concepts are used as indices in a |ArgumentPack|. Models
of |KeywordDefaultExpression| will hold a default value to be used when
no appropriate argument was passed.

.. _lazy default:

Lazy Defaults
~~~~~~~~~~~~~

A |KeywordDefaultExpression| may contain a *lazy default*, meaning it's
default value is only computed when needed.


.. class:: reference


//////////////////////////////////////////////////////////////////////////////

.. _argumentpack:

concept |ArgumentPack|
-------------------------------

Models of this concept are containers of parameters where each parameter
is tagged with a keyword.

Requirements
~~~~~~~~~~~~

* ``x`` and ``z`` are objects that model |ArgumentPack|.
* ``z`` is a |ArgumentPack|_ containing only one argument, as created by ``keyword::operator``.
* ``y`` is a model if |KeywordExpression|_.
* ``u`` is a model if |KeywordDefaultExpression|_.
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
|            |                           |                              | If ``u`` has a `lazy default`_, this may throw       |
|            |                           |                              | whatever the default value function of ``u`` throws  |
|            |                           |                              | when ``x`` does not contain an argument tagged with  |
|            |                           |                              | ``K``.                                               |
+------------+---------------------------+------------------------------+------------------------------------------------------+
| ``x, z``   | Model of |ArgumentPack|   | \-                           | Returns a composite |ArgumentPack|_ that             |
|            |                           |                              | contains bindings to all arguments bound in ``x``    |
|            |                           |                              | and ``z``.                                           |
+------------+---------------------------+------------------------------+------------------------------------------------------+


.. class:: reference


//////////////////////////////////////////////////////////////////////////////

.. _parameterspec:

concept |ParameterSpec|
-----------------------

Used to describe type restrictions and positional meaning in a parameter
set.

Models of this concept with special meaning are:

* :class:`required`
* :class:`optional`

Any other type will be treated as a *keyword Tag*.


.. class:: reference


//////////////////////////////////////////////////////////////////////////////

.. _boost_parameter_keyword:

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

