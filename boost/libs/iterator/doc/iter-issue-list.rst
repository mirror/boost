++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++
 Our Personal Iterator Issue List
++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++

.. _N1550: http://www.boost-consulting.com/writing/n1550.html
.. _N1530: http://anubis.dkuug.dk/jtc1/sc22/wg21/docs/papers/2003/n1530.html

:Author: David Abrahams and Jeremy Siek
:Contact: dave@boost-consulting.com, jsiek@osl.iu.edu
:Organization: `Boost Consulting`_, Indiana University Bloomington
:date: $Date$
:Copyright: Copyright David Abrahams, Jeremy Siek 2003. Use, modification and
      distribution is subject to the Boost Software License,
      Version 1.0. (See accompanying file LICENSE_1_0.txt or copy
      at http://www.boost.org/LICENSE_1_0.txt)

.. _`Boost Consulting`: http://www.boost-consulting.com


.. contents:: Table of Contents


problem with is_writable, is_swappable
======================================

See the separate writeup_.

.. _writeup: ./issues.html


reference requirements in readable iterator
===========================================

The DR has been submitted. This is a placeholder for updating our
proposals with respects to the resolution of that DR.


Subject: N1550: iterator_access overspecified?
==============================================
Date: Fri, 07 Nov 2003 10:25:45 -0500
Message c++std-lib-12262

The proposal includes:
 
enum iterator_access { readable_iterator = 1, writable_iterator = 2,
swappable_iterator = 4, lvalue_iterator = 8 };
 
In general, the standard specifies thing like this as a bitmask type with a
list of defined names, and specifies neither the exact type nor the
specific values. Is there a reason for iterator_access to be more specific?


Resolution
----------

The iterator_access enum has been removed, so this is no longer an issue.




N1530: Minor Issues
===================
Message c++std-lib-12299
Date: Tue, 11 Nov 2003 10:30:36 -0500

1. operators of iterator_facade overspecified. In general, we've provided 
operational semantics for things like operator++. That is, we've said that 
++iter must work, without requiring either a member function or a 
non-member function. iterator_facade specifies most operators as member 
functions. There's no inherent reason for these to be members, so we should 
remove this requirement. Similarly, some operations are specified as 
non-member functions but could be implemented as members. Again, the 
standard doesn't make either of these choices, and TR1 shouldn't, either. 
So: operator*(), operator++(), operator++(int), operator--(), 
operator--(int), operator+=, operator-=, operator-(difference_type), 
operator-(iterator_facade instance), and operator+ should be specified with 
operational semantics and not explicitly required to be members or non-members.

2. enable_if_interoperable needs standardese. The only discussion of what 
this means is in a note, so is non-normative. Further, the note seems to be 
incorrect. It says that enable_if_interoperable only works for types that 
"are interoperable, by which we mean they are convertible to each other." 
This requirement is too strong: it should be that one of the types is 
convertible to the other.

3. iterator_adaptor has an extraneous 'bool' at the start of the template 
definition.

4. iterator_adaptor has a private member named m_iterator. Presumably this 
is for exposition only, since it's an implementation detail. It needs to be 
marked as such.

5. iterator_adaptor operations specifications are a bit inconsistent. 
iterator_adpator() has a Requires clause, that Base must be default 
constructible. iterator_adaptor(Base) has no Requires clause, although the 
Returns clause says that the Base member is copy construced from the 
argument (this may actually be an oversight in N1550, which doesn't require 
iterators to be copy constructible or assignable).

6. similar to 2, "Specialized Adaptors" has a note describing 
enable_if_convertible. This should be normative text.

7. reverse iterator "flips the direction of the base iterator's motion". 
This needs to be more formal, as in the current standard. Something like: 
"iterates through the controlled sequence in the opposite direction"

8. reverse_iterator::dereference is specified as calling a function named 
'prior' which has no specification.

9. Transform iterator has a two-part specification: it does this, in other 
words, it does that. "In other words" always means "I didn't say it right, 
so I'll try again." We need to say it once.

10. similar to 4, transform_iterator has a private member named 'm_f' which 
should be marked "exposition only."

11. The description of Counting iterator is unclear. "The counting iterator 
adaptor implements dereference by returning a reference to the base object. 
The other operations are implemented by the base m_iterator, as per the 
inheritance from iterator_adaptor."

12. Counting iterator has the following note:

[Note: implementers are encouraged to provide an implementation of 
distance_to and a difference_type that avoids overflows in the cases when 
the Incrementable type is a numeric type.]

I'm not sure what this means. The user provides a template argument named 
Difference, but there's no difference_type. I assume this is just a glitch 
in the wording. But if implementors are encouraged to ignore this argument 
if it won't work right, why is it there?


Subject: N1550: iterator_facade Derived template argument underspecified
========================================================================
Message c++std-lib-12302,
Date: Wed, 12 Nov 2003 11:16:49 -0500
 
The first template argument to iterator_facade is named Derived, and the
proposal says:
 
        The Derived template parameter must be a class derived from iterator_facade.
 
First, iterator_facade is a template, so cannot be derived from. Rather,
the class must be derived from a specialization of iterator_facade. More
important, isn't Derived required to be the class that is being defined?
That is, if I understand it right, the definition of D here this is not valid:
 
class C : public iterator_facade<C, ... > { ... };
 
class D : public iterator_facade<C, ...> { ... };
 
In the definition of D, the Derived argument to iterator_facade is a class
derived from a specialization of iterator_facade, so the requirement is
met. Shouldn't the requirement be more like "when using iterator_facade to
define an iterator class Iter, the class Iter must be derived from a
specialization of iterator_facade whose first template argument is Iter."
That's a bit awkward, but at the moment I don't see a better way of
phrasing it.


Subject: N1550: return type of Iterator difference for iterator facade
======================================================================
Date: Wed, 12 Nov 2003 12:20:26 -0500
Message c++std-lib-12303
 
The proposal says:
 
>template <class Dr1, class V1, class AC1, class TC1, class R1, class D1,
>           class Dr2, class V2, class AC2, class TC2, class R2, class D2>
>typename enable_if_interoperable<Dr1, Dr2, bool>::type
>operator -(iterator_facade<Dr1, V1, AC1, TC1, R1, D1> const& lhs,
>            iterator_facade<Dr2, V2, AC2, TC2, R2, D2> const& rhs);
 
Shouldn't the return type be one of the two iterator types? Which one? The
idea is that if one of the iterator types can be converted to the other
type, then the subtraction is okay. Seems like the return type should then
be the type that was converted to. Is that right?



Subject: N1550: Minor Wording Issue
=================================== 
Date: Wed, 12 Nov 2003 13:19:07 -0500
From: Pete Becker <petebecker@acm.org>
Message c++std-lib-12305
 
In the table that lists the required (sort of) member functions of iterator
types that are based on iterator_facade, the entry for c.equal(y) says:
 
>true iff c and y refer to the same position. Implements c == y and c != y.
 
The second sentence is inside out. c.equal(y) does not implement either of
these operations. It is used to implement them. Same thing in the
description of c.distance_to(z).


Subject: N1530: Problems in iterator facade operations
======================================================
Date: Wed, 12 Nov 2003 13:52:55 -0500
From: Pete Becker <petebecker@acm.org>
Message c++std-lib-12308
 
1. Several of the descriptions use the name X without defining it. This
seems to be a carryover from the table immediately above this section, but
the text preceding that table says "In the table below, X is the derived
iterator type." Looks like the X:: qualifiers aren't really needed;
X::reference can simply be reference, since that's defined by the
iterator_facade specialization itself.
 
2. Several of the member functions return a Derived object or a Derived&.
Their Effects clauses end with

::
    
    return *this;

This should be

::

    return *(Derived*)this;
    

3. The returns clause for operator[](difference_type n) const says

::

    Returns: an object convertible to X::reference and holding a copy p of a+n
    such that, for a constant object v of type X::value_type,
    X::reference(a[n] = v) is equivalent to p = v.
    
This needs to define 'a', but assuming it's supposed to be *this (or
maybe *(Derived*)this), it still isn't clear what this
says. Presumably, the idea is that you can index off of an iterator
and assign to the result. But why the requirement that it hold a copy
of a+n? Granted, that's probably how it's implemented, but it seems
over-constrained. And the last phrase seems wrong. p is an iterator;
there's no requirement that you can assign a value_type object to
it. Should that be *p = v? But why the cast in reference(a[n] = v)?
 
