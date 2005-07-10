+++++++++++++++++++++++++++++++++++++++++++++++++
 The Boost Parameter Library |(logo)|__
+++++++++++++++++++++++++++++++++++++++++++++++++

.. |(logo)| image:: ../../../../boost.png
   :alt: Boost

__ ../../../../index.htm


-------------------------------------


:Authors:       David Abrahams, Daniel Wallin
:Contact:       dave@boost-consulting.com, dalwan01@student.umu.se
:organization:  `Boost Consulting`_
:date:          $Date: 2005/07/10 03:39:35 $

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
between one and four arguments, as shown in the table below:

+----------------+--------------+----------------------------------+
| Parameter Name | Dataflow     | Default Value (if any)           |
+================+==============+==================================+
|``graph``       | IN           |none - this argument is required. |
+----------------+--------------+----------------------------------+
|``visitor``     | OUT          |``boost::dfs_visitor<>()``        |
+----------------+--------------+----------------------------------+
|``index_map``   | IN           |``get(boost::vertex_index,graph)``|
+----------------+--------------+----------------------------------+
|``color_map``   | IN           |                                  |
+----------------+--------------+----------------------------------+

Defining the Keywords
=====================

Defining the Implementation Function
====================================

* Show Use of the Comma Operator at this point

Adding Defaults
===============

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

__ ../../../graph/doc/bgl_named_params.html