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
:date:          $Date: 2005/07/12 17:41:17 $

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
.. _`default expressions`: 

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
tag types could be declared this way::

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

.. Admonition:: Headers and Namespaces

   Most components of the Parameter library are declared in a
   header named for the component.  For example, ::
  
     #include <boost/parameter/keyword.hpp>

   will ensure ``boost::parameter::keyword`` is known to the
   compiler.  There is also a combined header,
   ``boost/parameter.hpp``, that includes most of the library's
   components.  For the the rest of this tutorial, unless we say
   otherwise, you can use the rule above to figure out which header
   to ``#include`` to access any given component of the library.

   Also, the examples below will also be written as if the
   namespace alias ::

     namespace parameter = boost::parameter;

   has been declared: we'll write ``parameter::xxx`` instead of
   ``boost::parameter::xxx``.

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
parameter: a bundle of references to the arguments that the caller
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

It's unlikely that many of the arguments the caller will eventually
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

.. Important::

   The index expression ``args[…]`` always yields a *reference*
   that is bound either to the actual argument passed by the caller
   or, if no argument is explicitly specified, to the specified
   default value.

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

We'll insert the `default expressions`_ in a moment but first we
need to come up with the types *Graph*, *Visitor*, *Vertex*,
*Index*, and *Color*.

The ``binding`` |Metafunction|_
-------------------------------

To compute the type of a parameter we can use a |Metafunction|_
called ``binding``:

.. parsed-literal::

  binding<ArgumentPack, Keyword, Default = void>

where ``Default`` is an optional argument describing the type of
the default argument value, if any.

For example, to declare and initialize ``g``, ``v``, and ``s``
above, we could write:

.. parsed-literal::

  namespace parameter = boost::parameter;

  typedef typename parameter::binding<
    ArgumentPack,\ **tag::graph**
  >::type Graph;

  Graph g = args[graph];

  typedef typename parameter::binding<
    ArgumentPack,\ **tag::visitor,boost::dfs_visitor<>**
  >::type Visitor;

  Visitor v = args[visitor|\ **boost::dfs_visitor<>()**\ ];

  typename **boost::graph_traits<Graph>::vertex_descriptor**
    s = args[root_vertex|\ ***vertices(g).first**\ ];