4. operator- has both an effects clause and a returns clause. Looks like
the returns clause should be removed.


Subject: N1530: Problems in indirect_iterator operations
========================================================
Date: Wed, 12 Nov 2003 14:49:44 -0500
From: Pete Becker <petebecker@acm.org>
Message c++std-lib-12310
 
1. The default constructor returns "An instance of indirect_iterator with a
default constructed base object", but the constructor that takes an
Iterator object returns "An instance of indirect_iterator with the
iterator_adaptor subobject copy constructed from x." The latter is the
correct form, since it does not reach inside the base class for its
semantics. So the default constructor shoudl return "An instance of
indirect_iterator with a default-constructed iterator_adaptor subobject."
 
2. The templated constructor that takes an indirect_iterator with a
different set of template arguments says that it returns "An instance of
indirect_iterator that is a copy of [the argument]". But the type of the
argument is different from the type of the object being constructed, and
there is no description of what a "copy" means. The Iterator template
parameter for the argument must be convertible to the Iterator template
parameter for the type being constructed, which suggests that the
argument's contained Iterator object should be converted to the target
type's Iterator type. Is that what's meant here?


Resolution
----------

1. As suggested, change the returns clause to read:

:Returns: An instance of ``indirect_iterator`` with a default-constructed
  ``iterator_adaptor`` subobject.


