+++++++++++++++++++++++++++++++++++++
 Iterator concept and adapter issues 
+++++++++++++++++++++++++++++++++++++

:date: $Date$
:copyright: Copyright David Abrahams, Jeremy Siek, and Thomas Witt 2003.

===================================
 Issues from Matt's TR issues list
===================================

.. contents:: Index

9.1 iterator_access overspecified?
==================================

:Submitter: Pete Becker 
:Status: New 

The proposal includes::

  enum iterator_access { 
     readable_iterator = 1, writable_iterator = 2,
     swappable_iterator = 4, lvalue_iterator = 8
  }; 

In general, the standard specifies thing like this as a bitmask type with a list of defined names, 
and specifies neither the exact type nor the specific values. Is there a reason for iterator_access to 
be more specific? 

:Proposed resolution: The ``iterator_access`` enum will be removed, so
   this is no longer an issue.  See the resolution to 9.15.


9.2 operators of iterator_facade overspecified 
==============================================

:Submitter: Pete Becker 
:Status: New 

In general, we've provided operational semantics for things like
operator++. That is, we've said that ++iter must work, without
requiring either a member function or a non-member function.
iterator_facade specifies most operators as member
functions. There's no inherent reason for these to be members, so
we should remove this requirement. Similarly, some operations are
specified as non-member functions but could be implemented as
members. Again, the standard doesn't make either of these choices,
and TR1 shouldn't, either. So: ``operator*()``, ``operator++()``,
``operator++(int)``, ``operator--()``, ``operator--(int)``,
``operator+=``, ``operator-=``, ``operator-(difference_type)``,
``operator-(iterator_facade instance)``, and ``operator+`` should
be specified with operational semantics and not explicitly required
to be members or non-members.

:Proposed resolution: Not a defect. 

:Rationale: The standard uses valid expressions such as ``++iter`` in
  requirements tables, such as for input iterator.
  However, for classes, such as ``reverse_iterator``,
  the standard uses function prototypes, as we have
  done here for ``iterator_facade``. Further, the prototype
  specification does not prevent the implementor from using members
  or non-members.


9.3 enable_if_interoperable needs standardese
=============================================

:Submitter: Pete Becker 
:Status: New 

The only discussion of what this means is in a note, so is non-normative. Further, the note seems 
to be incorrect. It says that enable_if_interoperable only works for types that "are 
interoperable, by which we mean they are convertible to each other." This requirement is too 
strong: it should be that one of the types is convertible to the other. 
N1541 48 

:Proposed resolution: Pete proposed:

  Remove the enable_if_interoperable stuff, and just write all the
  comparisons to return bool. Then add a blanket statement that the
  behavior of these functions is undefined if the two types aren't
  interoperable.

  **Needs diffs** (fixed in text).

9.4 enable_if_convertible unspecified, conflicts with requires 
==============================================================

:Submitter: Pete Becker 
:Status: New 

In every place where enable_if_convertible is used it's used like
this (simplified)::

  template<class T>
  struct C
  {
    template<class T1>
    C(T1, enable_if_convertible<T1, T>::type* = 0);
  };

The idea being that this constructor won't compile if T1 isn't convertible to T. As a result, the 
constructor won't be considered as a possible overload when constructing from an object x where 
the type of x isn't convertible to T. In addition, however, each of these constructors has a requires 
clause that requires convertibility, so the behavior of a program that attempts such a construction 
is undefined. Seems like the enable_if_convertible part is irrelevant, and should be removed. 
There are two problems. First, enable_if_convertible is never specified, so we don’t 
know what this is supposed to do. Second: we could reasonably say that this overload should be 
disabled in certain cases or we could reasonably say that behavior is undefined, but we can’t say 
both. 

Thomas Witt writes that the goal of putting in enable_if_convertible here is to make 
sure that a specific overload doesn’t interfere with the generic case except when that overload 
makes sense. He agrees that what we currently have is deficient. 
Dave Abrahams writes that there is no conflict with the requires cause because the requires 
clause only takes effect when the function is actually called. The presence of the constructor 
signature 
can/will be detected by is_convertible without violating the requires clause, and thus it makes a 
difference to disable those constructor instantiations that would be disabled by 
enable_if_convertible even if calling them invokes undefined behavior. 
There was more discussion on the reflector: c++std-lib-12312, c++std-lib-12325, c++std-lib-
12330, c++std-lib-12334, c++std-lib-12335, c++std-lib-12336, c++std-lib-12338, c++std-lib-
12362. 

:Proposed resolution: Specify enable_if_convertible to be as-if
  ::

    template <bool> enable_if_convertible_impl
    {};

    template <> enable_if_convertible_impl<true>
    { struct type; };

    template<typename From, typename To>
    struct enable_if_convertible
      : enable_if_convertible_impl<
          is_convertible<From, To>::value>
    {};


