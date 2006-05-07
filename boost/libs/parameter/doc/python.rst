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

``boost/parameter/python.hpp`` introduces a group of def_visitors_ that can
be used to easily expose Boost.Parameter-enabled member functions to Python with 
Boost.Python. It also provides a function template ``def()`` that can be used
to expose Boost.Parameter-enabled free functions.

.. _def_visitor: def_visitors_
.. _def_visitors: ../../../python/doc/v2/def_visitor.html

When binding a Boost.Parameter enabled function, the keyword tags
must be specified.  Additionally, because Boost.Parameter enabled
functions are templates, the desired function signature must be
specified.

.. Always diff my edited version with the original to see what I
.. changed, and think about why I changed it.  Ask if you don't
.. understand.  "Boost.Parameter-enabled" needs that hyphen
.. everywhere.  I'm leaving that change to you.

.. Why must keyword tags be specified again?  Ah, because we didn't
.. record their association with the wrapped function in the first
.. place.  I think that should be possible, no?

The keyword tags are specified as an `MPL Sequence`_, using the
pointer qualifications described in |KeywordsSpec|_ below.  The
signature is also specifid as an `MPL sequence`_ of parameter
types. Additional data may be needed in the signature sequence by
specific binding utilities. For example, ``function`` requires the
return type to be part of the signature sequence.

.. The last two sentences are terribly vague.  Which namespace is
.. ``function`` in?  Isn't the return type always needed?  What
.. else are we going to do other than pass these sequences to
.. function?

.. _`MPL Sequence`: ../../../mpl/doc/refmanual/sequences.html

Tutorial
--------

In this section we will outline the steps needed to bind a simple
Boost.Parameter enabled member function to Python. Knowledge of the
Boost.Parameter macros are required to understand this section.

.. Link to the docs for Boost.Parameter macros

The class and member function we are interested in binding looks
like this::

  // First the keywords
  BOOST_PARAMETER_KEYWORD(tag, title)
  BOOST_PARAMETER_KEYWORD(tag, width)
  BOOST_PARAMETER_KEYWORD(tag, height)

  class window
  {
   public:
      BOOST_PARAMETER_MEMBER_FUNCTION(
        (void), open, tag,
        (required (title, (std::string)))
        (optional (width, (unsigned), 400)
                  (height, (unsigned), 400))
      );
  };

.. Don't use endline layout.

It defines a set of overloaded member functions called ``open``
with one required parameter and two optional ones. To bind this
member function to Python we use the binding utility
``function``. ``function`` is a def_visitor_ that we'll
instantiate and pass to ``boost::python::class_::def()``.

::

  BOOST_PYTHON_MODULE(my_module)
  {
      using namespace boost::python;
      namespace py = boost::parameter::python;

      class_<window>("window")
          .def(
              "open", py::function<
                  mpl::vector<tag::title, tag::width*, tag::height*>,
                  mpl::vector<void, std::string, unsigned, unsigned>
              >()
          );
  }

.. you missed passing the first argument, open_fwd, I think?

.. be consistent in indentation and comma placement.  Pick either
.. leading or trailing commas.

.. Sorry to say this at such a late date, but this syntax really
.. strikes me as cumbersome.  Couldn't we do something like:

      class_<window>("window")
          .def(
              "open", 
              (void (*)( 
                  tag::title(std::string), 
                  tag::width*(unsigned), 
                  tag::height*(unsigned)) 
              )0
          );

   or at least:

      class_<window>("window")
          .def(
              "open", 
              mpl::vector<
                  void, 
                  tag::title(std::string), 
                  tag::width*(unsigned), 
                  tag::height*(unsigned)
              >()
          );

   assuming, that is, that we will have to repeat the tags (yes,
   users of broken compilers will have to give us function pointer
   types instead).

concept |KeywordsSpec|
----------------------

A |KeywordsSpec| is an `MPL sequence`_ where each element is either:

* A *required* keyword of the form ``K``
* **or**, an *optional* keyword of the form ``K*``
* **or**, a *special* keyword of the form ``K**``

where ``K`` is a specialization of ``boost::parameter::keyword``__.
 

