
// Copyright (C) 2009-2012 Lorenzo Caminiti
// Distributed under the Boost Software License, Version 1.0
// (see accompanying file LICENSE_1_0.txt or a copy at
// http://www.boost.org/LICENSE_1_0.txt)
// Home at http://www.boost.org/libs/local_function

#ifndef BOOST_CLOSURE_AUX_CODE_END_HPP_
#define BOOST_CLOSURE_AUX_CODE_END_HPP_

#include <boost/closure/aux_/symbol.hpp>
#include <boost/closure/aux_/config.hpp>
#include <boost/closure/aux_/function.hpp>
#include <boost/closure/aux_/macro/closure.hpp>
#include <boost/closure/aux_/macro/code_/functor.hpp>
#include <boost/closure/detail/preprocessor/keyword/inline.hpp>
#include <boost/typeof/typeof.hpp>
#include <boost/preprocessor/logical/bitor.hpp>
#include <boost/preprocessor/control/iif.hpp>

// PRIVATE //

#define BOOST_CLOSURE_AUX_CODE_END_FUNCTOR_PTR_ \
    BOOST_CLOSURE_AUX_SYMBOL( (functor_ptr) )

#define BOOST_CLOSURE_AUX_CODE_END_FUNCTOR_(id, \
        local_function_name, local_functor_name, nonlocal_functor_name) \
    /* `PARAMS() { ... }` expandsion here -- still within functor class */ \
    /* class functor ## __LINE__ { ... */ \
    public: \
        /* LIMITATION: member var used to deduce functor type using TYPEOF */ \
        /* (so it must be public, ptr to always allow for default init); */ \
        /* unfortunately, this introduces a dependency with Boost.Typeof */ \
        /* that cannot be removed even when all binds and result types are */ \
        /* explicitly specified but this is necessary because the functor */ \
        /* type is known to the CLOSURE macro which must pass it to the */ \
        /* END macro that is defined on a different line */ \
        BOOST_CLOSURE_AUX_CODE_FUNCTOR_TYPE* \
                BOOST_CLOSURE_AUX_CODE_END_FUNCTOR_PTR_; \
    /* local functor can be passed as tparam only on C++11 (faster) */ \
    } local_functor_name(BOOST_CLOSURE_AUX_CLOSURE_ARGS_VAR.value); \
    /* non-local functor can always be passed as tparam (but slower) */ \
    BOOST_TYPEOF(*(local_functor_name.BOOST_CLOSURE_AUX_CODE_END_FUNCTOR_PTR_))\
            nonlocal_functor_name; \
    /* initialization */ \
    local_functor_name.BOOST_CLOSURE_AUX_FUNCTION_INIT_CALL_FUNC( \
            &local_functor_name, nonlocal_functor_name);

#define BOOST_CLOSURE_AUX_CODE_END_FUNCTOR_VAR_(local_function_name) \
    BOOST_CLOSURE_AUX_SYMBOL( (local_function_name) )

// This can always be passed as a template parameters (on all compilers).
// However, it is slower because it cannot be inlined.
// Passed at tparam: Yes (on all C++). Inlineable: No. Recursive: No.
#define BOOST_CLOSURE_AUX_CODE_END_(local_function_name) \
    BOOST_CLOSURE_AUX_CODE_END_FUNCTOR_(__LINE__, local_function_name, \
            /* local functor */ \
            BOOST_CLOSURE_AUX_CODE_END_FUNCTOR_VAR_(local_function_name), \
            /* local function declared as non-local functor -- but it can */ \
            /* be inlined only by C++11 and it cannot be recursive */ \
            local_function_name)

// This is faster on some compilers but not all (e.g., it is faster on GCC
// because its optimization inlines it but not on MSVC). However, it cannot be
// passed as a template parameter on non C++11 compilers.
// Passed at tparam: Only on C++11. Inlineable: Yes. Recursive: No.
#define BOOST_CLOSURE_AUX_CODE_END_INLINE_(local_function_name) \
    BOOST_CLOSURE_AUX_CODE_END_FUNCTOR_(__LINE__, local_function_name, \
            /* inlined local function declared as local functor (maybe */ \
            /* inlined even by non C++11 -- but it can be passed as */ \
            /* template parameter only on C++11 */ \
            local_function_name, \
            /* non-local functor */ \
            BOOST_CLOSURE_AUX_CODE_END_FUNCTOR_VAR_(local_function_name))

// PUBLIC //

// Inlined local functions are specified by `..._NAME(inline name)`.
// They have more chances to be inlined for faster run-times by some compilers
// (for example by GCC but not by MSVC). C++11 compilers can always inline
// local functions even if they are not explicitly specified inline.
#define BOOST_CLOSURE_AUX_CODE_END(qualified_name) \
    BOOST_PP_IIF(BOOST_PP_BITOR( \
            BOOST_CLOSURE_AUX_CONFIG_LOCAL_TYPES_AS_TEMPLATE_PARAMS_01, \
            BOOST_CLOSURE_DETAIL_PP_KEYWORD_IS_INLINE_FRONT(qualified_name)), \
        /* on C++11 always use inlining because compilers might optimize */ \
        /* it to be faster and it can also be passed as tparam */ \
        BOOST_CLOSURE_AUX_CODE_END_INLINE_ \
    , \
        /* on non C++11 don't use liniling unless explicitly specified by */ \
        /* programmers `inline name` the inlined local function cannot be */ \
        /* passed as tparam */ \
        BOOST_CLOSURE_AUX_CODE_END_ \
    )(BOOST_CLOSURE_DETAIL_PP_KEYWORD_INLINE_REMOVE_FRONT(qualified_name))

#endif // #include guard

