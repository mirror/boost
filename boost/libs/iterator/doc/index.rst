+++++++++++++++++++++++++++++++++++++++++++++++++
 The Boost Iterator Library |(logo)|__
+++++++++++++++++++++++++++++++++++++++++++++++++

.. |(logo)| image:: ../../../c++boost.gif
   :alt: Boost

__ ../../../index.htm


-------------------------------------


:Authors:       David Abrahams, Jeremy Siek, Thomas Witt
:Contact:       dave@boost-consulting.com, jsiek@osl.iu.edu, witt@ive.uni-hannover.de
:organizations: `Boost Consulting`_, Indiana University `Open Systems
                Lab`_, University of Hanover `Institute for Transport
                Railway Operation and Construction`_
:date:          $Date$
:copyright:     Copyright David Abrahams, Jeremy Siek, Thomas Witt 2003. All rights reserved

.. _`Boost Consulting`: http://www.boost-consulting.com
.. _`Open Systems Lab`: http://www.osl.iu.edu
.. _`Institute for Transport Railway Operation and Construction`: http://www.ive.uni-hannover.de

:Abstract: The Boost Iterator Library contains two parts. The first
           is a system of concepts_ which extend the C++ standard
           iterator requirements. The second is a framework
           of components for building iterators based on these
           extended concepts and includes several useful iterator
           adaptors. The extended iterator concepts have
           been carefully designed so that new-style iterators will be
           compatible with old-style algorithms, though algorithms may
           need to be updated if they want to take full advantage of
           the new-style iterators.  Several components of this
           library have been proposed for the C++ standard technical
           report.  The components of the Boost Iterator Library
           replace the older Boost Iterator Adaptor Library.

.. _concepts: ../../../more/generic_programming.html#concept

.. contents:: **Table of Contents**


-------------------------------------


=====================
 New-Style Iterators
=====================

The iterator categories defined in C++98 are extremely limiting
because they bind together two orthogonal concepts: traversal and
element access.  For example, because a random access iterator is
required to return a reference (and not a proxy) when dereferenced,
it is impossible to capture the capabilities of
``vector<bool>::iterator`` using the C++98 categories.  This is the
infamous "``vector<bool>`` is not a container, and its iterators
aren't random access iterators", debacle about which Herb Sutter
wrote two papers for the standards comittee (n1185_ and n1211_),
and a `Guru of the Week`__.  New-style iterators go well beyond
patching up ``vector<bool>``, though: there are lots of other
iterators already in use which can't be adequately represented by
the existing concepts.  For details about the new iterator
concepts, see our

.. _n1185: http://www.gotw.ca/publications/N1185.pdf
.. _n1211: http://www.gotw.ca/publications/N1211.pdf
__ http://www.gotw.ca/gotw/050.htm


   `Standard Proposal For New-Style Iterators`__

__ new-iter-concepts.html

=============================
 Iterator Facade and Adaptor
=============================

Writing standard-conforming iterators is tricky.  In order to ease the
implementation of new iterators, the iterator library provides the
|facade|_ class template, which implements many useful
defaults and compile-time checks designed to help the author iterator
ensure that his iterator is correct.  It is common to define a new
iterator which behaves like another iterator, but modifies some aspect
of its behavior.  For that purpose, the library supplies the
|adaptor|_ class template, which is specially designed to
take advantage of as much of the underlying iterator's behavior as
possible. 

.. |facade| replace:: ``iterator_facade``
.. _facade: iterator_facade.html
.. |adaptor| replace:: ``iterator_adaptor``
.. _adaptor: iterator_adaptor.html

Both |facade|_ and |adaptor|_ as well as many of
the `specialized adaptors`_ mentioned below have been proposed for
standardization; see our 

   `Standard Proposal For Iterator Facade and Adaptor`__

for more details.

__ facade-and-adaptor.html

======================
 Specialized Adaptors
======================

The iterator library supplies a useful suite of standard-conforming
iterator templates based on the Boost `iterator facade and adaptor`_.

