
#ifndef BOOST_LOCAL_FUNCTION_AUX_PP_NAME_TRAITS_HPP_
#define BOOST_LOCAL_FUNCTION_AUX_PP_NAME_TRAITS_HPP_

#include <boost/local_function/detail/preprocessor/keyword/recursive.hpp>
#include <boost/local_function/detail/preprocessor/keyword/inline.hpp>
#include <boost/preprocessor/control/iif.hpp>
#include <boost/preprocessor/facilities/empty.hpp>
#include <boost/preprocessor/tuple/elem.hpp>
#include <boost/preprocessor/tuple/eat.hpp>

// PRIVATE //

// Inline and recursive qualifiers.

// Precondition: !recursive01
#define BOOST_LOCAL_FUNCTION_AUX_NAME_TRAITS_RECURSUVE_2ND_CHECK_( \
        function_type, default_count, recursive01, inline01, name) \
    ( \
        function_type \
    , \
        default_count \
    , \
        BOOST_LOCAL_FUNCTION_DETAIL_PP_KEYWORD_IS_RECURSIVE_FRONT(name) \
    , \
        inline01 \
    , \
        BOOST_LOCAL_FUNCTION_DETAIL_PP_KEYWORD_RECURSIVE_REMOVE_FRONT(name) \
    )
    
// Allows for inline and recursive to appear in swapped oder.
#define BOOST_LOCAL_FUNCTION_AUX_NAME_TRAITS_RECURSUVE_2ND_( \
        function_type, default_count, recursive01, inline01, name) \
    BOOST_PP_IIF(recursive01, \
        (function_type, default_count, recursive01, inline01, name) \
        BOOST_PP_TUPLE_EAT(5) \
    , \
        /* going via this macro allows to error if recursive given twice */ \
        BOOST_LOCAL_FUNCTION_AUX_NAME_TRAITS_RECURSUVE_2ND_CHECK_ \
    )(function_type, default_count, recursive01, inline01, name)

#define BOOST_LOCAL_FUNCTION_AUX_NAME_TRAITS_INLINE_( \
        function_type, default_count, recursive01, name) \
    BOOST_LOCAL_FUNCTION_AUX_NAME_TRAITS_RECURSUVE_2ND_( \
          function_type \
        , default_count \
        , recursive01 \
        , BOOST_LOCAL_FUNCTION_DETAIL_PP_KEYWORD_IS_INLINE_FRONT(name) \
        , BOOST_LOCAL_FUNCTION_DETAIL_PP_KEYWORD_INLINE_REMOVE_FRONT(name) \
    )

#define BOOST_LOCAL_FUNCTION_AUX_NAME_TRAITS_RECURSIVE_1ST_( \
        function_type, default_count, name) \
    BOOST_LOCAL_FUNCTION_AUX_NAME_TRAITS_INLINE_( \
          function_type \
        , default_count \
        , BOOST_LOCAL_FUNCTION_DETAIL_PP_KEYWORD_IS_RECURSIVE_FRONT(name) \
        , BOOST_LOCAL_FUNCTION_DETAIL_PP_KEYWORD_RECURSIVE_REMOVE_FRONT(name) \
    )
    
// Default parameter count (defaults).

#define BOOST_LOCAL_FUNCTION_AUX_NAME_TRAITS_DEFAULTS_TUPLE_( \
        function_type, defaults_name) \
    BOOST_LOCAL_FUNCTION_AUX_NAME_TRAITS_RECURSIVE_1ST_(function_type, \
            BOOST_PP_TUPLE_ELEM(2, 0, defaults_name), \
            BOOST_PP_TUPLE_ELEM(2, 1, defaults_name))

#define BOOST_LOCAL_FUNCTION_AUX_NAME_TRAITS_DEFAULTS_SPLIT_(defaults) \
    defaults /* trait not optional, assumed 0 when not specified */ \
    , /* comma splits */

// Precondition: name == `(default_count) ...`
#define BOOST_LOCAL_FUNCTION_AUX_NAME_TRAITS_DEFAULTS_YES_( \
        function_type, name) \
    BOOST_LOCAL_FUNCTION_AUX_NAME_TRAITS_DEFAULTS_TUPLE_(function_type, ( \
            BOOST_LOCAL_FUNCTION_AUX_NAME_TRAITS_DEFAULTS_SPLIT_ name))

