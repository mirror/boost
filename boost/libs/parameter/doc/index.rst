+++++++++++++++++++++++++++++++++++++++++++++++++
 The Boost Parameter Library |(logo)|__
+++++++++++++++++++++++++++++++++++++++++++++++++

.. |(logo)| image:: ../../../boost.png
   :alt: Boost

__ ../../../index.htm


-------------------------------------


:Authors:       David Abrahams, Daniel Wallin
:Contact:       dave@boost-consulting.com, dalwan01@student.umu.se
:organization:  `Boost Consulting`_
:date:          $Date: 2004/11/02 14:31:23 $

:copyright:     Copyright David Abrahams, Daniel Wallin 2005.

.. _`Boost Consulting`: http://www.boost-consulting.com

:Abstract: Use this library to write functions that accept
  arguments in any order as long as the the arguments are
  appropriately labelled at the call site:

  .. parsed-literal::

    new_window("alert", **width=10**, **titlebar=false**);

  This capability is especially useful when a function has more
  than one argument with a useful default value: the user need
  never pass an argument's default value explicitly just because it
  precedes an argument with a non-default value.

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

 * Since an argument's meaning is given by its position,
   we have to choose some (often arbitrary) order for parameters with
   default values, making some combinations of defaults unusable:

   .. parsed-literal::

     window* new_window(
        char const* name, 
        **int border_width = default_border_width,**
        bool movable = true,
        bool initially_visible = true
        );

     const bool movability = false;
     window* w = new_window("alert box", movability);

   In the example above, we wanted to make an unmoveable window
   with a default ``border_width``, but instead we got a moveable
   window with a ``border_width`` of zero.  To get the desired
   effect, we'd need to write:

   .. parsed-literal::

     window* w = new_window(
        "alert box", **default_border_width**, movability);


 * It can become difficult for readers to understand the meaning of
   arguments at the call site::

     window* w = new_window("alert", 1, true, false);

   is this window moveable and initially invisible, or unmoveable
   and initially visible?  The reader needs to remember the order
   of arguments to be sure.  

 * The author of the call may not remember the order of the
   arguments either, leading to hard-to-find bugs.

This library addresses the problems outlined above by associating
each parameter with a keyword object.  Now users can identify
arguments by keyword, rather than by position:

.. parsed-literal::

  window* w = new_window("alert2", **movable=**\ movability); // OK!

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
that you circumvent these limitations quite naturally.

==========
 Tutorial
==========

Introducing the Example
=======================

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


.. Copyright David Abrahams 2005. Distributed under the Boost
.. Software License, Version 1.0. (See accompanying
.. file LICENSE_1_0.txt or copy at http://www.boost.org/LICENSE_1_0.txt)