2. Basically, yes. The return clause should be changed to:

:Returns: An instance of ``indirect_iterator`` whose 
  ``iterator_adaptor`` subobject is constructed from ``y.base()``.



Subject: N1530: enable_if_convertible conflicts with requires
=============================================================
Date: Wed, 12 Nov 2003 15:09:48 -0500
From: Pete Becker <petebecker@acm.org>
Message c++std-lib-12312
 
In every place where enable_if_convertible is used it's used like this
(simplified):
 
template<class T>
struct C
{
template<class T1>
C(T1, enable_if_convertible<T1, T>::type* = 0);
};
 
The idea being that this constructor won't compile if T1 isn't convertible
to T. As a result, the constructor won't be considered as a possible
overload when constructing from an object x where the type of x isn't
convertible to T. In addition, however, each of these constructors has a
requires clause that requires convertibility, so the behavior of a program
that attempts such a construction is undefined. Seems like the
enable_if_convertible part is irrelevant, and should be removed.


Subject: N1530: transform_iterator argument irregularity
========================================================
Date: Wed, 12 Nov 2003 15:22:58 -0500
From: Pete Becker <petebecker@acm.org>
Message c++std-lib-12315
 
The specialized adaptors that take both a Value and a Reference template
argument all take them in that order, i.e. Value precedes Reference in the
template argument list, with the exception of transform_iterator, where
Reference precedes Value. This seems like a possible source of confusion.
Is there a reason why this order is prefereable?


Subject: N1530: function_output_iterator
======================================== 
Date: Wed, 12 Nov 2003 15:52:37 -0500
From: Pete Becker <petebecker@acm.org>
Message c++std-lib-12318
 
1. function_output_iterator requirements says: "The UnaryFunction must be
Assignable, Copy Constructible, and the expression f(x) must be valid,
where f is an object of type UnaryFunction and x is an object of a type
accepted by f."
 
Everything starting with "and," somewhat reworded, is actually a constraint
on output_proxy::operator=. All that's needed to create a
function_output_iterator object is that the UnaryFunction type be
Assignable and CopyConstructible. That's also sufficient to dereference and
to increment such an object. It's only when you try to assign through a
dereferenced iterator that f(x) has to work, and then only for the
particular function object that the iterator holds and for the particular
value that is being assigned.
 
