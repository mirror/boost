+++++++++++++++++++++++++++++++
 Issues With N1550_ and N1530_
+++++++++++++++++++++++++++++++

.. _N1550: http://www.boost-consulting.com/writing/n1550.html
.. _N1530: http://anubis.dkuug.dk/jtc1/sc22/wg21/docs/papers/2003/n1530.html

:Author: David Abrahams
:Contact: dave@boost-consulting.com
:Organization: `Boost Consulting`_
:date: $Date$
:Copyright: Copyright David Abrahams 2003. Use, modification and
      distribution is subject to the Boost Software License,
      Version 1.0. (See accompanying file LICENSE_1_0.txt or copy
      at http://www.boost.org/LICENSE_1_0.txt)

.. _`Boost Consulting`: http://www.boost-consulting.com

.. contents:: Table of Contents

==============
 Introduction
==============

Several issues with N1550_ (New Iterator Concepts) were raised in
the run-up before the fall 2003 C++ Committee meeting, in a thread
beginning with John Maddock's posting ``c++std-lib-12187``.  In
looking at those issues, several other problems came up.  This
document addresses those issues and discusses some potential
solutions and their impact on N1530_ (Iterator Facade and Adaptor).

============
 The Issues
============

Non-Uniformity of the "``lvalue_iterator`` Bit"
===============================================

The proposed ``iterator_tag`` class template accepts an "access
bits" parameter which includes a bit to indicate the iterator's
*lvalueness* (whether its dereference operator returns a reference
to its ``value_type``.  The relevant part of N1550_ says:

  The purpose of the ``lvalue_iterator`` part of the
  ``iterator_access`` enum is to communicate to ``iterator_tag``
  whether the reference type is an lvalue so that the appropriate
  old category can be chosen for the base class. The
  ``lvalue_iterator`` bit is not recorded in the
  ``iterator_tag::access`` data member.

The ``lvalue_iterator`` bit is not recorded because N1550_ aims to
improve orthogonality of the iterator concepts, and a new-style
iterator's lvalueness is detectable by examining its ``reference``
type.  This inside/outside difference is awkward and confusing.

Redundancy of Some Explicit Access Category Flags
=================================================

Shortly after N1550_ was accepted, we discovered that an iterator's
lvalueness can be determined knowing only its ``value_type``.  This
predicate can be calculated even for old-style iterators (on whose
``reference`` type the standard places few requirements).  A trait
in the Boost iterator library does it by relying on the compiler's
unwillingness to bind an rvalue to a ``T&`` function template
parameter.  Similarly, it is possible to detect an iterator's
readability knowing only its ``value_type``. Thus, any interface
which asks the *user* to explicitly describe an iterator's
lvalue-ness or readability seems to introduce needless complexity.

New Access Traits Templates Wrong For Some Iterators
====================================================

``is_writable_iterator``
------------------------

The part of the ``is_writable_iterator`` trait definition which
applies to old-style iterators is::

  if (cat is convertible to output_iterator_tag)
           return true;
      else if (
           cat is convertible to forward_iterator_tag
           and iterator_traits<Iterator>::reference is a 
               mutable reference)
          return true;
      else
          return false;

The current forward iterator requirements place no constraints on
the iterator's ``reference`` type, so the logic above will give
false negatives for some otherwise-writable forward iterators whose
``reference`` type is not a mutable reference.  Also, it will
report false positives for any forward, bidirectional, or random
access iterator whose ``reference`` is a mutable reference but
whose ``value_type`` is not assignable.

``is_swappable_iterator``
-------------------------

Similarly, the part of ``is_swappable_iterator`` which applies to
old-style iterators is::

    else if (cat is convertible to forward_iterator_tag) {
        if (iterator_traits<Iterator>::reference is a const reference)
            return false;
        else
            return true;
    } else 
        return false;

In this case false positives are possible for non-writable forward
iterators whose ``reference`` type is not a reference, or as above,
any forward, bidirectional, or random access iterator whose
``reference`` is not a constant reference but whose ``value_type``
is not assignable (e.g., because it has a private assignment
operator).

False negatives can be "reasoned away": since it is part of a
writable iterator's concept definition that
``is_writable<I>::value`` is ``true``, any iterator for which
it is ``false`` is by definition not writable.  This seems like a
perverse use of logic, though.

It might be reasonable to conclude that it is a defect that the
standard allows forward iterators with a ``reference`` type other
than ``value_type`` *cv*\ ``&``, but that still leaves the problem
of old-style iterators whose ``value_type`` is not assignable.  It
is not possible to correctly compute writability and swappability
for those old-style iterators without intervention
(specializations of ``is_writable_iterator`` and
``is_swappable_iterator``) from a user.

No Use Cases for Some Access Traits 
===================================

``is_swappable_iterator``
-------------------------

``is_swappable_iterator<I>`` is supposed to yield true if
``iter_swap(x,y)`` is valid for instances ``x`` and ``y`` of type
``I``.  The only argument we have heard for
``is_swappable_iterator`` goes something like this:

     *"If* ``is_swappable_iterator`` *yields* ``false``\ *, you
     could fall back to using copy construction and assignment on
     the* ``value_type`` *instead."*

This line of reasoning, however, falls down when closely examined.
To achieve the same effect using copy construction and assignment
on the iterator's ``value_type``, the iterator must be readable and
writable, and its ``value_type`` must be copy-constructible.  But
then, ``iter_swap`` must work in that case, because its default
implementation just calls ``swap`` on the dereferenced iterators.
The only purpose for the swappable iterator concept is to represent
iterators which do not fulfill the properties listed above, but
which are nonetheless swappable because the user has provided an
overload or specialization of ``iter_swap``.  In other words,
generic code which wants to swap the referents of two iterators
should *always* call ``iter_swap`` instead of doing the
assignments.

``is_writable_iterator``
------------------------

Try to imagine a case where ``is_writable_iterator`` can be used to
choose behavior.  Since the only requirement on a writable iterator
is that we can assign into its referent, the only use for
``is_writable_iterator`` in selecting behavior is to modify a
sequence when the sequence is mutable, and to not modify it
otherwise.

There is no precedent for generic functions which modify their
arguments only if the arguments are non-const reference, and with
good reason: the simple fact that data is mutable does not mean
that a user *intends* it to be mutated.  We provide ``const`` and
non-\ ``const`` overloads for functions like ``operator[]``, but
these do not modify data; they merely return a reference to data
which preserves the object's mutability properties.  We can do the
same with iterators using their ``reference`` types; the
accessibility of an assignment operator on the ``value_type``,
which determines writability, does not change that.

The one plausible argument we can imagine for
``is_writable_iterator`` and ``is_swappable_iterator`` is to remove
algorithms from an overload set using a SFINAE technique like
enable_if_, but that seems to be too small a gain for the
requirements imposed on iterator implementors by the need to report
writability and swappability, especially since it can't be done
correctly for all existing iterators.

.. _enable_if: http://tinyurl.com/tsr7

===================
 Proposed Solution
===================

(incomplete)

Change ``iterator_traits`` as follows::

  iterator_traits<I>::iterator_category
    = if (I::iterator_category is a type) // use mpl::has_xxx (SFINAE)
         return I::iterator_category

      if (iterator_value_type<I>::type is void
          || iterator_difference_type<I>::type is void
      )
         return std::output_iterator_tag

      t = iterator_traversal<I>::type
      
      if (is_lvalue_iterator<I>::value)
      {
         if (t is convertible to random_access_traversal_tag)
            return std::random_access_iterator_tag
         if (t is convertible to bidirectional_traversal_tag)
            return std::bidirectional_iterator_tag
         else if (t is convertible to forward_traversal_tag)
            return std::forward_iterator_tag
      }

      if (t is convertible to single_pass_traversal_tag
          && is_readable_iterator<I>::value
      )
         return input_output_iterator_tag // (**)
      else
         return std::output_iterator_tag