#define BOOST_LOCAL_FUNCTION_AUX_NAME_TRAITS_DEFAULTS_NO_( \
        function_type, name) \
    BOOST_LOCAL_FUNCTION_AUX_NAME_TRAITS_RECURSIVE_1ST_(function_type, \
            0 /* assume no defaults if not specified */, name)

#define BOOST_LOCAL_FUNCTION_AUX_NAME_TRAITS_DEFAULTS_(ftype_name) \
    BOOST_PP_IIF(BOOST_PP_IS_UNARY(BOOST_PP_TUPLE_ELEM(2, 1, ftype_name)), \
        BOOST_LOCAL_FUNCTION_AUX_NAME_TRAITS_DEFAULTS_YES_ \
    , \
        BOOST_LOCAL_FUNCTION_AUX_NAME_TRAITS_DEFAULTS_NO_ \
    )(BOOST_PP_TUPLE_ELEM(2, 0, ftype_name), \
            BOOST_PP_TUPLE_ELEM(2, 1, ftype_name))

// Function type (ftype).

#define BOOST_LOCAL_FUNCTION_AUX_NAME_TRAITS_FTYPE_SPLIT_(function_type) \
    function_type BOOST_PP_EMPTY /* optional trait */ \
    , /* comma splits */

// Precondition: name == `(function_type) ...`
#define BOOST_LOCAL_FUNCTION_AUX_NAME_TRAITS_FTYPE_YES_(name) \
    BOOST_LOCAL_FUNCTION_AUX_NAME_TRAITS_DEFAULTS_(( \
            BOOST_LOCAL_FUNCTION_AUX_NAME_TRAITS_FTYPE_SPLIT_ name))

#define BOOST_LOCAL_FUNCTION_AUX_NAME_TRAITS_FTYPE_NO_(name) \
    BOOST_LOCAL_FUNCTION_AUX_NAME_TRAITS_RECURSIVE_1ST_( \
            /* no function type and default specified (EMPTY) */ \
            BOOST_PP_EMPTY, 0 /* no defaults specified */, name)

// PUBLIC //

// name: [(function_type)] [(default_count)] [inline] [recursive] name
#define BOOST_LOCAL_FUNCTION_AUX_PP_NAME_TRAITS(name) \
    BOOST_PP_IIF(BOOST_PP_IS_UNARY(name), \
        BOOST_LOCAL_FUNCTION_AUX_NAME_TRAITS_FTYPE_YES_ \
    , \
        BOOST_LOCAL_FUNCTION_AUX_NAME_TRAITS_FTYPE_NO_ \
    )(name)

// Expand to `[function_type]`.
#define BOOST_LOCAL_FUNCTION_AUX_PP_NAME_TRAITS_FUNCTION_TYPE(name_traits) \
    BOOST_PP_TUPLE_ELEM(5, 0, name_traits)(/* expand empty */)

// Expand to 0, 1, 2, ... (0 if not specified).
#define BOOST_LOCAL_FUNCTION_AUX_PP_NAME_TRAITS_DEFAULTS(name_traits) \
    BOOST_PP_TUPLE_ELEM(5, 1, name_traits)

// Expand to 1 iff function was specified recursive.
#define BOOST_LOCAL_FUNCTION_AUX_PP_NAME_TRAITS_IS_RECURSIVE(name_traits) \
    BOOST_PP_TUPLE_ELEM(5, 2, name_traits)

// Expand to 1 iff function was specified inline.
#define BOOST_LOCAL_FUNCTION_AUX_PP_NAME_TRAITS_IS_INLINE(name_traits) \
    BOOST_PP_TUPLE_ELEM(5, 3, name_traits)

// Expand to (unqualified) function name.
#define BOOST_LOCAL_FUNCTION_AUX_PP_NAME_TRAITS_FUNCTION_NAME(name_traits) \
    BOOST_PP_TUPLE_ELEM(5, 4, name_traits)

#endif // #include guard