2. Should output_proxy really be a named type? This means someone can store
an output_proxy object for later use, whatever that means. It also
constrains output_proxy to hold a copy of the function object, rather than
a pointer to the iterator object. Is all this mechanism really necessary?
 


N1550: istreambuf_iterator isn't a Readable Iterator
====================================================
Date: Thu, 13 Nov 2003 08:24:39 -0500
From: Pete Becker <petebecker@acm.org>
Message c++std-lib-12333
 
N1550 requires that for a Readable Iterator a of type X, *a returns an
object of type iterator_traits<X>::reference.
istreambuf_iterator::operator* returns charT, but
istreambuf_iterator::reference is charT&. So am I overlooking something, or
is istreambuf_iterator not Readable?




Subject: N1530: iterator_facade free functions unspecified
========================================================== 
Date: Tue, 02 Dec 2003 14:44:05 -0500
From: Pete Becker <petebecker@acm.org>
Message c++std-lib-12562


The template functions operator==, operator!=, operator<, operator<=,
operator>, operator>=, and operator- that take two arguments that are
specializations of iterator_facade have no specification. The template
function operator+ that takes an argument that is a specialization of
iterator_facade and an argument of type difference_type has no specification.




Subject: N1530, iterator_facade: too many equals?
=================================================
Date: Tue, 02 Dec 2003 17:24:55 -0500
From: Pete Becker <petebecker@acm.org>
Message c++std-lib-12563

 
The table listing the functions required for types derived from
iterator_facade has two functions named equal and two named distance_to::

    c.equal(b)
    c.equal(y)
 
    c.distance_to(b)
    c.distance_to(z)
 
where b and c are const objects of the derived type, y and z are constant
objects of certain iterator types that are interoperable with the derived type.
 
Seems like the 'b' versions are redundant: in both cases, the other version
will take a 'b'. In fact, iterator_adaptor is specified to use
iterator_facade, but does not provide the 'b' versions of these functions.
 
Are the 'b' versions needed?



Subject: Re: Proposed revision of N1550
=======================================
From: Pete Becker <petebecker@acm.org>
Date: Wed, 03 Dec 2003 13:36:26 -0500
Message c++std-lib-12566

The footnote says:
 
>The UnaryTypeTrait concept is defined in n1519; the LWG added the
>requirement that specializations are derived from their nested ::type.
 
This is not correct. We had a vague discussion of this in Kona and agreed
in principle, but at the time there was no formal proposal. It's in the
issues list as a new issue.


Subject: Re: Proposed revision of N1550
=======================================
Date: Fri, 5 Dec 2003 15:09:32 -0500
From: Howard Hinnant <hinnant@twcny.rr.com>
Message c++std-lib-12585

I'm wading thru

http://boost-consulting.com/boost/libs/iterator/doc/new-iter-concepts.html

and due to my desire to plow through this in a sequential manner, I'm  
having trouble getting past one spot.  I've skimmed through the  
previous discussions and didn't see that this issue was addressed  
(sorry if I missed it).

Readable Iterator Requirements says::

    a->m      U&        pre: (*a).m is well-defined. Equivalent to (*a).m

Do we mean to outlaw iterators with proxy references from meeting the  
readable requirements?

Consider::

    template <class T>
    class proxy_pointer
    {
    public:
	 proxy_pointer(T* t) : t_(t) {}

	 T* operator->() {return t_;}
    private:
	 T* t_;
    };

    template <class T>
    class proxy_reference
    {
    public:
	 proxy_reference(T& t) : t_(&t) {}

	 proxy_reference& operator=(const T& t)
	 {
	     *t_ = t;
	     return *this;
	 }

	 proxy_reference& operator=(const proxy_reference& p)
	 {
	     *t_ = p->t_;
	     return *this;
	 }

	 operator T() const {return *t_;}

	 proxy_pointer<T> operator&() const {return proxy_pointer<T>(t_);}
    private:
	 T* t_;
    };

    template <class T>
    class iterator
    {
    public:
	 typedef proxy_reference<T> reference;
	 typedef proxy_pointer<T> pointer;

	 iterator(T* t) : t_(t) {}
	 reference operator*() const {return reference(*t_);}
	 pointer operator->() const {return pointer(t_);}
    private:
	 T* t_;
    };

    int main()
    {
	 typedef std::pair<int, int> T;
	 T p(1, 2);
	 iterator<T> r(&p);
	 int i = (*r).first;  // error
	 int j = r->first;  // ok
    }

