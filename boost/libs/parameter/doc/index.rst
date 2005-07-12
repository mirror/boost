+++++++++++++++++++++++++++++++++++++++++++++++++
 The Boost Parameter Library |(logo)|__
+++++++++++++++++++++++++++++++++++++++++++++++++

.. |(logo)| image:: ../../../../boost.png
   :alt: Boost

__ ../../../../index.htm

.. Firefox, at least, seems to need some help lowering
   subscripts. Without the following, subscripts seem not to drop
   at all.

.. raw:: html

  <style type="text/css">
  sub {
    vertical-align: -20%
  }
  </style>

-------------------------------------


:Authors:       David Abrahams, Daniel Wallin
:Contact:       dave@boost-consulting.com, dalwan01@student.umu.se
:organization:  `Boost Consulting`_
:date:          $Date: 2005/07/12 01:59:51 $

:copyright:     Copyright David Abrahams, Daniel Wallin
                2005. Distributed under the Boost Software License,
                Version 1.0. (See accompanying file LICENSE_1_0.txt
                or copy at http://www.boost.org/LICENSE_1_0.txt)

.. _`Boost Consulting`: http://www.boost-consulting.com

:Abstract: Use this library to write functions that accept
  arguments by name:

  .. parsed-literal::

    new_window("alert", **width=10**, **titlebar=false**);

  This capability is especially useful when a function has more
  than one argument with a useful default value, since named
  arguments can be passed in any order.

.. _concepts: ../../../more/generic_programming.html#concept

.. contents:: **Table of Contents**

.. role:: concept
   :class: interpreted

.. section-numbering::

-------------------------------------

==============
 Introduction
==============

In C++, arguments are normally given meaning by their positions
with respect to a parameter list.  That protocol is fine when there
are one or fewer parameters with default values, but when there are
even a few useful defaults, the positional interface becomes
burdensome:

* Since an argument's meaning is given by its position, we have to
  choose an (often arbitrary) order for parameters with default
  values, making some combinations of defaults unusable:

  .. parsed-literal::

    window* new_window(
       char const* name, 
       **int border_width = default_border_width,**
       bool movable = true,
       bool initially_visible = true
       );

    const bool movability = false;
    window* w = new_window("alert box", movability);

  In the example above we wanted to make an unmoveable window
  with a default ``border_width``, but instead we got a moveable
  window with a ``border_width`` of zero.  To get the desired
  effect, we'd need to write:

  .. parsed-literal::

    window* w = new_window(
       "alert box", **default_border_width**, movability);


* It can become difficult for readers to understand the meaning of
  arguments at the call site::

    window* w = new_window("alert", 1, true, false);

  Is this window moveable and initially invisible, or unmoveable
  and initially visible?  The reader needs to remember the order
  of arguments to be sure.  

* The author of the call may not remember the order of the
  arguments either, leading to hard-to-find bugs.

This library addresses the problems outlined above by associating
each parameter with a keyword object.  Now users can identify
arguments by keyword, rather than by position:

.. parsed-literal::

  window* w = new_window("alert box", **movable=**\ false); // OK!

.. I'm inclined to leave this part out.  In particular, the 2nd
   point is kinda lame because even with the library, we need to
   introduce overloads -- dwa:

   C++ has two other limitations, with respect to default arguments,
   that are unrelated to its positional interface:

   * Default values cannot depend on the values of other function
     parameters:

     .. parsed-literal::

       // Can we make resize windows to a square shape by default?
       void resize(
         window* w,
         int **width**, 
         int height **= width** // nope, error!
       );

   * Default values in function templates are useless for any
     argument whose type should be deduced when the argument is
     supplied explicitly::

        template <class T> 
        void f(T x = 0);

        f(3.14) // ok: x supplied explicitly; T is double
        f();    // error: can't deduce T from default argument 0!

   As a side effect of using the Boost Parameter library, you may find
   that you circumvent both of these limitations quite naturally.

==========
 Tutorial
==========

In this section we'll show how the Parameter library can be used to
build an expressive interface to the `Boost Graph library`__\ 's
|dfs|_ algorithm. [#old_interface]_ After describing the
algorithm's abstract interface, we'll show you how to build a basic
implementation with keyword support; then we'll add support for
default arguments, and gradually refine the implementation with
syntax improvements.  Finally we'll show how to streamline the
implementation of named parameter interfaces, improve their
participation in overload resolution, and optimize their runtime
efficiency.

__ ../../../graph/index.html

.. _dfs: ../../../graph/doc/depth_first_search.html

.. |dfs| replace:: ``depth_first_search``

The Abstract Interface to |dfs|
===============================

The Graph library's |dfs| algorithm is a generic function accepting
between one and four arguments by reference, as shown in the table
below:

.. _`parameter table`: 

.. table:: ``depth_first_search`` Parameters

  +----------------+----------+----------------------------------+
  | Parameter Name | Dataflow | Default Value (if any)           |
  +================+==========+==================================+
  |``graph``       | IN       |none - this argument is required. |
  +----------------+----------+----------------------------------+
  |``visitor``     | IN       |``boost::dfs_visitor<>()``        |
  +----------------+----------+----------------------------------+
  |``root_vertex`` | OUT      |``*vertices(g).first``            |
  +----------------+----------+----------------------------------+
  |``index_map``   | IN       |``get(boost::vertex_index,graph)``|
  +----------------+----------+----------------------------------+
  |``color_map``   | IN       |an ``iterator_property_map``      |
  |                |          |created from a ``std::vector`` of |
  |                |          |``default_color_type`` of size    |
  |                |          |``num_vertices(g)`` and using the |
  |                |          |``index_map`` for the index map.  |
  +----------------+----------+----------------------------------+

Don't be intimidated by the complex default values.  For the
purposes of this exercise, you don't need to understand what they
mean. Also, we'll show you how the default for ``color_map`` is
computed later in the tutorial; trust us when we say that the
complexity of its default will become valuable.

Defining the Keywords
=====================

The point of this exercise is to make it possible to call
``depth_first_search`` with keyword arguments, leaving out any
arguments for which the default is appropriate:

.. parsed-literal::

  graphs::depth_first_search(g, **color_map = my_color_map**);

To make that syntax legal, there needs to be an object called
``color_map`` with an assignment operator that can accept a
``my_color_map`` argument.  In this step we'll create one such
**keyword object** for each parameter.  Each keyword object should
be identified by a unique **keyword tag type**.  By convention,
we'll give the tag types the same names as the objects.  Assuming
we're defining our public interface in namespace ``graphs``, the
tag types should be declared this way::

  namespace graphs { namespace tag
  {
    class graph;
    class visitor;
    class root_vertex;
    class index_map;
    class color_map;
  }} // graphs::tag

Because our users never need to name tag types directly, we've put
them in in a nested ``tag`` namespace.  The keyword objects will
actually be provided by the library; we'll just declare references
to them::

  #include <boost/parameter/keyword.hpp>
  #include <boost/parameter/instance.hpp>

  namespace graphs { namespace // unnamed
  {
    using namespace boost::parameter;

    keyword<tag::graph>& graph = instance();
    keyword<tag::visitor>& visitor = instance();
    keyword<tag::root_vertex>& root_vertex = instance();
    keyword<tag::index_map>& index_map = instance();
    keyword<tag::color_map>& color_map = instance();
  }} // graphs::unnamed

The “fancy dance” here involving the unnamed namespace, references,
and the ``instance()`` object is all done to avoid violating the
C++ One Definition Rule (ODR) [#odr]_ when the named parameter
interface is used inside of function templates that get
instantiated in multiple translation units.  Note: if you use an
older compiler, a slightly more verbose syntax may be required
[#msvc_keyword]_.

.. Note::

   Most components of the Parameter library are declared in a
   header named for the component.  For example,
  
     #include <boost/parameter/keyword.hpp>

   will ensure ``boost::parameter::keyword`` is known to the
   compiler.  There is also a combined header,
   ``boost/parameter.hpp``, that includes most of the library's
   components.  For the the rest of this tutorial, unless we say
   otherwise, you can use the rule above to figure out which header
   to ``#include`` to access any given component of the library.

Defining the Implementation Function
====================================

Next we can write the skeleton of the function that implements
the core of ``depth_first_search``::

  namespace graphs { namespace core
  {
    template <class ArgumentPack>
    void depth_first_search(ArgumentPack const& args)
    {
        // algorithm implementation goes here
    }
  }}

.. |ArgumentPack| replace:: :concept:`ArgumentPack`

``core::depth_first_search`` has an |ArgumentPack|
parameter: a bundle of references to the arguments that the user
passes to the algorithm, tagged with their keywords.  To extract
each parameter, just pass its keyword object to the
|ArgumentPack|\ 's index operator.  We'll add some
temporary code to print the arguments, just to get a feel for how
it works:

.. parsed-literal::

  namespace graphs { namespace core
  {
    template <class ArgumentPack>
    void depth_first_search(ArgumentPack const& args)
    {
        std::cout << "graph:\\t" << **args[graph]** << std::endl;
        std::cout << "visitor:\\t" << **args[visitor]** << std::endl;
        std::cout << "root_vertex:\\t" << **args[root_vertex]** << std::endl;
        std::cout << "index_map:\\t" << **args[index_map]** << std::endl;
        std::cout << "color_map:\\t" << **args[color_map]** << std::endl;
    }
  }} // graphs::core

It's unlikely that many of the arguments the user will eventually
pass to ``depth_first_search`` can be printed, but for now the code
above will give us something to experiment with.  To see the
keywords in action, we can write a little test driver:

.. parsed-literal::

  int main()
  {
      using namespace graphs;

      core::depth_first_search(**(**
        graph = 'G', visitor = 2, root_vertex = 3.5, 
        index_map = "hello, world", color_map = false\ **)**);
  }

The results of assigning into each keyword object are combined
using an overloaded comma operator (``operator,``) into a single
|ArgumentPack| object that gets passed on to
``core::depth_first_search``.  The extra set of parentheses you see
in the example above are required: without them, each assignment
would be interpreted as a separate function argument and the comma
operator wouldn't take effect.  We'll show you how to get rid of
the extra parentheses in a moment.

Of course, we can pass the arguments in any order::

  int main()
  {
      using namespace graphs;

      core::depth_first_search((
        root_vertex = 3.14, graph = 'G', color_map = false, 
        index_map = "hello, world", visitor = 2));
  }

either of the two programs above will print::

  graph:       G
  visitor:     2
  root_vertex: 3.5
  index_map:   hello, world
  color_map:   false

Adding Defaults
===============

Currently, all the arguments to ``depth_first_search`` are
required.  If any parameter can't be found, there will be a
compilation error where we try to extract it from the
|ArgumentPack| using the square-brackets operator.  To make it
legal to omit an argument, we need to give it a default value.

Syntax
------

We can make any of the parameters optional by following its keyword
with the ``|`` operator and the parameter's default value within
the brackets.  In the following example, we've given
``root_vertex`` a default of ``42`` and ``color_map`` a default of
``"hello, world"``.

.. parsed-literal::

  namespace graphs { namespace core
  {
    template <class ArgumentPack>
    void depth_first_search(ArgumentPack const& args)
    {
        std::cout << "graph:\\t" << args[graph] << std::endl;
        std::cout << "visitor:\\t" << args[visitor] << std::endl;
        std::cout << "root_vertex:\\t" << args[root_vertex\ **|42**\ ] << std::endl;
        std::cout << "index_map:\\t" << args[index_map] << std::endl;
        std::cout << "color_map:\\t" << args[color_map\ **|"hello, world"**\ ] << std::endl;
    }
  }} // graphs::core

Now we can invoke the function without supplying ``color_map`` or
``root_vertex``::

  core::depth_first_search((
    graph = 'G', index_map = "index", visitor = 6));

The call above would print::

  graph:       G
  visitor:     6
  root_vertex: 42
  index_map:   index
  color_map:   hello, world

Getting More Realistic
----------------------

Now it's time to put some more realistic defaults in place.  We'll
have to give up our print statements—at least if we want to see the
defaults work—because as we mentioned, the default values of these
parameters generally aren't printable.

Instead, we'll connect local variables to the arguments and use
those in our algorithm:

.. parsed-literal::

  namespace graphs { namespace core
  {
    template <class ArgumentPack>
    void depth_first_search(ArgumentPack const& args)
    {
        *Graph*   g = args[graph];
        *Visitor* v = args[visitor|\ *default-expression*\ :sub:`1`\ ];
        *Vertex*  s = args[root_vertex|\ *default-expression*\ :sub:`2`\ ];
        *Index*   i = args[index_map|\ *default-expression*\ :sub:`3`\ ];
        *Color*   c = args[visitor|\ *default-expression*\ :sub:`4`\ ];

        *…use g, v, s, i, and c to implement the algorithm…*
    }
  }} // graphs::core

We'll insert the default expressions in a moment (we outlined them
in the `parameter table`_ above) but first we need to come up with
the types *Graph*, *Visitor*, *Vertex*, *Index*, and *Color*.

The ``binding`` |Metafunction|_
-------------------------------

To compute the type of a parameter we can use a |Metafunction|_
called ``binding``:

.. parsed-literal::

  binding<|ArgumentPack|, *keyword-tag*, *default-type*\ :sub:`opt`>

where *default-type*\ :sub:`opt` is an optional argument describing
the type of the default argument value, if any.  

For example, to declare the *Graph* and *Visitor* types above, we
could write:

.. parsed-literal::

  namespace parameter = boost::parameter;
  using parameter::binding;

  **typename parameter::binding<
    ArgumentPack,tag::graph
  >::type** g = args[graph];

  **typename parameter::binding<
    ArgumentPack,tag::visitor,boost::dfs_visitor<> 
  >::type** v = args[visitor|boost::dfs_visitor<>()];

As shown in the `parameter table`_, ``graph`` has no default, so
the ``binding`` invocation for *Graph* takes only two arguments.
The default ``visitor`` is ``boost::dfs_visitor<>()``, so the
``binding`` invocation for *Visitor* takes three.

.. |Metafunction| replace:: :concept:`Metafunction`

.. _Metafunction: ../../../mpl/doc/refmanual/metafunction.html

  
.. Note::

   For the remainder of this tutorial, you can assume that the
   namespace alias ::

     namespace parameter = boost::parameter;

   is in effect.

Avoiding the Extra Parentheses (Forwarding Functions)
=====================================================

Passing non-const References positionally
-----------------------------------------

Generating the Forwarding Functions with Macros
-----------------------------------------------

Controlling Overload Resolution
-------------------------------

Lazy Default Evaluation
-----------------------


.. [#old_interface] As of Boost 1.33.0 the Graph library was still
   using an `older named parameter mechanism`__, but there were
   plans to change it to use Boost.Parameter (this library) in an
   upcoming release, while keeping the old interface available for
   backward-compatibility.  

.. [#odr] The **One Definition Rule** says that any entity in a C++
   program must have the same definition in all translation units
   (object files) that make up a program.

.. [#msvc_keyword] Microsoft Visual C++ 7.0 and Earlier have bugs
   that makes the syntax for declaring keywords a bit more verbose.
   This syntax will also work on all other known compilers.

   .. parsed-literal::

    namespace // unnamed
    {
      using namespace boost::parameter;

      keyword<tag::graph>& graph = **keyword<tag::graph>::get()**;
      keyword<tag::visitor>& visitor = **keyword<tag::visitor>::get()**;
      keyword<tag::root_vertex>& root_vertex = **keyword<tag::root_vertex>::get()**;
      keyword<tag::index_map>& index_map = **keyword<tag::index_map>::get()**;
      keyword<tag::color_map>& color_map = **keyword<tag::color_map>::get()**;

    } // unnamed

__ ../../../graph/doc/bgl_named_params.html