9.5 iterator_adaptor has an extraneous 'bool' at the start of the template definition 
=====================================================================================

:Submitter: Pete Becker 
:Status: New 

The title says it all; this is probably just a typo. 

:Proposed resolution: Remove the 'bool'.

9.6 Name of private member shouldn't be normative 
=================================================

:Submitter: Pete Becker 
:Status: New 

iterator_adaptor has a private member named m_iterator. Presumably this is for exposition only, 
since it's an implementation detail. It needs to be marked as such. 

:Proposed resolution: Mark the member m_iterator as exposition
   only.  Note/DWA: I think this is NAD because the user can't
   detect it, though I'm happy to mark it exposition only.

9.7 iterator_adaptor operations specifications are a bit inconsistent 
=====================================================================

:Submitter: Pete Becker 
:Status: New 

iterator_adpator() has a Requires clause, that Base must be default constructible. 
iterator_adaptor(Base) has no Requires clause, although the Returns clause says that the Base 
member is copy construced from the argument (this may actually be an oversight in N1550, 
which doesn't require iterators to be copy constructible or assignable). 

:Proposed resolution:
  Add a requirements section for the template parameters of
  iterator_adaptor, and state that Base must be Copy Constructible and
  Assignable.

  N1550 does in fact include requirements for copy constructible
  and assignable in the requirements tables. To clarify, we've also
  added the requirements to the text.


9.8 Specialized adaptors text should be normative 
=================================================

:Submitter: Pete Becker 
:Status: New 

similar to 9.3, "Specialized Adaptors" has a note describing enable_if_convertible. This should 
be normative text. 

:Proposed resolution: Changed it to normative
  text.  See the resolution of 9.4

9.9 Reverse_iterator text is too informal 
=========================================

:Submitter: Pete Becker 
:Status: New 

reverse iterator "flips the direction of the base iterator's motion". This needs to be more formal, 
as in the current standard. Something like: "iterates through the controlled sequence in the 
opposite direction" 

:Proposed resolution:
  Change the introduction to: The reverse iterator adaptor iterates
  through the adapted iterator range in the opposite direction.


9.10 'prior' is undefined 
=========================

:Submitter: Pete Becker 
:Status: New 

reverse_iterator::dereference is specified as calling a function named 'prior' which has no 
specification. 

:Proposed resolution:
  Change the specification to avoid using ``prior`` as follows.

:Effects: 

::

    Iterator tmp = m_iterator;
    return *--tmp;



9.11 "In other words" is bad wording 
====================================

:Submitter: Pete Becker 
:Status: New 

Transform iterator has a two-part specification: it does this, in other words, it does that. "In other 
words" always means "I didn't say it right, so I'll try again." We need to say it once. 

:Proposed resolution:
  Change:

    The transform iterator adapts an iterator by applying some function
    object to the result of dereferencing the iterator. In other words,
    the ``operator*`` of the transform iterator first dereferences the
    base iterator, passes the result of this to the function object, and
    then returns the result.

  to:

    The transform iterator adapts an iterator by modifying the
    ``operator*`` to apply a function object to the result of
    dereferencing the iterator and returning the result.


9.12 Transform_iterator shouldn't mandate private member 
========================================================

:Submitter: Pete Becker 
:Status: New 

transform_iterator has a private member named 'm_f' which should be marked "exposition only." 

:Proposed resolution: Mark the member ``m_f`` as exposition
  only. Note/DWA: I think this is NAD because the user can't
  detect it, though I'm happy to mark it exposition only.

  Change::

    UnaryFunction m_f;

  to::

    UnaryFunction m_f;   // exposition only



9.13 Unclear description of counting iterator 
=============================================

:Submitter: Pete Becker 
:Status: New 

The description of Counting iterator is unclear. "The counting iterator adaptor implements 
dereference by returning a reference to the base object. The other operations are implemented by 
the base m_iterator, as per the inheritance from iterator_adaptor." 

:Proposed resolution:
  Change the introduction to: ``counting_iterator`` adapts an object by adding an ``operator*`` that
  returns the current value of the object. All other iterator operations
  are forwarded to the adapted object.



9.14 Counting_iterator's difference type 
========================================

:Submitter: Pete Becker 
:Status: New 

Counting iterator has the following note: 

  [Note: implementers are encouraged to provide an implementation
  of distance_to and a difference_type that avoids overflows in the
  cases when the Incrementable type is a numeric type.]

I'm not sure what this means. The user provides a template argument named Difference, but 
there's no difference_type. I assume this is just a glitch in the wording. But if implementors are 
encouraged to ignore this argument if it won't work right, why is it there? 

:Proposed resolution:
  The ``difference_type`` was inherited from ``iterator_adaptor``.
  However, we've removed the explicit inheritance, so explicit typedefs have
  been added.



9.15 How to detect lvalueness? 
==============================

:Submitter: Dave Abrahams 
:Status: New 

Shortly after N1550 was accepted, we discovered that an iterator's lvalueness can be determined 
knowing only its value_type. This predicate can be calculated even for old-style iterators (on 
whose reference type the standard places few requirements). A trait in the Boost iterator library 
does it by relying on the compiler's unwillingness to bind an rvalue to a T& function template 
parameter. Similarly, it is possible to detect an iterator's readability knowing only its value_type. 
Thus, any interface which asks the user to explicitly describe an iterator's lvalue-ness or 
readability seems to introduce needless complexity. 


:Proposed resolution: 

  1. Remove the ``is_writable`` and ``is_swappable`` traits, and remove the
     requirements in the Writable Iterator and Swappable Iterator concepts
     that require their models to support these traits.

  2. Change the ``is_readable`` specification to be:

       ``is_readable<X>::type`` is ``true_type`` if the
       result type of ``X::operator*`` is convertible to
       ``iterator_traits<X>::value_type`` and is ``false_type``
       otherwise. Also, ``is_readable`` is required to satisfy
       the requirements for the UnaryTypeTrait concept
       (defined in the type traits proposal).

     Remove the requirement for support of the ``is_readable`` trait from
     the Readable Iterator concept.


  3. Remove the ``iterator_tag`` class.

  4. Change the specification of ``traversal_category`` to::

      traversal-category(Iterator) =
          let cat = iterator_traits<Iterator>::iterator_category
          if (cat is convertible to incrementable_iterator_tag)
            return cat; // Iterator is a new iterator
          else if (cat is convertible to random_access_iterator_tag)
              return random_access_traversal_tag;
          else if (cat is convertible to bidirectional_iterator_tag)
              return bidirectional_traversal_tag;
          else if (cat is convertible to forward_iterator_tag)
              return forward_traversal_tag;
          else if (cat is convertible to input_iterator_tag)
              return single_pass_iterator_tag;
          else if (cat is convertible to output_iterator_tag)
              return incrementable_iterator_tag;
          else
              return null_category_tag;

:Rationale: 

1. There are two reasons for removing ``is_writable``
   and ``is_swappable``. The first is that we do not know of
   a way to fix the specification so that it gives the correct
   answer for all iterators. Second, there was only a weak
   motivation for having ``is_writable`` and ``is_swappable``
   there in the first place.  The main motivation was simply
   uniformity: we have tags for the old iterator categories
   so we should have tags for the new iterator categories.
   While having tags and the capability to dispatch based
   on the traversal categories is often used, we see
   less of a need for dispatching based on writability
   and swappability, since typically algorithms
   that need these capabilities have no alternative if
   they are not provided.

2. We discovered that the ``is_readable`` trait can be implemented
   using only the iterator type itself and its ``value_type``.
   Therefore we remove the requirement for ``is_readable`` from the
   Readable Iterator concept, and change the definition of
   ``is_readable`` so that it works for any iterator type.

3. The purpose of the ``iterator_tag`` class was to
   bundle the traversal and access category tags
   into the ``iterator_category`` typedef.
   With ``is_writable`` and ``is_swappable`` gone, and
   ``is_readable`` no longer in need of special hints,
   there is no reason for iterators to provide
   information about the access capabilities of an iterator.
   Thus there is no need for the ``iterator_tag``. The
   traversal tag can be directly used for the
   ``iterator_category``. If a new iterator is intended to be backward
   compatible with old iterator concepts, a tag type
   that is convertible to both one of the new traversal tags 
   and also to an old iterator tag can be created and use
   for the ``iterator_category``.

4. The changes to the specification of ``traversal_category`` are a 
   direct result of the removal of ``iterator_tag``.



9.16 is_writable_iterator returns false positives 
=================================================

:Submitter: Dave Abrahams 
:Status: New 

is_writable_iterator returns false positives for forward iterators whose value_type has a private 
assignment operator, or whose reference type is not a reference (currently legal). 

:Proposed Resolution: See the resolution to 9.15.


9.17 is_swappable_iterator returns false positives 
==================================================

:Submitter: Dave Abrahams 
:Status: New 

is_swappable_iterator has the same problems as is_writable_iterator. In addition, if we allow 
users to write their own iter_swap functions it's easy to imagine old-style iterators for which 
is_swappable returns false negatives. 

:Proposed Resolution: See the resolution to 9.15.


9.18 Are is_readable, is_writable, and is_swappable useful? 
===========================================================

:Submitter: Dave Abrahams 
:Status: New 

I am concerned that there is little use for any of is_readable, is_writable, or is_swappable, and 
that not only do they unduly constrain iterator implementors but they add overhead to 
iterator_facade and iterator_adaptor in the form of a template parameter which would otherwise 
be unneeded. Since we can't implement two of them accurately for old-style iterators, I am 
having a hard time justifying their impact on the rest of the proposal(s). 

:Proposed Resolution: See the resolution to 9.15.

9.19 Non-Uniformity of the "lvalue_iterator Bit" 
================================================

:Submitter: Dave Abrahams 
:Status: New 

The proposed iterator_tag class template accepts an "access bits"
parameter which includes a bit to indicate the iterator's
lvalueness (whether its dereference operator returns a reference to
its value_type. The relevant part of N1550 says:

  The purpose of the lvalue_iterator part of the iterator_access
  enum is to communicate to iterator_tagwhether the reference type
  is an lvalue so that the appropriate old category can be chosen
  for the base class. The lvalue_iterator bit is not recorded in
  the iterator_tag::access data member.

The lvalue_iterator bit is not recorded because N1550 aims to
improve orthogonality of the iterator concepts, and a new-style
iterator's lvalueness is detectable by examining its reference
type. This inside/outside difference is awkward and confusing.

:Proposed Resolution: The iterator_tag class will be removed, so this is no longer an issue.
  See the resolution to 9.15.


9.20 Traversal Concepts and Tags 
================================

:Submitter: Dave Abrahams 
:Status: New 

Howard Hinnant pointed out some inconsistencies with the naming of these tag types::

  incrementable_iterator_tag // ++r, r++ 
  single_pass_iterator_tag // adds a == b, a != b 
  forward_traversal_iterator_tag // adds multi-pass 
  bidirectional_traversal_iterator_tag // adds --r, r--
  random_access_traversal_iterator_tag // adds r+n,n+r,etc. 

Howard thought that it might be better if all tag names contained the word "traversal". 
It's not clear that would result in the best possible names, though. For example, incrementable 
iterators can only make a single pass over their input. What really distinguishes single pass 
iterators from incrementable iterators is not that they can make a single pass, but that they are 
equality comparable. Forward traversal iterators really distinguish themselves by introducing 
multi-pass capability. Without entering a "Parkinson's Bicycle Shed" type of discussion, it might 
be worth giving the names of these tags (and the associated concepts) some extra attention. 

:Proposed resolution: Change the names of the traversal tags to the
  following names::

    incrementable_traversal_tag
    single_pass_traversal_tag
    forward_traversal_tag
    bidirectional_traversal_tag
    random_access_traversal_tag


   ** Needs work ** (thw) I still believe that implicit_traversal_tag is more
   appropriate than incrementable_traversal_tag


9.21 iterator_facade Derived template argument underspecified 
=============================================================

:Submitter: Pete Becker 
:Status: New 

The first template argument to iterator_facade is named Derived,
and the proposal says: 

  The Derived template parameter must be a class derived from
  iterator_facade. 

First, iterator_facade is a template, so cannot be derived from. Rather, the class must be derived 
from a specialization of iterator_facade. More important, isn't Derived required to be the class 
that is being defined? That is, if I understand it right, the
definition of D here this is not valid::

  class C : public iterator_facade<C, ... > { ... }; 
  class D : public iterator_facade<C, ...> { ... }; 

In the definition of D, the Derived argument to iterator_facade is a class derived from a 
specialization of iterator_facade, so the requirement is met. Shouldn't the requirement be more 
like "when using iterator_facade to define an iterator class Iter, the class Iter must be derived 
from a specialization of iterator_facade whose first template argument is Iter." That's a bit 
awkward, but at the moment I don't see a better way of phrasing it. 

:Proposed resolution: Add: In addition,
   ``static_cast<Derived*>(iterator_facade*)`` shall be
   well-formed.

9.22 return type of Iterator difference for iterator facade
===========================================================

:Submitter: Pete Becker 
:Status: New 

The proposal says::

  template <class Dr1, class V1, class AC1, class TC1, class R1, class D1, 
  class Dr2, class V2, class AC2, class TC2, class R2, class D2>
  typename enable_if_interoperable<Dr1, Dr2, bool>::type
  operator -(iterator_facade<Dr1, V1, AC1, TC1, R1, D1> const& lhs, 
  iterator_facade<Dr2, V2, AC2, TC2, R2, D2> const& rhs); 

Shouldn't the return type be one of the two iterator types? Which
one? The idea is that if one of the iterator types can be converted
to the other type, then the subtraction is okay. Seems like the
return type should then be the type that was converted to. Is that
right?

:Proposed resolution: **Needs diffs** (fixed in text)

9.23 Iterator_facade: minor wording Issue
=========================================

:Submitter: Pete Becker 
:Status: New 

In the table that lists the required (sort of) member functions of iterator types that are based on 
iterator_facade, the entry for c.equal(y) says: 

  true iff c and y refer to the same position. Implements c == y
  and c != y.  The second sentence is inside out. c.equal(y) does
  not implement either of these operations. It is used to implement
  them. Same thing in the description of c.distance_to(z).

:Proposed resolution: remove "implements" descriptions from
   table.  See resolution to 9.34


9.24 Use of undefined name in iterator_facade table 
===================================================

:Submitter: Pete Becker 
:Status: New 

Several of the descriptions use the name X without defining it. This seems to be a carryover from 
the table immediately above this section, but the text preceding that table says "In the table 
below, X is the derived iterator type." Looks like the X:: qualifiers aren't really needed; 
X::reference can simply be reference, since that's defined by the iterator_facade specialization 
itself. 

:Proposed resolution: Removed the use of X.


9.25 Iterator_facade: wrong return type 
=======================================

:Submitter: Pete Becker 
:Status: New 

Several of the member functions return a Derived object or a Derived&. Their Effects clauses 
end with::

  return *this;

This should be ::

  return *static_cast<Derived*>(this);

:Proposed resolution: 
  Change the returns clause to::

    return *static_cast<Derived*>(this);

  Note/DWA: I think this needs to be a more detailed change list,
  so I'm marking it **Needs language**.

9.26 Iterator_facade: unclear returns clause for operator[] 
===========================================================

:Submitter: Pete Becker 
:Status: New 

The returns clause for ``operator[](difference_type n)`` const
says: 

  Returns: an object convertible to X::reference and holding a copy
  p of a+n such that, for a constant object v of type
  X::value_type, X::reference(a[n] = v) is equivalent to p = v.
  This needs to define 'a', but assuming it's supposed to be
  ``*this`` (or maybe ``*(Derived*)this``), it still isn't clear
  what this says. Presumably, the idea is that you can index off of
  an iterator and assign to the result. But why the requirement
  that it hold a copy of a+n? Granted, that's probably how it's
  implemented, but it seems over-constrained. And the last phrase
  seems wrong. p is an iterator; there's no requirement that you
  can assign a value_type object to it. Should that be ``*p = v``?
  But why the cast in reference(a[n] = v)?

:Proposed resolution: Reworded.

9.27 Iterator_facade: redundant clause 
======================================

:Submitter: Pete Becker 
:Status: New 

``operator-`` has both an effects clause and a returns clause. Looks like the returns clause should be 
removed. 

:Proposed resolution: Remove the returns clause.


9.28 indirect_iterator: incorrect specification of default constructor 
======================================================================

:Submitter: Pete Becker 
:Status: New 

The default constructor returns "An instance of indirect_iterator with a default constructed base 
object", but the constructor that takes an Iterator object returns "An instance of indirect_iterator 
with the iterator_adaptor subobject copy constructed from x." The latter is the correct form, since 
it does not reach inside the base class for its semantics. So the default constructor shoudl return 
"An instance of indirect_iterator with a default-constructed iterator_adaptor subobject." 

:Proposed resolution: Change the specification of the default constructor to

  ``indirect_iterator();``

  :Requires: ``Iterator`` must be Default Constructible.
  :Returns: An instance of ``indirect_iterator`` with 
     a default-constructed ``m_iterator``.


:Rationale: Inheritance from iterator_adaptor has been removed, so we instead
  give the semantics in terms of the (exposition only) member
  ``m_iterator``.


9.29 indirect_iterator: unclear specification of template constructor 
=====================================================================

:Submitter: Pete Becker 
:Status: New 

The templated constructor that takes an indirect_iterator with a different set of template 
arguments says that it returns "An instance of indirect_iterator that is a copy of [the argument]". 
But the type of the argument is different from the type of the object being constructed, and there 
is no description of what a "copy" means. The Iterator template parameter for the argument must 
be convertible to the Iterator template parameter for the type being constructed, which suggests 
that the argument's contained Iterator object should be converted to the target type's Iterator type. 
Is that what's meant here? 
(Pete later writes: In fact, this problem is present in all of the specialized adaptors that have a 
constructor like this: the constructor returns "a copy" of the argument without saying what a 
copy is.) 

:Proposed resolution: Change the specification to

::

  template <
      class Iterator2, class Value2, unsigned Access, class Traversal
    , class Reference2, class Difference2
  >
  indirect_iterator(
      indirect_iterator<
           Iterator2, Value2, Access, Traversal, Reference2, Difference2
      > const& y
    , typename enable_if_convertible<Iterator2, Iterator>::type* = 0 // exposition
  );

:Requires: ``Iterator2`` is implicitly convertible to ``Iterator``.
:Returns: An instance of ``indirect_iterator`` whose 
    ``m_iterator`` subobject is constructed from ``y.base()``.


:Rationale: Inheritance from iterator_adaptor has been removed, so we
  instead give the semantics in terms of the (exposition only) member
  ``m_iterator``.


9.30 transform_iterator argument irregularity 
=============================================

:Submitter: Pete Becker 
:Status: New 

The specialized adaptors that take both a Value and a Reference template argument all take them 
in that order, i.e. Value precedes Reference in the template argument list, with the exception of 
transform_iterator, where Reference precedes Value. This seems like a possible source of 
confusion. Is there a reason why this order is preferable? 

:Proposed resolution: NAD

:Rationale: defaults for Value depend on Reference.  A sensible
   Value can almost always be computed from Reference.  The first
   parameter is UnaryFunction, so the argument order is already
   different from the other adapters.


9.31 function_output_iterator overconstrained 
=============================================

:Submitter: Pete Becker 
:Status: New 

function_output_iterator requirements says: "The UnaryFunction must be Assignable, Copy 
Constructible, and the expression f(x) must be valid, where f is an object of type UnaryFunction 
and x is an object of a type accepted by f." 

Everything starting with "and," somewhat reworded, is actually a constraint on 
output_proxy::operator=. All that's needed to create a function_output_iterator object is that the 
UnaryFunction type be Assignable and CopyConstructible. That's also sufficient to dereference 
and to increment such an object. It's only when you try to assign through a dereferenced iterator 
that f(x) has to work, and then only for the particular function object that the iterator holds and 
for the particular value that is being assigned. 

:Proposed resolution: Remove the part of the sentence
  after "and". Remove the use of ``output_proxy`` and instead
  specify ``operator*`` in the following way.

  ``/* implementation defined */ operator*();``

  :Returns: An object ``r`` of implementation defined type
    such that if ``f(t)`` is a valid expression for
    some object ``t`` then ``r = t`` is a valid expression.
    ``r = t`` will have the same effect as ``f(t)``.


9.32 Should output_proxy really be a named type? 
================================================

:Submitter: Pete Becker 
:Status: New 

This means someone can store an output_proxy object for later use, whatever that means. It also 
constrains output_proxy to hold a copy of the function object, rather than a pointer to the iterator 
object. Is all this mechanism really necessary? 

:Proposed resolution: See issue 9.31.



9.33 istreambuf_iterator isn't a Readable Iterator 
==================================================

:Submitter: Pete Becker 
:Status: New 

c++std-lib-12333: 

  N1550 requires that for a Readable Iterator a of type X, ``*a`` returns an object of type 
  ``iterator_traits<X>::reference``. ``istreambuf_iterator::operator*`` returns ``charT``, but 
  ``istreambuf_iterator::reference`` is ``charT&``. So am I overlooking something, or is 
  ``istreambuf_iterator`` not Readable.

:Proposed resolution:
  Remove all constraints on ``iterator_traits<X>::reference`` in Readable Iterator
  and Lvalue Iterator. Change Lvalue Iterator to refer to ``T&`` instead of
  ``iterator_traits<X>::reference``.

:Rationale: Ideally there should be requirements on the reference type, however,
  since Readable Iterator is suppose to correspond to the current
  standard iterator requirements (which do not place requirements
  on the reference type) we will leave them off for now.
  There is a DR in process with respect to the reference type in the
  stadard iterator requirements. Once that is resolved we will revisit
  this issue for Readable Iterator and Lvalue Iterator.


9.34 iterator_facade free functions unspecified
===============================================

:Submitter: Pete Becker 
:Status: New 

c++std-lib-12562:

  The template functions ``operator==``, ``operator!=``,
  ``operator<``, ``operator<=``, ``operator>``, ``operator>=``, and
  ``operator-`` that take two arguments that are specializations of
  iterator_facade have no specification. The template function
  operator+ that takes an argument that is a specialization of
  iterator_facade and an argument of type difference_type has no
  specification.

:Proposed resolution: **Needs diffs** Added the missing specifications.


9.35 iterator_facade: too many equals? 
======================================

:Submitter: Pete Becker 
:Status: New 

c++std-lib-12563:

  The table listing the functions required for types derived from iterator_facade has two functions
  named equal and two named distance_to::

    c.equal(b)
    c.equal(y)
    c.distance_to(b)
    c.distance_to(z)

  where b and c are const objects of the derived type, y and z are constant objects of certain iterator 
  types that are interoperable with the derived type. 
  Seems like the 'b' versions are redundant: in both cases, the other version will take a 'b'. In fact, 
  iterator_adaptor is specified to use iterator_facade, but does not provide the 'b' versions of these 
  functions. 

  Are the 'b' versions needed? 

:Proposed resolution:  Remove the 'b' versions.


9.36 iterator_facade function requirements 
==========================================

:Submitter: Pete Becker 
:Status: New 

c++std-lib-12636:

  The table that lists required functions for the derived type X passed to iterator_facade lists,
  among others:

  for a single pass iterator::

    c.equal(b)
    c.equal(y)

  where b and c are const X objects, and y is a const object of a single pass iterator that is
  interoperable with X. Since X is interoperable with itself, c.equal(b) is redundant. There is a
  difference in their descriptions, but its meaning isn't clear. The first is "true iff b and c are
  equivalent", and the second is "true iff c and y refer to the same position." Is there a difference
  between the undefined term "equivalent" and "refer to the same position"?

  Similarly, for a random access traversal iterator::

    c.distance_to(b)
    c.distance_to(z)

  where z is a constant object of a random access traversal iterator that is interoperable with X.
  Again, X is interoperable with itself, so c.distance_to(b) is redundant.
  Also, the specification for c.distance_to(z) isn't valid. It's written as "equivalent to distance(c,
  z)". The template function distance takes two arguments of the same type, so distance(c, z) isn't
  valid if c and z are different types. Should it be distance(c, (X)z)?

:Proposed resolution:   Removed the 'b' versions, added the cast.

====================================
 More Issues (not from Matt's list)
====================================



9.37x Inheritance in iterator_adaptor and other adaptors is an overspecification
================================================================================

:Submitter: Pete Becker
:Status: New 

c++std-lib-12696:
The paper requires that iterator_adaptor be derived from an
appropriate instance of iterator_facade, and that most of the specific
forms of adaptors be derived from appropriate instances of
iterator_adaptor. That seems like overspecification, and we ought to
look at specifying these things in terms of what the various templates
provide rather than how they're implemented.

:Proposed resolution:

  Remove the specfication of inheritance, and explicit specification of
  all the functionality that was inherited from the specialized
  iterators. 

  In iterator_adaptor, inheritance is retained, sorry NAD.  Also,
  the Interoperable Iterators concept is added to the new iterator
  concepts, and this concept is used in the specification of the
  iterator adaptors.


9.38x Problem with specification of a->m in Readable Iterator
=============================================================

:Submitter: Howard Hinnant
:Status: New

c++std-lib-12585:

Readable Iterator Requirements says::

    a->m      U&        pre: (*a).m is well-defined. Equivalent to (*a).m

Do we mean to outlaw iterators with proxy references from meeting the  
readable requirements?

Would it be better for the requirements to read ``static_cast<T>(*a).m``
instead of ``(*a).m`` ?

:Proposed resolution: NAD.  

:Rationale: We think you're misreading "pre:".
  If ``(*a).m`` is not well defined, then the iterator is not
  required to provide ``a->m``. So a proxy iterator is not
  required to provide ``a->m``.

  As an aside, it is possible for proxy iterators to
  support ``->``, so changing the requirements to
  read ``static_cast<T>(*a).m`` is interesting.
  However, such a change to Readable Iterator would
  mean that it no longer corresponds to the
  input iterator requirements. So old iterators would not necessarily
  conform to new iterator requirements.


9.39x counting_iterator Traversal argument unspecified
======================================================

:Submitter: Pete Becker

c++std-lib-12635:
 
counting_iterator takes an argument for its Traversal type, with a
default value of use_default. It is derived from an instance of
iterator_adaptor, where the argument passed for the Traversal type
is described as "\ ``/* see details for traversal category
*/``". The details for counting_iterator describe constraints on
the Incrementable type imposed by various traversal
categories. There is no description of what the argument to
iterator_adaptor should be.


:Proposed resolution:
  We no longer inherit from iterator_adaptor. So instead,
  we specify the iterator_category in terms of the Traversal type
  (which is now called CategoryOrTraversal). Also the
  requirements and models section was reorganized to
  match these changes and to make more sense.



9.40x indirect_iterator requirements muddled
============================================

:Submitter: Pete Becker

c++std-lib-12640:

    The value_type of the Iterator template parameter should itself be 
    dereferenceable. The return type of the ``operator*`` for the value_type must 
    be the same type as the Reference template parameter.

  I'd say this a bit differently, to emphasize what's required:
  iterator_traits<Iterator>::value_type must be dereferenceable.
  The Reference template parameter must be the same type as 
  ``*iterator_traits<Iterator>::value_type()``.

    The Value template parameter will be the value_type for the 
    indirect_iterator, unless Value is const. If Value is const X, then 
    value_type will be non- const X.

  Also non-volatile, right? In other words, if Value isn't use_default, it 
  just gets passed as the Value argument for iterator_adaptor.

    The default for Value is::

      iterator_traits< iterator_traits<Iterator>::value_type >::value_type

    If the default is used for Value, then there must be a valid
    specialization of iterator_traits for the value type of the
    base iterator.

  The earlier requirement is that
  ``iterator_traits<Iterator>::value_type`` must be
  dereferenceable. Now it's being treated as an iterator. Is this
  just a pun, or is ``iterator_traits<Iterator>::value_type``
  required to be some form of iterator? If it's the former we need
  to find a different way to say it.  If it's the latter we need to
  say so.

:Proposed resolution:   Resolved **Needs Language**


9.41x Problem with transform_iterator requirements
==================================================

:Submitter: Pete Becker

c++std-lib-12641:

      The reference type of transform_iterator is
      ``result_of<UnaryFunction(iterator_traits<Iterator>::reference)>::type``. The
      ``value_type`` is ``remove_cv<remove_reference<reference> >::type``.

These are the defaults, right? If the user supplies their own types that's
what gets passed to iterator_adaptor. And again, the specification should
be in terms of the specialization of iterator_adaptor, and not in terms of
the result:

Reference argument to iterator_adaptor::

    if (Reference != use_default)
        Reference
    else
        result_of<UnaryFunction(iterator_traits<Iterator>::reference)>::type

Value argument to iterator_adaptor::

    if (Value != use_default)
        Value
    else if (Reference != use_default)
        remove_reference<reference>::type
    else
        remove_reference<result_of<UnaryFunction(iterator_traits<Iterator>::reference)>::type>::type

There's probably a better way to specify that last alternative, but I've
been at this too long, and it's all turning into a maze of twisty passages,
all alike.

:Proposed resolution:
  Replace:

      The reference type of transform_iterator is
      ``result_of<UnaryFunction(iterator_traits<Iterator>::reference)>::type``. The
      ``value_type`` is ``remove_cv<remove_reference<reference> >::type``.

  with:

      If ``Reference`` is ``use_default`` then the ``reference`` member of
      ``transform_iterator`` is
      ``result_of<UnaryFunction(iterator_traits<Iterator>::reference)>::type``.
      Otherwise, ``reference`` is ``Reference``.

      If ``Value`` is ``use_default`` then the ``value_type`` member is
      ``remove_cv<remove_reference<reference> >::type``.  Otherwise,
      ``value_type`` is ``Value``.


9.42x filter_iterator details unspecified
=========================================

:Submitter: Pete Becker

c++std-lib-12642:

The paper says::

    template<class Predicate, class Iterator>
    class filter_iterator
         : public iterator_adaptor<
             filter_iterator<Predicate, Iterator>,
             Iterator,
             use_default,
             /* see details */ >
 
That comment covers the Access, Traversal, Reference, and Difference
arguments. The only specification for any of these in the details is:
 
    The access category of the filter_iterator will be the same as
    the access category of Iterator.
 
Needs more.

:Proposed resolution:
  Add to the synopsis::

      typedef iterator_traits<Iterator>::value_type value_type;
      typedef iterator_traits<Iterator>::reference reference;
      typedef iterator_traits<Iterator>::pointer pointer;
      typedef iterator_traits<Iterator>::difference_type difference_type;
      typedef /* see below */ iterator_category;

  and add just after the synopsis:

      If ``Iterator`` models Readable Lvalue Iterator and Forward Traversal
      Iterator then ``iterator_category`` is convertible to
      ``std::forward_iterator_tag``. Otherwise ``iterator_category`` is
      convertible to ``std::input_iterator_tag``.


9.43x transform_iterator interoperability too restrictive
=========================================================

We do not need to require that the function objects have the same
type, just that they be convertible.

:Proposed resolution:

  Change::

      template<class OtherIterator, class R2, class V2>
      transform_iterator(
            transform_iterator<UnaryFunction, OtherIterator, R2, V2> const& t
          , typename enable_if_convertible<OtherIterator, Iterator>::type* = 0 // exposition
      );

  to::

      template<class F2, class I2, class R2, class V2>
      transform_iterator(
            transform_iterator<F2, I2, R2, V2> const& t
          , typename enable_if_convertible<I2, Iterator>::type* = 0      // exposition only
          , typename enable_if_convertible<F2, UnaryFunction>::type* = 0 // exposition only
      );