Would it be better for the requirements to read static_cast<T>(*a).m  
instead of (*a).m ?


Subject: N1530: counting_iterator Traversal argument unspecified
================================================================
Date: Tue, 09 Dec 2003 10:09:15 -0500
From: Pete Becker <petebecker@acm.org>
Message c++std-lib-12635
 
counting_iterator takes an argument for its Traversal type, with a default
value of use_default. It is derived from an instance of iterator_adaptor,
where the argument passed for the Traversal type is described as "/* see
details for traversal category */". The details for counting_iterator
describe constraints on the Incrementable type imposed by various traversal
categories. There is no description of what the argument to
iterator_adaptor should be.


Subject: N1530: iterator_facade function requirements
=====================================================
Date: Tue, 09 Dec 2003 10:47:40 -0500
From: Pete Becker <petebecker@acm.org>
Message c++std-lib-12636
 
The table that lists required functions for the derived type X passed to
iterator_facade lists, among others:
 
for a single pass iterator:
c.equal(b)
c.equal(y)
 
where b and c are const X objects, and y is a const object of a single pass
iterator that is interoperable with X. Since X is interoperable with
itself, c.equal(b) is redundant. There is a difference in their
descriptions, but its meaning isn't clear. The first is "true iff b and c
are equivalent", and the second is "true iff c and y refer to the same
position." Is there a difference between the undefined term "equivalent"
and "refer to the same position"?
 
Similarly, for a random access traversal iterator:
c.distance_to(b)
c.distance_to(z)
 
where z is a constant object of a random access traversal iterator that is
interoperable with X. Again, X is interoperable with itself, so
c.distance_to(b) is redundant.
 
Also, the specification for c.distance_to(z) isn't valid. It's written as
"equivalent to distance(c, z)". The template function distance takes two
arguments of the same type, so distance(c, z) isn't valid if c and z are
different types. Should it be distance(c, (X)z)?



Subject: N1530: iterator_facade requirements muddled
====================================================
Date: Tue, 09 Dec 2003 11:20:00 -0500
From: Pete Becker <petebecker@acm.org>
Message c++std-lib-12638

Sorry for the title. The problem is that the section entitled 
"iterator_facade requirements" mixes specification of the implementation 
with specification of constraints on user-supplied types. The specification 
of the implementation isn't really need, though. Paragraph by paragraph:

>Some of the constraints on template parameters to iterator_facade are 
>expressed in terms of resulting nested types and should be viewed in the 
>context of their impact on iterator_traits<Derived>.

This isn't really true, once we go through the rest. Remove it.

>The Derived template parameter must be a class derived from iterator_facade.

There's already an open issue on the wording here. No other changes needed.

>The nested ::value_type type will be the same as remove_cv<Value>::type, 
>so the Value parameter must be an (optionally const-qualified) 
>non-reference type.

The first clause repeats what's already said in the definition of the 
template. The second clause is the important part. Rewrite as:

The Value parameter shall be an optionally const-qualified non-reference type.

>AccessCategory must be an unsigned value which uses no more bits than the 
>greatest value of iterator_access.

There's an open issue in N1550 about the specification of access 
categories. The standard defines "bitmask type" for this purpose. Using it 
removes the problem of determining what "uses no more bits" means.

>The nested ::reference will be the same as the Reference parameter; it 
>must be a suitable reference type for the resulting iterator. The default 
>for the Reference parameter is Value&.

