.. Sequences/Intrinsic Metafunctions//sequence_tag

sequence_tag
============

Synopsis
--------

.. parsed-literal::
    
    template<
          typename X
        >
    struct sequence_tag
    {
        typedef |unspecified| type;
    };



Description
-----------

``sequence_tag`` is a |tag-metafunction| for all |tag dispatched| 
`intrinsic sequence operations`__.

__ `Intrinsic Metafunctions`_


Header
------

.. parsed-literal::
    
    #include <boost/mpl/sequence_tag.hpp>


Parameters
----------

+---------------+-------------------+-----------------------------------------------+
| Parameter     | Requirement       | Description                                   |
+===============+===================+===============================================+
| ``X``         | Any type          | A type to obtain a sequence tag for.          |
+---------------+-------------------+-----------------------------------------------+


Expression semantics
--------------------

For any arbitrary type ``x``:


.. parsed-literal::

    typedef sequence_tag<x>::type tag; 

:Return type:
    A type.

:Semantics:
    ``tag`` is an unspecified tag type for ``x``.


Complexity
----------

Amortized constant time.


See also
--------

`Intrinsic Metafunctions`_, |Tag Dispatched Metafunction|
