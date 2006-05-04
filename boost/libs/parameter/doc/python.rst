+++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++
 The Boost Parameter Library Python Binding Documentation 
+++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++

|(logo)|__

.. |(logo)| image:: ../../../../boost.png
   :alt: Boost

__ ../../../../index.htm

:Authors:       Daniel Wallin
:Contact:       dalwan01@student.umu.se
:organization:  `Boost Consulting`_
:date:          $Date$

:copyright:     Copyright David Abrahams, Daniel Wallin
                2005. Distributed under the Boost Software License,
                Version 1.0. (See accompanying file LICENSE_1_0.txt
                or copy at http://www.boost.org/LICENSE_1_0.txt)

.. _`Boost Consulting`: http://www.boost-consulting.com


.. role:: class
    :class: class

.. role:: concept
    :class: concept

.. role:: function
    :class: function

.. |KeywordsSpec| replace:: :concept:`KeywordsSpec`

.. contents::
    :depth: 1

Introduction
------------

``boost/parameter/python.hpp`` introduces a group of **def_visitors** that can
be used to easily expose Boost.Parameter enabled member functions to Python via 
Boost.Python. It also provides a function template ``def()`` that can be used
to expose Boost.Parameter enabled free functions.

concept |KeywordsSpec|
----------------------

A |KeywordsSpec| is an MPL sequence where each element is either:

* A *required* keyword tag, ``K``
* **or**, an *optional* keyword tag, ``K*``
* **or**, a *special* keyword tag ``K**``

The **arity range** of a |KeywordsSpec| is determined by:

.. parsed-literal::

    [ mpl::size<S> - number of *special* keyword tags in ``S`` , mpl::size<S> ]

For example, the **arity range** of ``mpl::vector2<x,y>`` is 2, the **arity range** of
``mpl::vector2<x,y*>`` is 2 and the **arity range** of ``mpl::vector2<x,y**>`` is 1.

*special* keyword tags
---------------------------------

If the default type for an argument is not convertible to the argument type, as
specified to the binding functions below, that argument must be specified as a
*special* argument.

In the example below the default type for argument ``y`` is ``char const[5]``, but
the argument type is ``int``. Therefore ``y`` must be specified as a *special*
argument in the |KeywordsSpec|.

Doing this will generate N^2 overloads, where N is the number of *special* arguments.
In this case two overloads will be generated, one with ``y`` included and one without.
Having many *special* keywords will result in lots of overloads, and stress the
compiler.

Note that this makes the *arity range* ``[1,2]``, so we'll need two forwarding overloads.

.. parsed-literal::

    BOOST_PARAMETER_FUNCTION((void), f, tag,
        (required (x, \*))
        (optional (y, \*))
    )
    {
        std::cout << args[x] << args[y | "none"] << "\n";
    }

    struct f_fwd
    {
        template <class A0, class A1>
        void operator()(boost::type<void>, A0 const& a0)
        {
            f(a0);
        }

        template <class A0, class A1>
        void operator()(boost::type<void>, A0 const& a0, A1 const& a1)
        {
            f(a0, a1);
        }
    };

    BOOST_PYTHON_MODULE(..)
    {
        class_<X>("X")
            .def("f",
                function<
                    fwd
                  , mpl::vector2<tag::x, **tag::y\*\***>
                  , mpl::vector3<void, int, int>
                >()
            );
    }
        

------------------------------------------------------------------------------

class template ``init``
-----------------------

Defines a named parameter enabled constructor.

.. parsed-literal::

    template <class Keywords, class Signature>
    struct init : python::def_visitor<init<Keywords, Signature> >
    {
        template <class Class> 
        void def(Class& class\_);
    };

``init`` requirements 
~~~~~~~~~~~~~~~~~~~~~

* ``Keywords`` is a model of |KeywordsSpec|. 
* ``Signature`` is an MPL sequence with the types of the keyword arguments, 
  in the order dictated by ``Keywords``.
* ``Class`` must support these expressions:

  ======================================================= ==================== ==============================================
  Expression                                              Return type          Requirements
  ======================================================= ==================== ==============================================
  ``Class(a0, ..., aN)``                                  \-                   ``a0``..\ ``aN`` are tagged arguments.
  ======================================================= ==================== ==============================================

  For every ``N`` in ``[U,V]``, where ``[U,V]`` is the **arity range** of ``Keywords``.

Example
~~~~~~~

.. parsed-literal::

    struct base { /\* ... \*/ };

    class X : base
    {
    public:
        BOOST_PARAMETER_CONSTRUCTOR(X, (base),
            (required (x, \*))
            (optional (y, \*))
        )
    };

    BOOST_PYTHON_MODULE(..)
    {
        class_<X>("X")
            .def(
                init<
                  , mpl::vector2<tag::x, tag::y\*>
                  , mpl::vector2<int, int>
                >()
            );
    }

------------------------------------------------------------------------------

class template ``call``
-----------------------

Defines a ``__call__`` operator, mapped to ``operator()`` in C++.

.. parsed-literal::

    template <class Keywords, class Signature>
    struct call : python::def_visitor<call<Keywords, Signature> >
    {
        template <class Class> 
        void def(Class& class\_);
    };

``call`` requirements 
~~~~~~~~~~~~~~~~~~~~~

* ``Keywords`` is a model of |KeywordsSpec|. 
* ``Signature`` is an MPL sequence with the types of the keyword arguments, 
  in the order dictated by ``Keywords``, and the return type prepended.
* ``Class`` must support these expressions, where ``c`` is an instance of ``Class``:

  ======================================================= ==================== ==============================================
  Expression                                              Return type          Requirements
  ======================================================= ==================== ==============================================
  ``c(a0, ..., aN)``                                      Convertible to ``R`` ``a0``..\ ``aN`` are tagged arguments.
  ======================================================= ==================== ==============================================

  For every ``N`` in ``[U,V]``, where ``[U,V]`` is the **arity range** of ``Keywords``.

Example
~~~~~~~

.. parsed-literal::

    typedef parameter::parameters<
        parameter::required<tag::x>
      , parameter::optional<tag::y>
    > call_parameters;

    class X
    {
    public:
        template <class Args>
        int call_impl(Args const& args)
        {
            /\* ... \*/
        }

        template <class A0>
        int operator()(A0 const& a0)
        {
            return call_impl(call_parameters()(a0));
        }

        template <class A0, class A1>
        int operator()(A0 const& a0, A1 const& a1)
        {
            return call_impl(call_parameters()(a0,a1));
        }
    };

    BOOST_PYTHON_MODULE(..)
    {
        class_<X>("X")
            .def("f",
                call<
                  , mpl::vector2<tag::x, tag::y\*>
                  , mpl::vector3<int, int, int>
                >()
            );
    }    

------------------------------------------------------------------------------

class template ``function``
---------------------------

Defines a named parameter enabled member function.

.. parsed-literal::

    template <class Fwd, class Keywords, class Signature>
    struct function : python::def_visitor<function<Fwd, Keywords, Signature> >
    {
        template <class Class, class Options> 
        void def(Class& class\_, char const* name, Options const& options);
    };

``function`` requirements 
~~~~~~~~~~~~~~~~~~~~~~~~~

* ``Keywords`` is a model of |KeywordsSpec|. 
* ``Signature`` is an MPL sequence with the types of the keyword arguments, 
  in the order dictated by ``Keywords``, and the return type prepended.
* An instance of ``Fwd`` must support this expression:

  ======================================================= ==================== ==============================================
  Expression                                              Return type          Requirements
  ======================================================= ==================== ==============================================
  ``fwd(boost::type<R>(), self, a0, ..., aN)``            Convertible to ``R`` ``self`` is a reference to the object on which
                                                                               the function should be invoked. ``a0``..\ ``aN``
                                                                               are tagged arguments.
  ======================================================= ==================== ==============================================

  For every ``N`` in ``[U,V]``, where ``[U,V]`` is the **arity range** of ``Keywords``.


Example
~~~~~~~

This example exports a member function ``f(int x, int y = ..)`` to Python.
The |KeywordsSpec| ``mpl::vector2<tag::x, tag::y*>`` has an **arity range**
of [2,2], so we only need one forwarding overload.

.. parsed-literal::

    class X
    {
    public:
        BOOST_PARAMETER_MEMBER_FUNCTION((void), f, tag,
            (required (x, \*))
            (optional (y, \*))
        )
        {
            /\* .. \*/
        }
    };

    struct f_fwd
    {
        template <class A0, class A1>
        void operator()(boost::type<void>, X& self, A0 const& a0, A1 const& a1)
        {
            self.f(a0, a1);
        }
    };

    BOOST_PYTHON_MODULE(..)
    {
        class_<X>("X")
            .def("f",
                function<
                    fwd
                  , mpl::vector2<tag::x, tag::y\*>
                  , mpl::vector3<void, int, int>
                >()
            );
    }

------------------------------------------------------------------------------

function template ``def``
-------------------------

Defines a named parameter enabled free function in the current Python scope.

.. parsed-literal::

    template <class Fwd, class Keywords, class Signature>
    void def(char const* name);

``def`` requirements 
~~~~~~~~~~~~~~~~~~~~

* ``Keywords`` is a model of |KeywordsSpec|. 
* ``Signature`` is an MPL sequence with the types of the keyword arguments, 
  in the order dictated by ``Keywords``, and the return type prepended.
* An instance of ``Fwd`` must support this expression:

  ======================================================= ==================== ==============================================
  Expression                                              Return type          Requirements
  ======================================================= ==================== ==============================================
  ``fwd(boost::type<R>(), a0, ..., aN)``                  Convertible to ``R`` ``a0``..\ ``aN`` are tagged arguments.
  ======================================================= ==================== ==============================================

  For every ``N`` in ``[U,V]``, where ``[U,V]`` is the **arity range** of ``Keywords``.


Example
~~~~~~~

This example exports a function ``f(int x, int y = ..)`` to Python.
The |KeywordsSpec| ``mpl::vector2<tag::x, tag::y*>`` has an **arity range**
of [2,2], so we only need one forwarding overload.

.. parsed-literal::

    BOOST_PARAMETER_FUNCTION((void), f, tag,
        (required (x, \*))
        (optional (y, \*))
    )
    {
        /\* .. \*/
    }

    struct f_fwd
    {
        template <class A0, class A1>
        void operator()(boost::type<void>, A0 const& a0, A1 const& a1)
        {
            f(a0, a1);
        }
    };

    BOOST_PYTHON_MODULE(..)
    {
        def<
            fwd
          , mpl::vector2<tag::x, tag::y\*>
          , mpl::vector3<void, int, int>
        >("f");
    }

Portability
-----------

The Boost.Parameter Python binding library requires *partial template specialization*.