The first clause repeats what's already said in the definition of the 
template. The second clause has no technical meaning. The last sentence is 
part of the specification of the template, and should be moved to the 
definition of the template. Remove this paragraph, and change the template 
argument in the definition of iterator_facade from

         class Reference = /* see below */

to

         class Reference = Value&;

Finally, something that isn't quite as clearcut:

>Depending on the resulting iterator's iterator_category, a subset of the 
>expressions listed in the table are required to be valid.

Is it meaningful to have an iterator that is neither readable nor writable? 
If not, then this can be phrased as "Depending on the template argument 
TraversalCategory", and the first line of the following table can be 
removed from the table and stated as an overall requirement.





Subject: N1530: iterator_adaptor issues
=======================================
Date: Tue, 09 Dec 2003 12:36:44 -0500
From: Pete Becker <petebecker@acm.org>
Message c++std-lib-12639


1. The Derived argument seems to be underspecified. Same problem as 
described in N1541, 9.21 for iterator_facade.

2. The name Base for the iterator that's being adapted (and in the member 
functions base() and base_reference()) is confusing, since it's not a base 
in the sense that the term is used in C++. The templates indirect_iterator 
and reverse_iterator both name their iterator argument Iterator. We should 
do the same here.

3. The clause entitled "iterator_adaptor requirements" talks about 
iterator_traits<Derived>::iterator_category. The base iterator_facade 
defines iterator_category, so it would seem more natural to simply use 
that. Unless, of course, Derived is permitted to provide its own definition 
of iterator_category which is different from the one in the base, or that 
iterator_traits<Derived> can be specialized to provide a differnt one. That 
doesn't seem reasonable, since the type in the base is determined by the 
Access and Traversal arguments that the user passed to iterator_adaptor. 
Why would the user want to define it differently?

4. The clause entitled "iterator_adaptor requirements" sets out 
requirements in terms of the typedefs defined in iterator_facade. It would 
be clearer to specify the arguments that should be passed to iterator_facade:

Value argument to iterator_facade::

    if (Value != use_default)
        Value
    else
        iterator_traits<Base>::value_type

But note that the default here is slightly different from the default 
specified in the paper. The latter can't be implemented correctly with an 
argument to iterator_facade, since iterator_traits<Base>::value_type might 
be cv-qualified, and iterator_facade strips the cv-qualifier. The approch 
I've given strips the cv-qualifier, too. In order to implement what the 
paper says, iterator_adaptor would have to provide its own version of 
value_type.

AccessCategory argument to iterator_facade::

    if (Access != use_default)
	Access
    else if (is_const<Value>)
	access_category<Base>::value & ~writable_iterator
    else
	access_category<Base>::value

