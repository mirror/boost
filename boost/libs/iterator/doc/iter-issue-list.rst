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


reference requirements in readable iterator
-------------------------------------------

The DR has been submitted. This is a placeholder for updating our
proposals with respects to the resolution of that DR.


Message c++std-lib-12562
------------------------

The template functions operator==, operator!=, operator<, operator<=,
operator>, operator>=, and operator- that take two arguments that are
specializations of iterator_facade have no specification. The template
function operator+ that takes an argument that is a specialization of
iterator_facade and an argument of type difference_type has no specification.


Message c++std-lib-12563
------------------------
 
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


Message c++std-lib-12566
------------------------

The footnote says:
 
>The UnaryTypeTrait concept is defined in n1519; the LWG added the
>requirement that specializations are derived from their nested ::type.
 
This is not correct. We had a vague discussion of this in Kona and agreed
in principle, but at the time there was no formal proposal. It's in the
issues list as a new issue.
