.. Data Types/Numeric//bool_ |10

bool\_
======

Synopsis
--------

.. parsed-literal::
    
    template<
          bool C
        >
    struct bool\_
    {
        // |unspecified|
        // ...
    };

    typedef bool_<true>  true\_;
    typedef bool_<false> false\_;


Description
-----------

A boolean |Integral Constant| wrapper.


Header
------

.. parsed-literal::
    
    #include <boost/mpl/bool.hpp>


Model of
--------

|Integral Constant|


Parameters
----------

+---------------+-------------------------------+---------------------------+
| Parameter     | Requirement                   | Description               |
+===============+===============================+===========================+
| ``C``         | A boolean integral constant   | A value to wrap.          | 
+---------------+-------------------------------+---------------------------+

Expression semantics
--------------------

|Semantics disclaimer...| |Integral Constant|.

For arbitrary integral constant ``c``:

+-------------------+-----------------------------------------------------------+
| Expression        | Semantics                                                 |
+===================+===========================================================+
| ``bool_<c>``      | An |Integral Constant| ``x`` such that ``x::value == c``  |
|                   | and ``x::value_type`` is identical to ``bool``.           |
+-------------------+-----------------------------------------------------------+


Example
-------

.. parsed-literal::
    
    BOOST_MPL_ASSERT(( is_same< bool_<true>::value_type, bool > ));
    BOOST_MPL_ASSERT(( is_same< bool_<true>, |true_| > )); }
    BOOST_MPL_ASSERT(( is_same< bool_<true>::type, bool_<true> > ));
    BOOST_MPL_ASSERT_RELATION( bool_<true>::value, ==, true );
    assert( bool_<true>() == true );


See also
--------

|Data Types|, |Integral Constant|, |int_|, |long_|, |integral_c|


.. |true_| replace:: |``true_``|__
.. |``true_``| replace:: ``true_``
__ `bool\_`_

.. |false_| replace:: |``false_``|__
.. |``false_``| replace:: ``false_``
__ `bool\_`_