This assumes (as does the paper) that there is a suitable definition of 
access_category somewhere (N1550 doesn't specify it).

TraversalCategory argument to iterator_facade::

    if (Traversal != use_default)
	Traversal
    else
	traversal_category<Base>::type

This assumes (as does the paper) that there is a suitable definition of 
traversal_category somewhere (N1550 doesn't specify it).

iterator_category is redundant and should be removed.

Reference argument to iterator_facade::

    if (Reference != use_default)
        Reference
    else if (Value != use_default)
        Value&
    else
        iterator_traits<Base>::reference

The Difference argument to iterator_facade isn't specified here. Needs to 
be added. By analogy, should it be this?::

    if (Difference != use_default)
	Difference
    else
	iterator_traits<Base>::difference_type





Subject: N1530: indirect_iterator requirements muddled
======================================================
Date: Tue, 09 Dec 2003 13:35:20 -0500
From: Pete Becker <petebecker@acm.org>
Message c++std-lib-12640


Part 1
------

>The value_type of the Iterator template parameter should itself be 
>dereferenceable. The return type of the operator* for the value_type must 
>be the same type as the Reference template parameter.

I'd say this a bit differently, to emphasize what's required:

iterator_traits<Iterator>::value_type must be dereferenceable.

The Reference template parameter must be the same type as 
*iterator_traits<Iterator>::value_type().


Resolution
----------

I don't think we want to require default constructible for
``iterator_traits<Iterator>::value_type``, so I've reworded to avoid
that implication.

Change the text to:

The following requirements are placed on the type
``iterator_traits<Iterator>::value_type``. Let ``i`` be an object of
type ``iterator_traits<Iterator>::value_type``.  Then ``*i`` must be a
valid expression, and the type of ``*i`` must be the same as the
``Reference`` template parameter.

Part 2
------

>The Value template parameter will be the value_type for the 
>indirect_iterator, unless Value is const. If Value is const X, then 
>value_type will be non- const X.

Also non-volatile, right? In other words, if Value isn't use_default, it 
just gets passed as the Value argument for iterator_adaptor.


Resolution
----------

Yes, I think that's right. Dave, can you confirm?

Here's the rewording:

The ``Value`` template parameter will be the ``value_type`` for the
``indirect_iterator``, unless ``Value`` is cv-qualified. If ``Value``
is cv-qualified then ``value_type`` will be non-qualified version of
the type.


Part 3
------

>The default for Value is
>
>iterator_traits< iterator_traits<Iterator>::value_type >::value_type
>
>If the default is used for Value, then there must be a valid 
>specialization of iterator_traits for the value type of the base iterator.

The earlier requirement is that iterator_traits<Iterator>::value_type must 
be dereferenceable. Now it's being treated as an iterator. Is this just a 
pun, or is iterator_traits<Iterator>::value_type required to be some form 
of iterator? If it's the former we need to find a different way to say it. 
If it's the latter we need to say so.


Resolution
----------

Dave, help!


Part 4
------

>The Reference parameter will be the reference type of the 
>indirect_iterator. The default is Value&.

That is, the Reference parameter is passed unchanged as the Reference 
argument to iterator_adaptor. Which is what it should say, instead of 
repeating what iterator_adaptor does.

Resolution
----------

Yes.


Part 5
------

>The Access and Traversal parameters are passed unchanged to the 
>corresponding parameters of the iterator_adaptor base class, and the 
>Iterator parameter is passed unchanged as the Base parameter to the 
>iterator_adaptor base class.

Okay, but wordy. We should put it in the template definition:

template<
         class Iterator,
         class Value = use_default,
         class Access = use_default_access,
         class Traversal = use_default,
         class Reference = use_default,
         clsas Difference = use_default>
class indirect_iterator
         : public iterator_adaptor<
                 indirect_iterator<Iterator, Value, Access, Traversal, 
Reference, Difference>,
                 Iterator,
                 /* Value = see below */,
                 Access,
                 Traversal,
                 Reference,
                 Difference>

Resolution
----------

Yes.


Part 6
------

>The indirect iterator will model the most refined standard traversal 
>concept that is modeled by the Iterator type. The indirect iterator will 
>model the most refined standard access concept that is modeled by the 
>value type of Iterator.

That's not strictly true. The Access and Traversal arguments can be more 
restrictive than the Iterator, in which case the operations needed for the 
most refined types are available, but iterator_traits<X>::iterator_category 
won't reflect those capabilities.


Resolution
----------

The indirect iterator will model the most refined standard traversal
concept that is modeled by the ``Iterator`` type and that refines the
traversal category specified in the ``CategoryOrTraversal`` parameter.
The indirect iterator will model the most refined standard access
concept that is modeled by the value type of ``Iterator``.

.. I am not confident in the above. -JGS


Subject: N1530: transform_iterator requirements
===============================================
Date: Tue, 09 Dec 2003 13:42:49 -0500
From: Pete Becker <petebecker@acm.org>
Message c++std-lib-12641
 
>The reference type of transform_iterator is
>result_of<UnaryFunction(iterator_traits<Iterator>::reference)>::type. The
>value_type is remove_cv<remove_reference<reference> >::type.
 
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


 
Subject: N1530: filter_iterator details unspecified
===================================================
Date: Tue, 09 Dec 2003 13:52:21 -0500
From: Pete Becker <petebecker@acm.org>
Message c++std-lib-12642
 
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
 
>The access category of the filter_iterator will be the same as the access
>category of Iterator.
 
Needs more.


