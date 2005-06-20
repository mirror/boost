=========================================
 Boost.Parameter Reference Documentation
=========================================

.. contents::
    :depth: 1

//////////////////////////////////////////////////////////////////////////////

.. role:: class
    :class: class

.. role:: concept
    :class: concept

.. role:: function
    :class: function

.. class:: reference

class template :class:`keyword`
------------------------------------

TODO Introduction

**Models**
    :concept:`IndexExpression`

.. parsed-literal::

    template <class Tag>
    struct keyword
    {
        template <class T>
        :concept:`KeywordTuple` `operator=`_\(T& value) const;

        template <class T>
        :concept:`KeywordTuple` `operator=`_\(T const& value) const;

        template <class T>
        :concept:`IndexDefaultExpression` `operator|`_\(T& default\_) const;

        template <class T>
        :concept:`IndexDefaultExpression` `operator|`_\(T const& default\_) const;

        template <class F>
        :concept:`IndexDefaultExpression` `operator||`_\(F const&) const;
    };


operator=
~~~~~~~~~

.. parsed-literal::

    template <class T> :concept:`KeywordTuple` operator=(T& value) const;
    template <class T> :concept:`KeywordTuple` operator=(T const& value) const;

**Requires**
    Nothing.

**Returns**
    A model of :concept:`KeywordTuple`, holding a *cv* reference to ``value``,
    tagged with ``Tag``.


operator|
~~~~~~~~~

.. parsed-literal::

    template <class T> :concept:`IndexDefaultExpression` operator|(T& default\_) const;
    template <class T> :concept:`IndexDefaultExpression` operator|(T const& default\_) const;

**Requires**
    Nothing

**Returns**
    An object that models :concept:`IndexDefaultExpression`, that when used as
    an argument to ``ArgumentTuple::operator[]`` which doesn't contain
    a parameter specified with ``Tag`` returns ``default_``.


operator||
~~~~~~~~~~

.. parsed-literal::

    template <class F> :concept:`IndexDefaultExpression` operator|(F const& fn) const;

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
    An object that models :concept:`IndexDefaultExpression`, that when used as
    an argument to ``ArgumentTuple::operator[]`` which doesn't contain
    a parameter specified with ``Tag`` evaluates and returns ``fn()``.


//////////////////////////////////////////////////////////////////////////////

.. class:: reference

class template :class:`parameters`
---------------------------------------------------

.. parsed-literal::

    template <class P0, class P1, ..., class PN>
    struct parameters
    {
        template <class T0, class T1, ..., class TN>
        struct `restrict`_
        {
            ...
        };

        template <class A0>
        :concept:`KeywordTuple` `operator()`_\(A0 const& a0) const;

        template <class A0, class A1>
        :concept:`KeywordTuple` `operator()`_\(A0 const& a0, A1 const& a1) const;

        template <class A0, class A1, ..., class An>
        :concept:`KeywordTuple` `operator()`_\(A0 const& a0, A1 const& a1, ..., An const& an) const;
    };


Template Parameter Semantics
~~~~~~~~~~~~~~~~~~~~~~~~~~~~

TODO


restrict
~~~~~~~~

.. parsed-literal::

        template <class T0, class T1, ..., class TN> struct restrict { ... };

**Requires**
    Nothing

**Returns**
    TODO


operator()
~~~~~~~~~~

.. parsed-literal::

    template <class A0> :concept:`KeywordTuple` operator()(A0 const& a0) const;
    template <class A0, class A1> :concept:`KeywordTuple` operator()(A0 const& a0, A1 const& a1) const;
    ...

**Requires**
    TODO

**Returns**
    TODO


//////////////////////////////////////////////////////////////////////////////

.. class:: reference

class template :class:`required`
-------------------------------------------------------------

.. parsed-literal::

    template <class Tag, class Predicate = *unspecified*>
    struct required;


//////////////////////////////////////////////////////////////////////////////

.. class:: reference

class template :class:`optional`
-------------------------------------------------------------

.. parsed-literal::

    template <class Tag, class Predicate = *unspecified*>
    struct optional;


//////////////////////////////////////////////////////////////////////////////

.. class:: reference

class template :class:`binding`
-------------------------------------------------------------

A metafunction that, given an :concept:`ArgumentTuple`, returns the reference
type of the parameter identified by ``Keyword``.  If no such parameter has been
specified, returns ``Default``.

.. parsed-literal::

    template <class Parameters, class Keyword, class Default = *unspecified*>
    struct binding
    {
        typedef ... type;
    };


.. class:: reference


//////////////////////////////////////////////////////////////////////////////

class template :class:`lazy_binding`
------------------------------------------------------------------

A metafunction that, given an :concept:`ArgumentTuple`, returns the reference
type of the parameter identified by ``Keyword``.  If no such parameter has been
specified, returns the type returned by invoking ``DefaultFn``.

.. parsed-literal::

    template <class Parameters, class Keyword, class DefaultFn>
    struct lazy_binding
    {
        typedef ... type;
    };

Requirements 
~~~~~~~~~~~~ 

``DefaultFn`` is a nullary function object. The type returned by invoking this
function is determined by ``boost::result_of<DefaultFn()>::type`` on compilers
that support partial specialization. On less compliant compilers a nested
``DefaultFn::result_type`` is used instead.


.. class:: reference


//////////////////////////////////////////////////////////////////////////////

concept :concept:`IndexExpression`, :concept:`IndexDefaultExpression`
---------------------------------------------------------------------

Models of these concepts are used as indices in a :concept:`KeywordTuple`.


.. class:: reference


//////////////////////////////////////////////////////////////////////////////

concept :concept:`KeywordTuple`
-------------------------------

.. Rename this?

Models of this concept are containers of parameters where each parameter
is tagged with a keyword.

Requirements
~~~~~~~~~~~~

* ``x`` and ``z`` are objects that model :concept:`KeywordTuple`.
* ``y`` is a model if :concept:`IndexExpression`.
* ``u`` is a model if :concept:`IndexDefaultExpression`.
* ``X`` is the type of ``x``.
* ``K`` is the tag type used in ``y`` and ``u``.
* ``D`` is the type of the default value in ``u``.

+---------------+-----------------------------+------------------------------------------------+
| Expression    | Type                        | Notes                                          |
+===============+=============================+================================================+
|``x[y]``       | binding<X, K>::type         | Returns the bound argument tagged with ``K``.  |
+---------------+-----------------------------+------------------------------------------------+
|``x[u]``       | binding<X, K, D>::type      | Returns the bound argument tagged with ``K``.  |
+---------------+-----------------------------+------------------------------------------------+
|``x, z``       | :concept:`KeywordTuple`     | Returns a composite KeywordTuple.              |
+---------------+-----------------------------+------------------------------------------------+