.. __ ../../../parameter/doc/html/reference.html#keyword

The **arity range** of a |KeywordsSpec| is defined as the closed
range:

.. parsed-literal::

    [ mpl::size<S> - number of *special* keyword tags in ``S`` , mpl::size<S> ]

For example, the **arity range** of ``mpl::vector2<x,y>`` is [2,2], the **arity range** of
``mpl::vector2<x,y*>`` is [2,2] and the **arity range** of ``mpl::vector2<x,y**>`` is [1,2].

.. Don't optional keywords affect the arity range?


*special* keyword tags
---------------------------------

Sometimes it is desirable to have a default value for a parameter that differ
in type from the parameter. This technique is useful for doing simple tag-dispatching
based on the presence of a parameter. An example_ of this is given in the Boost.Parameter
docs. The example uses a different technique, but could also have been written like this:

.. parsed-literal::

  template <class ArgumentPack>
  void dfs_dispatch(ArgumentPack& args, mpl::false\_)
  {
      *…compute and use default color map…*
  }
  
  template <class ArgumentPack, class ColorMap>
  void dfs_dispatch(ArgumentPack& args, ColorMap colormap)
  {
      *…use colormap…*
  }
  
  template <class ArgumentPack>
  void depth_first_search(ArgumentPack& args)
  {
      core::dfs_dispatch(args, args[color | mpl::false_()]);
  }

.. _example: index.html#dispatching-based-on-the-presence-of-a-default

.. there have been several mistakes in these code examples.  I
.. built a literate programming system for ReST, which we used for
.. the MPL book.  If you'd like I'll check it in and you can use it
.. to check these.

In the above example the type of the default for ``color`` is ``mpl::false_``, a
type that is distinct from any color map that the user might supply.

When binding the case outlined above, the default type for ``color`` will not
be convertible to the parameter type. Therefore we need to tag the ``color``
keyword as a *special* keyword. By doing this we tell the binding functions
that it needs to generate two overloads, one with the ``color`` parameter
present and one without. Had there been two *special* keywords, four
overloads would need to be generated. The number of generated overloads is
equal to ``2^N``, where ``N`` is the number of *special* keywords.

.. The entire section below was rewritten.

.. No need to leave commented out detritus in the document.  That's
.. what source control is for.

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
* ``Signature`` is an MPL sequence of parameter types, 
  in the order dictated by ``Keywords``.
* For every ``N`` in ``[U,V]``, where ``[U,V]`` is the **arity
  range** of ``Keywords``, ``Class`` must support these
  expressions: 

  ======================================================= ==================== ==============================================
  Expression                                              Return type          Requirements
  ======================================================= ==================== ==============================================
  ``Class(a0, ..., aN)``                                  \-                   ``a0``..\ ``aN`` are tagged arguments.
  ======================================================= ==================== ==============================================

.. Limit the width of these table cells.  Some rst backend
.. processors actually produce different results depending on the
.. distribution of width.

  

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
* ``Signature`` is an MPL sequence with the types of the keyword parameters, 
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
* ``Signature`` is an MPL sequence with the types of the keyword parameters, 
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

.. This example is not consistent with your definition of arity
.. range, above.  There are no special keywords in play here.

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
* ``Signature`` is an MPL sequence of parameters types, 
  in the order dictated by ``Keywords``, with the return type
  prepended. 
* An instance of ``Fwd`` must support this expression:

  ======================================================= ==================== ==============================================
  Expression                                              Return type          Requirements
  ======================================================= ==================== ==============================================
  ``fwd(boost::type<R>(), a0, ..., aN)``                  Convertible to ``R`` ``a0``..\ ``aN`` are tagged arguments.
  ======================================================= ==================== ==============================================

  For every ``N`` in ``[U,V]``, where ``[U,V]`` is the **arity range** of ``Keywords``.


Example
~~~~~~~

This example exports a function ``f(int x, int y = ...)`` to Python.
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

.. again, the undefined ``fwd`` identifier.

Portability
-----------

The Boost.Parameter Python binding library requires *partial template specialization*.

.. Oh.  In that case, we don't have to worry so much about
.. compilers that can't parse function types.