As shown in the `parameter table`_, ``graph`` has no default, so
the ``binding`` invocation for *Graph* takes only two arguments.
The default ``visitor`` is ``boost::dfs_visitor<>()``, so the
``binding`` invocation for *Visitor* takes three.  Of course,
sometimes we know the type we need, and there's no need to use
``binding`` at all.  Any caller-supplied value for ``root_vertex`` is
nrequired to be (and the default is) of the graph's
``vertex_descriptor`` type, [#vertex_descriptor]_ so we can just
use that type directly.  

.. _dangling:

Note that the default ``visitor`` is supplied as a *temporary*
instance of ``dfs_visitor``.  Because ``args[…]`` always yields
a reference, making ``v`` a reference would cause it to bind to
that temporary, and immediately dangle.  Therefore, it's crucial
that we passed ``dfs_visitor<>``, and not ``dfs_visitor<>
const&``, as the last argument to ``binding``.

.. Important:: 

   Never pass ``binding`` a reference type as the default if the
   default value passed to the |ArgumentPack|\ 's indexing operator
   is a temporary.

.. |Metafunction| replace:: :concept:`Metafunction`

.. _Metafunction: ../../../mpl/doc/refmanual/metafunction.html

Beyond Ordinary Default Aruments
--------------------------------

Here's how you might write the declaration for the ``index_map``
parameter:

.. parsed-literal::

  typedef typename parameter::binding<
      ArgumentPack
    , tag::index_map
    , **typename boost::property_map<Graph, vertex_index_t>::const_type**
  >::type Index;

  Index i = args[index_map|\ **get(boost::vertex_index,g)**\ ];

We'd like you to notice two capabilities we've gained over what
plain C++ default arguments provide:

1. The default value of the ``index`` parameter depends on the
   value of the ``graph`` parameter.  That's illegal in plain C++:
   
   .. parsed-literal::

     void f(int **graph**, int index = **graph** + 1); // error

2. The ``index`` parameter has a useful default, yet it is
   templated and its type can be deduced when  an ``index``
   argument is explicitly specified by the caller.  In plain C++, you
   can *specify* a default value for a parameter with deduced type,
   but it's not very useful:

   .. parsed-literal::

     template <class Index>
     int f(Index index **= 42**);  // OK
     int y = f();                // **error; can't deduce Index**
     
Efficiency Issues
=================

The extraction and binding of the ``color_map`` parameter gives us a few
efficiency issues to consider.  Here's a first cut:

.. parsed-literal::

  typedef 
    vector_property_map<default_color_type, Index>
  default_color_map;

  typename parameter::binding<
      ArgumentPack
    , tag::color_map
    , default_color_map
  >::type color = args[color_map|\ **default_color_map(num_vertices(g),i)**\ ];

Eliminating Copies
------------------

The library has no way to know whether an explicitly-supplied
argument is expensive to copy (or even if it is copiable at all),
so ``binding<…,xxx,…>::type`` is always a reference type when the
*xxx* parameter is supplied by the caller.  Since ``args[…]``
yields a reference to the actual argument, ``color`` will be bound
to the actual ``color_map`` argument and no copying will be done.

As described above__, because the default is a temporary, it's
important that ``color`` be a non-reference when the default is
used.  In that case, the default value will be *copied* into
``color``.  If we store the default in a named variable, though,
``color`` can be a reference, thereby eliminating the copy:

.. parsed-literal::

  default_color_map default_color(num_vertices(g),i);

  typename parameter::binding<
      ArgumentPack
    , tag::color_map
    , **default_color_map&**
  >::type color = args[color_map|default_color];

__ dangling_

.. Hint:: 

   Pass ``binding`` a *reference* to the type of the default to
   avoid making needless copies.x

Eliminating Construction
------------------------

Of course it's nice to avoid copying ``default_color``, but the
more important cost is that of *constructing* it in the first
place.

Dispatching Based on the Presence of a Default
----------------------------------------------

Eliminating Template Instantiation
----------------------------------

However, 
and
``args[visitor…]`` always yields a reference—in this case, a
reference bound directly to the actual argument passed by the user.
When no ``visitor`` is explicitly specified, though, we have to use
the default value, which is supplied as a *temporary* instance of
``dfs_visitor``.  Because ``args[visitor…]`` yields a reference to
that temporary, making ``v`` a reference would cause it to dangle
immediately.  Therefore, it's crucial that we passed
``dfs_visitor<>``, and not ``dfs_visitor<> const&``, to
``binding``.

Since a ``dfs_visitor<>`` is cheap to copy, this arrangement is
non-problematic.

type.  Choosing to make ``Visitor`` a reference in that case

, ``binding`` had better not add

Improving the Syntax
====================

Passing non-const References positionally
-----------------------------------------

Generating the Forwarding Functions with Macros
-----------------------------------------------

Controlling Overload Resolution
===============================


.. [#old_interface] As of Boost 1.33.0 the Graph library was still
   using an `older named parameter mechanism`__, but there were
   plans to change it to use Boost.Parameter (this library) in an
   upcoming release, while keeping the old interface available for
   backward-compatibility.  

.. [#odr] The **One Definition Rule** says that any entity in a C++
   program must have the same definition in all translation units
   (object files) that make up a program.

.. [#msvc_keyword] GCC 2.95.x and Microsoft Visual C++ 6.x and 7.0
   have bugs that makes the syntax for declaring keywords a bit more
   verbose.  This syntax works on all supported compilers, including
   the out-of-date compilers just mentioned:

   .. parsed-literal::

    namespace graphs { namespace // unnamed
    {
      using namespace boost::parameter;

      keyword<tag::graph>& graph = **keyword<tag::graph>::get()**;
      keyword<tag::visitor>& visitor = **keyword<tag::visitor>::get()**;
      keyword<tag::root_vertex>& root_vertex = **keyword<tag::root_vertex>::get()**;
      keyword<tag::index_map>& index_map = **keyword<tag::index_map>::get()**;
      keyword<tag::color_map>& color_map = **keyword<tag::color_map>::get()**;

    }} // unnamed

   If you use Visual C++ 6.x, you may find you also need the
   following using declarations (which really should be
   redundant)::

    namespace graphs
    {
      using graphs::graph;
      using graphs::visitor;
      using graphs::root_vertex;
      using graphs::index_map;
      using graphs::color_map;
    }

.. [#vertex_descriptor] If you're not familiar with the Boost Graph
   Library, don't worry about the meaning of any
   Graph-library-specific details you encounter.  In this case you
   could replace all mentions of vertex descriptor types with
   ``int`` in the text, and your understanding of the Parameter
   library wouldn't suffer.

__ ../../../graph/doc/bgl_named_params.html