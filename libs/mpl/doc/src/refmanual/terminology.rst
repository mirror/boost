
.. Copyright Aleksey Gurtovoy, David Abrahams 2007.
.. Distributed under the Boost
.. Software License, Version 1.0. (See accompanying
.. file LICENSE_1_0.txt or copy at http://www.boost.org/LICENSE_1_0.txt)

.. _`Overloaded name`:
.. |Overloaded name link| replace:: `Overloaded name`_

Overloaded name
    Overloaded name is a term used in this reference documentation to designate
    a metafunction providing more than one public interface. In reality, 
    class template overloading is nonexistent and the referenced functionality
    is implemented by other, unspecified, means.
    

.. |overloaded name| replace:: `overloaded name <|Overloaded name link|>`__


.. _`Concept-identical`:
.. |Concept-identical link| replace:: `Concept-identical`_

Concept-identical    
    A sequence ``s1`` is said to be concept-identical to a sequence ``s2`` if 
    ``s1`` and ``s2`` model the exact same set of concepts.


.. _`Bind expression`:
.. |Bind expression link| replace:: `Bind expression`_

Bind expression
    A bind expression is simply that |--| an instantiation of one of the |bind| 
    class templates. For instance, these are all bind expressions::
    
        bind< quote3<if_>, _1,int,long >
        bind< _1, bind< plus<>, int_<5>, _2> >
        bind< times<>, int_<2>, int_<2> >

    and these are not::

        if_< _1, bind< plus<>, int_<5>, _2>, _2 >        
        protect< bind< quote3<if_>, _1,int,long > >
        _2


.. |bind expression| replace:: `bind expression <|Bind expression link|>`__
.. |concept-identical| replace:: `concept-identical <|Concept-identical link|>`__