* |counting|_: an iterator over a sequence of consecutive values.
  Implements a "lazy sequence"

* |filter|_: an iterator over the subset of elements of some
  sequence which satisfy a given predicate

* |indirect|_: an iterator over the objects *pointed-to* by the
  elements of some sequence.

* |permutation|_: an iterator over the elements of some random-access
  sequence, rearranged according to some sequence of integer indices.

* |reverse|_: an iterator which traverses the elements of some
  bidirectional sequence in reverse.  Corrects many of the
  shortcomings of C++98's ``std::reverse_iterator``.

* |transform|_: an iterator over elements which are the result of
  applying some functional transformation to the elements of an
  underlying sequence.  This component also replaces the old
  ``projection_iterator_adaptor``.

.. |counting| replace:: ``counting_iterator``
.. _counting: counting_iterator.html

.. |filter| replace:: ``filter_iterator``
.. _filter: filter_iterator.html

.. |indirect| replace:: ``indirect_iterator``
.. _indirect: indirect_iterator.html

.. |permutation| replace:: ``permutation_iterator``
.. _permutation: permutation_iterator.html

.. |reverse| replace:: ``reverse_iterator``
.. _reverse: reverse_iterator.html

.. |transform| replace:: ``transform_iterator``
.. _transform: transform_iterator.html

====================
 Iterator Utilities
====================

Traits
------

* |iterator_traits|_: Provides MPL_\ -compatible metafunctions which
  retrieve an iterator's traits.  Also corrects for the deficiencies
  of broken implementations of ``std::iterator_traits``.

* |interoperable|_: Provides an MPL_\ -compatible metafunction for
  testing iterator interoperability

.. |iterator_traits| replace:: ``iterator_traits.hpp``
.. _iterator_traits: iterator_traits.html

.. |interoperable| replace:: ``interoperable.hpp``
.. _interoperable: interoperable.html

.. _MPL: ../../mpl/doc/index.html

Testing and Concept Checking
----------------------------

* |iterator_archetypes|_: Add summary here

* |iterator_concepts|_: Add summary

.. |iterator_archetypes| replace:: ``iterator_archetypes.hpp``
.. _iterator_archetypes: iterator_archetypes.html

.. |iterator_concepts| replace:: ``iterator_concepts.hpp``
.. _iterator_concepts: iterator_concepts.html


=======================================================
 Upgrading from the old Boost Iterator Adaptor Library
=======================================================

Turn your policy class into the body of the iterator

Use transform_iterator with a true reference type for
projection_iterator.

=========
 History
=========

In 2000 Dave Abrahams was writing an iterator for a container of
pointers, which would access the pointed-to elements when
dereferenced.  Naturally, being a library writer, he decided to
generalize the idea and the Boost Iterator Adaptor library was born.
Dave was inspired by some writings of Andrei Alexandrescu and chose a
policy based design (though he probably didn't capture Andrei's idea
very well - there was only one policy class for all the iterator's
orthogonal properties).  Soon Jeremy Siek realized he would need the
library and they worked together to produce a "Boostified" version,
which was reviewed and accepted into the library.  They wrote a paper
and made several important revisions of the code.

Eventually, several shortcomings of the older library began to make
the need for a rewrite apparent.  Dave and Jeremy started working at
the Santa Cruz C++ committee meeting in 2002, and had quickly
generated a working prototype.  Thomas Witt expressed interest and
became the voice of compile-time checking for the project...

..
 LocalWords:  Abrahams Siek Witt const bool Sutter's WG int UL LI href Lvalue
 LocalWords:  ReadableIterator WritableIterator SwappableIterator cv pre iter
 LocalWords:  ConstantLvalueIterator MutableLvalueIterator CopyConstructible TR
 LocalWords:  ForwardTraversalIterator BidirectionalTraversalIterator lvalue
 LocalWords:  RandomAccessTraversalIterator dereferenceable Incrementable tmp
 LocalWords:  incrementable xxx min prev inplace png oldeqnew AccessTag struct
 LocalWords:  TraversalTag typename lvalues DWA Hmm JGS
