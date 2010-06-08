.. Macros/Introspection//BOOST_MPL_HAS_XXX_TEMPLATE_NAMED_DEF

.. Copyright Daniel Walker 2007.
.. Distributed under the Boost
.. Software License, Version 1.0. (See accompanying
.. file LICENSE_1_0.txt or copy at http://www.boost.org/LICENSE_1_0.txt)

BOOST_MPL_HAS_XXX_TEMPLATE_NAMED_DEF
====================================

Synopsis
--------

.. parsed-literal::

    #define BOOST_MPL_HAS_XXX_TEMPLATE_NAMED_DEF(trait, name, n, default\_) \\
        |unspecified-token-seq| \\
    /\*\*/


Description
-----------

Expands into the definition of a boolean n-ary |Metafunction| ``trait``
such that for any types ``x, a1, a2, ..., an`` ``trait<x, a1, ...,
an>::value == true`` if and only if ``x`` is a class type and has a
nested template member ``x::template name<a1, ..., an>``.

On deficient compilers not capable of performing the detection,
``trait<x, a1, ..., an>::value`` always returns a fallback value
``default_``.  A boolean configuration macro,
|BOOST_MPL_CFG_NO_HAS_XXX_TEMPLATE|, is provided to signal or override
the "deficient" status of a particular compiler.  |Note:| The fallback
value can also be provided at the point of the metafunction
invocation; see the `Expression semantics` section for details |-- end
note|


Header
------

.. parsed-literal::
    
    #include <boost/mpl/has_xxx.hpp>


Parameters
----------

+---------------+-------------------------------+---------------------------------------------------+
| Parameter     | Requirement                   | Description                                       |
+===============+===============================+===================================================+
| ``trait``     | A legal identifier token      | A name of the metafunction to be generated.       |
+---------------+-------------------------------+---------------------------------------------------+
| ``name``      | A legal identifier token      | A name of the member being detected.              |
+---------------+-------------------------------+---------------------------------------------------+
| ``n``         | An integral constant >= 0     | The arity of the template member being detected.  |
+---------------+-------------------------------+---------------------------------------------------+
| ``default_``  | An boolean constant           | A fallback value for the deficient compilers.     |
+---------------+-------------------------------+---------------------------------------------------+


Expression semantics
--------------------

For any legal C++ identifiers ``trait`` and ``name``, integral
constant expression ``n`` greater than or equal to 0, boolean constant
expression ``c1``, boolean |Integral Constant| ``c2``, and arbitrary
type ``x``:

.. parsed-literal::

    BOOST_MPL_HAS_XXX_TEMPLATE_NAMED_DEF(trait, name, n, c1)

:Precondition:
    Appears at namespace scope.

:Return type:
    None.

:Semantics:
    Expands into an equivalent of the following class template
    definition

    .. parsed-literal::

        template<
            typename X
          , typename A1, ..., typename An
          , typename fallback = boost::mpl::bool\_<c1>
        >
        struct trait
        {
            // |unspecified|
            // ...
        };
    
    where ``trait`` is a boolean |Metafunction| with the following
    semantics:
    
    .. parsed-literal::

        typedef trait<x, a1, ..., an>::type r;

    :Return type:
        |Integral Constant|.

    :Semantics:
        If |BOOST_MPL_CFG_NO_HAS_XXX_TEMPLATE| is defined, ``r::value
        == c1``; otherwise, ``r::value == true`` if and only if ``x``
        is a class type that has a nested type member ``x::template
        name<a1, ..., an>``.
    
    
    .. parsed-literal::

        typedef trait< x, a1, ..., an, c2 >::type r;

    :Return type:
        |Integral Constant|.

    :Semantics:
        If |BOOST_MPL_CFG_NO_HAS_XXX_TEMPLATE| is defined, ``r::value
        == c2::value``; otherwise, equivalent to

        .. parsed-literal::

            typedef trait<x, a1, ..., an>::type r;


Example
-------

.. parsed-literal::
    
    BOOST_MPL_HAS_XXX_TEMPLATE_NAMED_DEF(
        has_xxx, xxx, 1, false
    )

    struct test1  {};
    struct test2  { void xxx(); };
    struct test3  { int xxx; };
    struct test4  { static int xxx(); };
    struct test5  { typedef int xxx; };
    struct test6  { struct xxx; };
    struct test7  { typedef void (\*xxx)(); };
    struct test8  { typedef void (xxx)(); };
    struct test9  { template< class T > struct xxx {}; };

    BOOST_MPL_ASSERT_NOT(( has_xxx<test1, int> ));
    BOOST_MPL_ASSERT_NOT(( has_xxx<test2, int> ));
    BOOST_MPL_ASSERT_NOT(( has_xxx<test3, int> ));
    BOOST_MPL_ASSERT_NOT(( has_xxx<test4, int> ));
    BOOST_MPL_ASSERT_NOT(( has_xxx<test5, int> ));
    BOOST_MPL_ASSERT_NOT(( has_xxx<test6, int> ));
    BOOST_MPL_ASSERT_NOT(( has_xxx<test7, int> ));
    BOOST_MPL_ASSERT_NOT(( has_xxx<test8, int> ));

    #if !defined(BOOST_MPL_CFG_NO_HAS_XXX_TEMPLATE)
    BOOST_MPL_ASSERT(( has_xxx<test9, int> ));
    #endif

    BOOST_MPL_ASSERT(( has_xxx<test9, int, true\_> ));


See also
--------

|Macros|, |BOOST_MPL_HAS_XXX_TEMPLATE_DEF|, |BOOST_MPL_CFG_NO_HAS_XXX_TEMPLATE|

