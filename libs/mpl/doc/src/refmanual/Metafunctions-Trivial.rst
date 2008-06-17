
.. Copyright Aleksey Gurtovoy, David Abrahams 2007.
.. Distributed under the Boost
.. Software License, Version 1.0. (See accompanying
.. file LICENSE_1_0.txt or copy at http://www.boost.org/LICENSE_1_0.txt)

The MPL provides a number of |Trivial Metafunction|\ s that a nothing more than
thin wrappers for a differently-named class nested type members. While important
in the context of `in-place metafunction composition`__, these metafunctions have
so little to them that presenting them in the same format as the rest of the
compoments in this manual would result in more boilerplate syntactic baggage than
the actual content. To avoid this problem, we instead factor out the common 
metafunctions' requirements into the `corresponding concept`__ and gather all of 
them in a single place |--| this subsection |--| in a compact table form that is 
presented below.

__ `Composition and Argument Binding`_
__ `Trivial Metafunction`_


Trivial Metafunctions Summary
=============================

In the following table, ``x`` is an arbitrary class type.

.. |first| replace:: `:refentry:`first` <|first link|>`__
.. |second| replace:: `:refentry:`second` <|second link|>`__
.. |base| replace:: `:refentry:`base` <|base link|>__

.. |first link| replace:: `trivial-first`_
.. |second link| replace:: `trivial-second`_
.. |base link| replace:: `trivial-base`_


.. _`trivial-first`:
.. _`trivial-second`:
.. _`trivial-base`:


+---------------------------+-------------------------------------------+
| Metafunction              | Header                                    |
+===========================+===========================================+
| ``first<x>::type``        | ``#include <boost/mpl/pair.hpp>``         |
+---------------------------+-------------------------------------------+
| ``second<x>::type``       | ``#include <boost/mpl/pair.hpp>``         |
+---------------------------+-------------------------------------------+
| ``base<x>::type``         | ``#include <boost/mpl/base.hpp>``         |
+---------------------------+-------------------------------------------+


See Also
--------

|Metafunctions|, |Trivial Metafunction|

.. |Trivial Metafunctions| replace:: `Trivial Metafunctions <|Trivial link|>`__
