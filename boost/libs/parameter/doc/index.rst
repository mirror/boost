+++++++++++++++++++++++++++++++++++++++++++++++++
 The Boost Parameter Library 
+++++++++++++++++++++++++++++++++++++++++++++++++

|(logo)|__

.. |(logo)| image:: ../../../../boost.png
   :alt: Boost

__ ../../../../index.htm

-------------------------------------

:Abstract: Use this library to write functions and class templates
  that can accept arguments by name:

  .. parsed-literal::

    new_window("alert", **width=10**, **titlebar=false**);

    smart_ptr<
       Foo 
     , **deleter_is<Deallocate<Foo> >**
     , **copy_policy_is<DeepCopy>**> p(new Foo);
    
  Since named arguments can be passed in any order, they are
  especially useful when a function or template has more than one
  parameter with a useful default value.  The library also supports
  *unnamed* parameters; that is to say, parameters whose identity
  can be deduced from their types.

-------------------------------------

:Authors:       David Abrahams, Daniel Wallin
:Contact:       dave@boost-consulting.com, dalwan01@student.umu.se
:Organization:  `Boost Consulting`_
:Date:          $Date: 2005/07/18 20:34:31 $

:Copyright:     Copyright David Abrahams, Daniel Wallin
                2005. Distributed under the Boost Software License,
                Version 1.0. (See accompanying file LICENSE_1_0.txt
                or copy at http://www.boost.org/LICENSE_1_0.txt)

.. _`Boost Consulting`: http://www.boost-consulting.com

.. _concepts: ../../../more/generic_programming.html#concept

-------------------------------------

.. contents:: **Table of Contents**

.. role:: concept
   :class: concept

.. role:: vellipsis
   :class: vellipsis

.. section-numbering::

-------------------------------------

==============
 Motivation
==============

In C++, arguments are normally given meaning by their positions
with respect to a parameter list.  That protocol is fine when there
is at most one parameter with a default value, but when there are
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

It's not uncommon for a function to have parameters that can be
uniquely identified based on the types of arguments passed.  The
``name`` parameter to ``new_window`` is one such example.  None of
the other arguments, if valid, can reasonably be converted to a
``char const*``, so in theory a user could pass the window name in
*any* argument position without causing ambiguity.  The Parameter
library's **unnamed parameter** facility can be employed to allow
that usage:

.. parsed-literal::

  window* w = new_window(movable=false, **"alert box"**); // OK!

Appropriately used, an unnamed parameter interface can free the
user of the burden of even remembering the formal parameter names.

The reasoning we've given for named and unnamed parameter
interfaces applies equally well to class templates as it does to
functions.  The syntax for passing named template parameters is not
quite as natural as it is for named function parameters:

.. parsed-literal::

  // *The ideal would be*
  //    *smart_ptr<ownership=shared, value_type=Client> p;*
  // 
  // *but instead we must write something like:*
  smart_ptr<**ownership<shared>**, **value_type<Client>** > p;

This small syntactic deficiency makes unnamed parameters an
especially big win when used with class templates:

.. parsed-literal::

  // *p and q could be equivalent, given an unnamed*
  // *parameter interface.*
  smart_ptr<**shared**, **Client**> p;
  smart_ptr<**Client**, **shared**> q;

==========
 Tutorial
==========

In this section we'll show how the Parameter library can be used to
build an expressive interface to the `Boost Graph library`__\ 's
|dfs|_ algorithm. [#old_interface]_ 

.. Revisit this

  After laying some groundwork
  and describing the algorithm's abstract interface, we'll show you
  how to build a basic implementation with keyword support.  Then
  we'll add support for default arguments and we'll gradually refine the
  implementation with syntax improvements.  Finally we'll show how to
  streamline the implementation of named parameter interfaces,
  improve their participation in overload resolution, and optimize
  their runtime efficiency.

__ ../../../graph/index.html

.. _dfs: ../../../graph/doc/depth_first_search.html

.. |dfs| replace:: ``depth_first_search``


Headers And Namespaces
======================

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

The Abstract Interface to |dfs|
===============================

The Graph library's |dfs| algorithm is a generic function accepting
from one to four arguments by reference.  If all arguments were
required, its signature might be as follows::

   template <
       class Graph, class DFSVisitor, class Index, class ColorMap
   >
   void depth_first_search(
     , Graph const& graph 
     , DFSVisitor visitor
     , typename graph_traits<g>::vertex_descriptor root_vertex
     , IndexMap index_map
     , ColorMap& color);

However, most of the parameters have a useful default value, as
shown in the table below.

.. _`parameter table`: 
.. _`default expressions`: 

.. table:: ``depth_first_search`` Parameters

  +----------------+----------+----------------------------------+
  | Parameter Name | Dataflow | Default Value (if any)           |
  +================+==========+==================================+
  |``graph``       | in       |none - this argument is required. |
  +----------------+----------+----------------------------------+
  |``visitor``     | in       |``boost::dfs_visitor<>()``        |
  +----------------+----------+----------------------------------+
  |``root_vertex`` | in       |``*vertices(graph).first``        |
  +----------------+----------+----------------------------------+
  |``index_map``   | in       |``get(boost::vertex_index,graph)``|
  +----------------+----------+----------------------------------+
  |``color_map``   | out      |an ``iterator_property_map``      |
  |                |          |created from a ``std::vector`` of |
  |                |          |``default_color_type`` of size    |
  |                |          |``num_vertices(graph)`` and using |
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

  graphs::depth_first_search(g, **color_map=my_color_map**);

To make that syntax legal, there needs to be an object called
``color_map`` with an assignment operator that can accept a
``my_color_map`` argument.  In this step we'll create one such
**keyword object** for each parameter.  Each keyword object will be
identified by a unique **keyword tag type**.  

We're going to define our interface in namespace ``graphs``.  Since
users need access to the keyword objects, but not the tag types,
we'll define the keyword objects so they're acceessible through
``graphs``, and we'll hide the tag types away in a tested
namespace, ``graphs::tag``.  The library provides a convenient
macro for that purpose (MSVC6.x users see this note__)::

  #include <boost/parameter/keyword.hpp>

  namespace graphs
  {
    BOOST_PARAMETER_KEYWORD(tag, graph)    // Note: no semicolon
    BOOST_PARAMETER_KEYWORD(tag, visitor)
    BOOST_PARAMETER_KEYWORD(tag, root_vertex)
    BOOST_PARAMETER_KEYWORD(tag, index_map)
    BOOST_PARAMETER_KEYWORD(tag, color_map)
  }

__ `Compiler Can't See References In Unnamed Namespace`_

The declaration of the ``visitor`` keyword you see here is
equivalent to::

  namespace graphs 
  {
    namespace tag 
    { 
      // The tag type
      struct visitor; 
    }

    namespace // unnamed
    {
      // A reference to the tag object
      boost::parameter::keyword<tag::visitor>& visitor
      = boost::parameter::keyword<tag::visitor>::instance;
    }
  }

This “fancy dance” involving the unnamed namespace and references
is all done to avoid violating the One Definition Rule (ODR)
[#odr]_ when the named parameter interface is used by function
templates that are instantiated in multiple translation
units.

A Bare Bones Function Interface
===============================

Next we can write the skeleton of our ``depth_first_search``
function template.  To declare the function, we'll use the
``BOOST_PARAMETER_FUNCTION`` macro::

  #include <boost/parameter/preprocessor.hpp>

  namespace graphs
  {
    BOOST_PARAMETER_FUNCTION(
        (void), 
        depth_first_search, 

        tag,
        (required (graph,*) )
        (optional (visitor,*) (root_vertex,*) 
                  (index_map,*) (out(color_map),*) )
    )
    {
        // ... body of function goes here...
    }
  }

The first argument to ``BOOST_PARAMETER_FUNCTION`` is the
function's return type, in parentheses.  These parentheses are
necessary because some types, such as ``std::pair<int,int>``,
contain commas that would otherwise confuse the preprocessor.  The
second argument is the name of the resulting function template.
The third argument is the name of the namespace in which keyword
types can be found, but most of the interesting information is in
the fourth argument, which describes the function signature.

The Signature
-------------

The fourth argument to ``BOOST_PARAMETER_FUNCTION`` is a
`Boost.Preprocessor`_ sequence_ of two elements, describing the
required and optional parameters to ``depth_first_search``,
respectively (if the parameters were all required—or all
optional—the sequence would have had only one element).  The first
element specifies a single ``required`` parameter, ``graph``::

   (required (graph,*) )

The ``*`` simply indicates that we can pass anything at all to
``depth_first_search`` as a ``graph``.  The second element of the
outer sequence lists the ``optional`` arguments.
Since there are multiple optional arguments, their entries are
composed into another sequence_.  Note that since the ``color_map`` is an
“out” parameter, its name has been enclosed in the ``out(…)``
construct, which indicates to the library that it should be passed
by non-const reference (for an “in/out” parameter we'd use
``in_out(…)``).  If you refer back to the `parameter table`_ it
should be clear that, default values aside, this function signature
describes the same information.


.. _`Boost.Preprocessor`: ../../preprocessor
.. _sequence: ../../preprocessor/doc/data/sequences.html

Exercising the Interface
------------------------

We've already gained the ability to call our function with a
mixture of positional and named arguments::

  int main()
  {
      // Make keyword names available without qualification
      using namespace graphs;

      graphs::depth_first_search(
        'G', 'v',                               // Positional args
        index_map = "hello, world",             // Named args in
        root_vertex = 3.5, color_map = false);  // arbitrary order
  }

Signature Matching and Overloading
----------------------------------

We can also observe the effects of using ``required`` and
``optional`` in the function signature.  Any invocation of
``depth_first_search`` will compile, as long as it has a ``graph``
parameter::

  depth_first_search("some-graph");                        // OK
  depth_first_search(index_map="hello, world", graph='G'); // OK

however, if we leave out the graph argument, the compiler will
complain that no ``depth_first_search`` matches the arguments::

  depth_first_search(root_vertex=3.5);                     // ERROR

It's important to note that the parameter library is not forcing a
compilation error in this case.  If we add another overload of
``depth_first_search`` that *does* match, the compiler will be
happy again::

  // New overload; matches anything
  template <class T> void depth_first_search(T) {}

  depth_first_search(root_vertex=3.5);                     // OK

This capability depends on your compiler's support for SFINAE. [#sfinae]_

Filling in the Body
===================

.. |ArgumentPack| replace:: :concept:`ArgumentPack`

Of course, the test above isn't very interesting unless we can see
the values of the arguments.  Just to get a feel for how things
work, let's add some temporary code to print the arguments.  The
most natural approach would be to access the arguments directly, by
name::

  {
      std::cout << "graph:\\t" << graph << std::endl;
      std::cout << "visitor:\\t" << visitor << std::endl;
      std::cout << "root_vertex:\\t" << root_vertex << std::endl;
      std::cout << "index_map:\\t" << index_map << std::endl;
      std::cout << "color_map:\\t" << color_map << std::endl;
  }

Unfortunately, that won't quite work, because the function whose
body we'll be writing doesn't have parameters named ``graph``,
``visitor``, etc.  It may not be obvious, since the declaration is
generated by the ``BOOST_PARAMETER_FUNCTION`` macro, but there is
actually only a single parameter, called ``args``.  ``args`` is what
is known as an |ArgumentPack|: a bundle of references to the actual
arguments, tagged with their keywords.  To extract each parameter,
we just need to pass its keyword object to the |ArgumentPack|\ 's
subscript operator, like this:

.. parsed-literal::

  namespace graphs
  {
    BOOST_PARAMETER_FUNCTION(
        (void), 
        depth_first_search, 

        tag,
        (required (graph,\*) )
        (optional (visitor,\*) (root_vertex,\*)
                  (index_map,\*) (out(color_map),\*) )
    )
    {
        std::cout << "graph:\\t" << **args[graph]** << std::endl;
        std::cout << "visitor:\\t" << **args[visitor]** << std::endl;
        std::cout << "root_vertex:\\t" << **args[root_vertex]** << std::endl;
        std::cout << "index_map:\\t" << **args[index_map]** << std::endl;
        std::cout << "color_map:\\t" << **args[color_map]** << std::endl;
    }
  }

Now our program will print::

  graph:       G
  visitor:     2
  root_vertex: 3.5
  index_map:   hello, world
  color_map:   false

Of course, we can pass the arguments in any order without changing
the result::

  int main()
  {
      using namespace graphs;

      graphs::depth_first_search(
        root_vertex = 3.5, graph = 'G', color_map = false, 
        index_map = "hello, world", visitor = 2);
  }

Adding Defaults
===============

Despite the use of ``optional`` in the signature, all
the arguments to ``depth_first_search`` are actually required.  If
any parameter can't be found, there will be a compilation error
where we try to extract it from the |ArgumentPack| using the
subscript operator.  To make it legal to omit an argument we need
to give it a default value.

Syntax
------

To make an optional parameter *truly* optional, we can follow its keyword
with the ``|`` operator and the parameter's default value within
the square brackets.  In the following example, we've given
``root_vertex`` a default of ``42`` and ``color_map`` a default of
``"hello, world"``.

.. parsed-literal::

  namespace graphs 
  {
  {
    BOOST_PARAMETER_FUNCTION(
        (void), 
        depth_first_search, 

        tag,
        (required (graph,\*) )
        (optional (visitor,\*) (root_vertex,\*) 
                  (index_map,\*) (out(color_map),\*) )
    )
    {
        std::cout << "graph:\\t" << args[graph] << std::endl;
        std::cout << "visitor:\\t" << args[visitor] << std::endl;
        std::cout << "root_vertex:\\t" << args[root_vertex\ **|42**\ ] << std::endl;
        std::cout << "index_map:\\t" << args[index_map] << std::endl;
        std::cout << "color_map:\\t" << args[color_map\ **|"hello, world"**\ ] << std::endl;
    }
  }

Now we can invoke the function without supplying ``color_map`` or
``root_vertex``::

  graphs::depth_first_search(
    graph = 'G', index_map = "index", visitor = 6);

The call above would print::

  graph:       G
  visitor:     6
  root_vertex: 42
  index_map:   index
  color_map:   hello, world

.. Important::

   The index expression ``args[…]`` always yields a *reference*
   that is bound either to the actual argument passed by the caller
   or, if no argument is passed explicitly, to the specified
   default value.

Deducing Parameter Types
========================

Now it's time to put some more realistic defaults in place.  We'll
have to give up our print statements—at least if we want to see the
defaults work—since the default values of these
parameters generally aren't printable.

Instead, we'll connect local variables to the arguments and use
those in our algorithm:

.. parsed-literal::

  namespace graphs
  {
    BOOST_PARAMETER_FUNCTION(
        (void), 
        depth_first_search, 

        tag,
        (required (graph,\*) )
        (optional (visitor,\*) (root_vertex,\*)
                  (index_map,\*) (out(color_map),\*) )
    )
    {
        *Graph*   g = args[graph];
        *Visitor* v = args[visitor|\ *default-expression*\ :sub:`1`\ ];
        *Vertex*  s = args[root_vertex|\ *default-expression*\ :sub:`2`\ ];
        *Index*   i = args[index_map|\ *default-expression*\ :sub:`3`\ ];
        *Color*   c = args[color|\ *default-expression*\ :sub:`4`\ ];

        *…use g, v, s, i, and c to implement the algorithm…*
    }
  }

We'll insert the `default expressions`_ in a moment, but first we
need to come up with the types *Graph*, *Visitor*, *Vertex*,
*Index*, and *Color*.

Forwarding to an Implementation Function
----------------------------------------

The easiest way to discover the parameter types is to forward them
on to another function template and allow C++ to do the type
deduction for us:

.. parsed-literal::

  namespace graphs
  {
    namespace detail
    {
      template <
          class Graph, class Visitor
        , class Vertex, class Index, class Color>
      void depth_first_search_impl(
        Graph const& g, Visitor const& v, 
        Vertex const& s, Index const& i, Color& c)
      {
        *…use g, v, s, i, and c to implement the algorithm…*
      }
    }

    BOOST_PARAMETER_FUNCTION(
        (void), 
        depth_first_search, 

        tag,
        (required (graph,\*) )
        (optional (visitor,\*) (root_vertex,\*) 
                  (index_map,\*) (out(color_map),\*) )
    )
    {
        detail::depth_first_search_impl(
          args[graph], args[visitor|\ *default-expression*\ :sub:`1`\ ],
          args[root_vertex|\ *default-expression*\ :sub:`2`\ ],
          args[index_map|\ *default-expression*\ :sub:`3`\ ],
          args[color|\ *default-expression*\ :sub:`4`\ ]);
    }
  }

The ``binding`` |Metafunction|_
-------------------------------

If for some reason forwarding isn't an option, or if writing a
separate implementation function is too cumbersome, we can use a
|Metafunction|_ called ``binding`` to compute parameter types
directly:

.. parsed-literal::

  binding<ArgumentPack, Keyword, Default = parameter::void\ _>
  { typedef *see text* type; };

where ``Default`` is the type of the default argument, if any.

To use ``binding`` we need one more piece of information that's
hidden by the macro generating our declaration: the *type* of
``args``, our ArgumentPack, is quite fittingly available as
``Args``.  Now, to directly declare and initialize ``g``, we could
write:

.. parsed-literal::

  typedef typename parameter::binding<
    Args,\ **tag::graph**
  >::type Graph;

  Graph g = args[graph];

``binding`` With Defaults
-------------------------

As shown in the `parameter table`_, ``graph`` has no default, so
the ``binding`` invocation for *Graph* takes only two arguments.
The default ``visitor`` is ``boost::dfs_visitor<>()``, so the
``binding`` invocation for *Visitor* takes three arguments:

.. parsed-literal::

  typedef typename parameter::binding<
    Args,\ **tag::visitor,boost::dfs_visitor<>**
  >::type Visitor;

  Visitor v = args[visitor|\ **boost::dfs_visitor<>()**\ ];


.. _dangling:

``binding`` Safely
------------------

Note that the default ``visitor`` is supplied as a *temporary*
instance of ``dfs_visitor``.  Because ``args[…]`` always yields
a reference, making ``v`` a reference would cause it to bind to
that temporary, and immediately dangle.  Therefore, it's crucial
that we passed ``dfs_visitor<>``, and not ``dfs_visitor<>
const&``, as the last argument to ``binding``.

.. Important:: 

   Never pass ``binding`` a reference type as the default unless
   you know that the default value passed to the |ArgumentPack|\ 's
   indexing operator will outlive the reference you'll bind to it.

Sometimes there's no need to use ``binding`` at all.  The
``root_vertex`` argument is required to be of the graph's
``vertex_descriptor`` type, [#vertex_descriptor]_ so we can just
declare it that way:

.. parsed-literal::

  typename **boost::graph_traits<Graph>::vertex_descriptor**
    s = args[root_vertex|\ ***vertices(g).first**\ ];

.. |Metafunction| replace:: :concept:`Metafunction`

.. _Metafunction: ../../../mpl/doc/refmanual/metafunction.html


Beyond Ordinary Default Arguments
=================================

Consider how one might bind a variable to the ``index_map``
parameter:

.. parsed-literal::

  typedef typename parameter::binding<
      ArgumentPack
    , tag::index_map
    , **typename boost::property_map<Graph, vertex_index_t>::const_type**
  >::type Index;

  Index i = args[index_map|\ **get(boost::vertex_index,g)**\ ];

We have gained two capabilities beyond what plain C++ default
arguments provide:

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

More Restrictive Signatures
===========================

Currently, our function will be considered for overload resolution
whenever``depth_first_search`` is called with a ``graph`` argument
and up to four others, of any type.  Compilation may fail inside
our ``depth_first_search`` when it is instantiated if the compiler
discovers that the argument types don't provide the required
operations, but that may be too late:

* By the time our ``depth_first_search`` is instantiated, it has
  been selected as the best matching overload.  Some other
  ``depth_first_search`` overload might've worked had it been
  chosen instead.  By the time we see a compilation error, there's
  no chance to change that decision.

* Even if there are no overloads, error messages generated at
  instantiation time usually expose users to confusing
  implementation details.  For example, users might see references
  to ``graphs::detail::depth_first_search_impl`` or worse (think
  of the kinds of errors you get from your STL implementation when
  you make a mistake).

* The problems with exposing such permissive function template
  signatures have been the subject of much discussion, especially
  in the presence of `unqualified calls`__.  If all we want is to
  avoid unintentional argument-dependent lookup (ADL), we can
  isolate ``depth_first_search`` in a namespace containing no
  types [#using]_, but suppose we *want* it to found via ADL?


It's usually a good idea to prevent functions from being considered
for overload resolution when the passed argument types aren't
appropriate.  We've already seen that the library does this when
the required ``graph`` parameter is not supplied.

__ http://anubis.dkuug.dk/jtc1/sc22/wg21/docs/lwg-defects.html#225

Checking for Convertibility to Specific Types
---------------------------------------------

The simplest way to make the signature more restrictive is to
replace some of the ``*``\ s with types to which the corresponding
arguments must be convertible, in parentheses.  For example, the
following signature will only be matched when the
``graph`` parameter is convertible to ``char const*`` and the
``root_vertex`` parameter is convertible to ``int``:

.. parsed-literal::

  namespace graphs
  {
    BOOST_PARAMETER_FUNCTION(
        (void), 
        depth_first_search, 

        tag,
        (required (graph,\ **(char const\*)**) )
        (optional (visitor,\*) (root_vertex,\ **(int)**) 
                  (index_map,\*) (out(color_map),\*) )
    )
    {
        *…*
    }
  }

Signature Restriction Predicates
--------------------------------

Sometimes the appropriate restriction can't be expressed in terms
of convertibility.  In that case, instead of replacing the ``*``,
you can *follow* it with a parenthesized unary `MPL lambda
expression`_ that, when applied to the actual type of the argument,
indicates whether that argument type meets the function's
requirements for that parameter position.

.. _`MPL lambda expression`: ../../../mpl/doc/refmanual/lambda-expression.html

For example, if we want to require that the ``visitor`` parameter
be derived from some class ``VBase``, we can write:

.. parsed-literal::

  namespace graphs
  {
    using namespace boost::mpl;

    BOOST_PARAMETER_FUNCTION(
        (void), 
        depth_first_search, 

        tag,
        (required (graph,(char const\*)) )
        (optional (visitor,\ ***\ (boost::is_base_and_derived<VBase,_>)**)
                  (root_vertex,(int)) (index_map,\*) (out(color_map),\*) )
    )
    {
        *…*
    }
  }

.. Note::

   The restrictions implemented in this section are not realistic
   ones for use with the graph library, and further examples are
   written under the assumption that no such restrictions are in
   effect.

Efficiency Issues
=================

The ``color_map`` parameter gives us a few efficiency issues to
consider.  Here's a first cut at extraction and binding:

.. parsed-literal::

  typedef 
    vector_property_map<boost::default_color_type, Index>
  default_color_map;

  typename parameter::binding<
      ArgumentPack
    , tag::color_map
    , default_color_map
  >::type color = args[color_map|\ **default_color_map(num_vertices(g),i)**\ ];

Eliminating Copies
------------------

The library has no way to know whether an explicitly-supplied
argument is expensive to copy (or even if it is copyable at all),
so ``binding<…,k,…>::type`` is always a reference type when the
*k* parameter is supplied by the caller.  Since ``args[…]``
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

   To avoid making needless copies, pass a *reference to the
   default type* as the third argument to ``binding``, and store
   the default value in a *named* variable.


That said,

.. Note::

   The extra copy becomes a non-issue if we just use the
   forwarding_ technique described earlier.

.. _forwarding: `Forwarding to an Implementation Function`_

Lazy Default Computation
------------------------

Of course it's nice to avoid copying ``default_color``, but the
more important cost is that of *constructing* it in the first
place.  A ``vector_property_map`` is cheap to copy, since it holds
its elements via a |shared_ptr|_.  On the other hand, construction of
``default_color`` costs at least two dynamic memory allocations and
``num_vertices(g)`` copies; it would be better to avoid doing this
work when the default value won't be needed.

.. |shared_ptr| replace:: ``shared_ptr``

.. _shared_ptr: ../../../smart_ptr/shared_ptr.htm

To that end, the library allows us to supply a callable object
that—if no argument was supplied by the caller—will be invoked to
construct the default value.  Instead of following the keyword with
the ``|`` operator, we'll use ``||`` and follow it with a
nullary (zero-argument) function object that constructs a
default_color_map.  Here, we build the function object using
Boost.Lambda_: [#bind]_

.. _Boost.Lambda: ../../../lambda/index.html

.. parsed-literal::

  // After #include <boost/lambda/construct.hpp>
  typename parameter::binding<
      ArgumentPack
    , tag::color_map
    , default_color_map
  >::type color = args[
    color_map
    **|| boost::lambda::construct<default_color_map>(num_vertices(g),i)**
  ];

.. sidebar:: Mnemonics

   To remember the difference between ``|`` and ``||``, recall that
   ``||`` normally uses short-circuit evaluation: its second
   argument is only evaluated if its first argument is ``false``.
   Similarly, in ``color_map[param||f]``, ``f`` is only invoked if
   no ``color_map`` argument was supplied.

Dispatching Based on the Presence of a Default
----------------------------------------------

In fact, the Graph library itself constructs a slightly different
``color_map``, to avoid even the overhead of initializing a
|shared_ptr|_::

   std::vector<boost::default_color_type> 
     color_vec(num_vertices(g));

   boost::iterator_property_map<
       typename std::vector<
          boost::default_color_type
       >::iterator
     , Index
   > c(color_vec.begin(), i);

To avoid instantiating that code when it isn't needed, we'll have
to find a way to select different function implementations, at
compile time, based on whether a ``color_map`` argument was
supplied.  By using `tag dispatching`_ on the presence of a
``color_map`` argument, we can do just that:

.. _`tag dispatching`: ../../../../more/generic_programming.html#tag_dispatching

.. parsed-literal::

  #include <boost/type_traits/is_same.hpp>
  #include <boost/mpl/bool.hpp>

  namespace graphs 
  { 
      template <class ArgumentPack>
    void dfs_dispatch(ArgumentPack& args, **mpl::true_**)
    {
        *…use the color map computed in the previous example…*
    }
    
    template <class ArgumentPack>
    void dfs_dispatch(ArgumentPack& args, **mpl::false_**)
    {
        *…use args[color]…*
    }
    
    BOOST_PARAMETER_FUNCTION(
        (void), 
        depth_first_search, 

        tag,
        (required (graph,*) )
        (optional (visitor,*) (root_vertex,*) 
                  (index_map,*) (out(color_map),*) )
    )
    {
        typedef typename binding<args,tag::color>::type color\_;
        dfs_dispatch(
          args, **boost::is_same<color\_,parameter::void_>()**\ );
    }
  }

We've used the fact that the default for ``binding``\ 's third
argument is ``parameter::void``: because specializations of ``is_same`` are
``bool``-valued MPL |Integral Constant|_\ s derived either
from ``mpl::true_`` or ``mpl::false_``, the appropriate
``dfs_dispatch`` implementation will be selected.

.. |Integral Constant| replace:: :concept:`Integral Constant`

.. _`Integral Constant`: ../../../mpl/doc/refmanual/integral-constant.html

============================
 Portability Considerations
============================

Use the `regression test results`_ for the latest Boost release of
the Parameter library to see how it fares on your favorite
compiler.  Additionally, you may need to be aware of the following
issues and workarounds for particular compilers.

.. _`regression test results`: http://www.boost.org/regression/release/user/parameter.html

No SFINAE Support
=================

Some older compilers don't support SFINAE.  If your compiler meets
that criterion, then Boost headers will ``#define`` the preprocessor
symbol ``BOOST_NO_SFINAE``, and parameter-enabled functions won't be
removed from the overload set based on their signatures.

No Support for |result_of|_
===========================

.. |result_of| replace:: ``result_of``

.. _result_of: ../../../utility/utility.htm#result_of

`Lazy default computation`_ relies on the |result_of| class
template to compute the types of default arguments given the type
of the function object that constructs them.  On compilers that
don't support |result_of|, ``BOOST_NO_RESULT_OF`` will be
``#define``\ d, and the compiler will expect the function object to
contain a nested type name, ``result_type``, that indicates its
return type when invoked without arguments.  To use an ordinary
function as a default generator on those compilers, you'll need to
wrap it in a class that provides ``result_type`` as a ``typedef``
and invokes the function via its ``operator()``.

.. 
  Can't Declare |ParameterSpec| via ``typedef``
  =============================================

  In principle you can declare a |ParameterSpec| as a ``typedef``
  for a specialization of ``parameters<…>``, but Microsoft Visual C++
  6.x has been seen to choke on that usage.  The workaround is to use
  inheritance and declare your |ParameterSpec| as a class:

  .. parsed-literal::

       **struct dfs_parameters
         :** parameter::parameters<
             tag::graph, tag::visitor, tag::root_vertex
           , tag::index_map, tag::color_map
       > **{};**


  Default Arguments Unsupported on Nested Templates
  =================================================

  As of this writing, Borland compilers don't support the use of
  default template arguments on member class templates.  As a result,
  you have to supply ``BOOST_PARAMETER_MAX_ARITY`` arguments to every
  use of ``parameters<…>::match``.  Since the actual defaults used
  are unspecified, the workaround is to use
  |BOOST_PARAMETER_MATCH|_ to declare default arguments for SFINAE.

  .. |BOOST_PARAMETER_MATCH| replace:: ``BOOST_PARAMETER_MATCH``

Compiler Can't See References In Unnamed Namespace
==================================================

If you use Microsoft Visual C++ 6.x, you may find that the compiler
has trouble finding your keyword objects.  This problem has been
observed, but only on this one compiler, and it disappeared as the
test code evolved, so we suggest you use it only as a last resort
rather than as a preventative measure.  The solution is to add
*using-declarations* to force the names to be available in the
enclosing namespace without qualification::

    namespace graphs
    {
      using graphs::graph;
      using graphs::visitor;
      using graphs::root_vertex;
      using graphs::index_map;
      using graphs::color_map;
    }

===========
 Reference
===========

.. _reference: reference.html

Follow `this link`__ to the Boost.Parameter reference
documentation.  

__ reference.html

==================
 Acknowledgements
==================

The authors would like to thank all the Boosters who participated
in the review of this library and its documentation, most
especially our review manager, Doug Gregor.

--------------------------

.. [#old_interface] As of Boost 1.33.0 the Graph library was still
   using an `older named parameter mechanism`__, but there are
   plans to change it to use Boost.Parameter (this library) in an
   upcoming release, while keeping the old interface available for
   backward-compatibility.  

__ ../../../graph/doc/bgl_named_params.html

.. [#odr] The **One Definition Rule** says that any given entity in
   a C++ program must have the same definition in all translation
   units (object files) that make up a program.

.. [#vertex_descriptor] If you're not familiar with the Boost Graph
   Library, don't worry about the meaning of any
   Graph-library-specific details you encounter.  In this case you
   could replace all mentions of vertex descriptor types with
   ``int`` in the text, and your understanding of the Parameter
   library wouldn't suffer.

.. [#bind] The Lambda library is known not to work on `some
   less-conformant compilers`__.  When using one of those you could
   define ::
   
      template <class T>
      struct construct2
      {
          typedef T result_type;

          template <class A1, class A2>
          T operator()(A1 a1, A2 a2) { return T(a1,a2); }
      };

    and use `Boost.Bind`_ to generate the function object::

      boost::bind(construct2<default_color_map>(),num_vertices(g),i)

__ http://www.boost.org/regression/release/user/lambda.html
.. _Boost.Bind: ../../../libs/bind/index.html


.. [#using] You can always give the illusion that the function
   lives in an outer namespace by applying a *using-declaration*::

      namespace foo_overloads
      {
        // foo declarations here
        void foo() { ... }
        ...
      }
      using foo_overloads::foo;

    This technique for avoiding unintentional argument-dependent
    lookup is due to Herb Sutter.


.. [#sfinae] **SFINAE**: **S**\ ubstitution **F**\ ailure **I**\ s
   **N**\ ot **A**\ n **E** rror.  If type substitution during the
   instantiation of a function template results in an invalid type,
   no compilation error is emitted; instead the overload is removed
   from the overload set. By producing an invalid type in the
   function signature depending on the result of some condition,
   we can decide whether or not an overload is considered during overload
   resolution.  The technique is formalized in
   the |enable_if|_ utility.  Most recent compilers support SFINAE;
   on compilers that don't support it, the Boost config library
   will ``#define`` the symbol ``BOOST_NO_SFINAE``.
   See
   http://www.semantics.org/once_weakly/w02_SFINAE.pdf for more
   information on SFINAE.

.. |enable_if| replace:: ``enable_if``
.. _enable_if: ../../../utility/enable_if.html


