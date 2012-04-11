
// Copyright (C) 2009-2012 Lorenzo Caminiti
// Distributed under the Boost Software License, Version 1.0
// (see accompanying file LICENSE_1_0.txt or a copy at
// http://www.boost.org/LICENSE_1_0.txt)
// Home at http://www.boost.org/libs/local_function

#ifndef BOOST_LOCAL_FUNCTION_AUX_NAME_HPP_
#define BOOST_LOCAL_FUNCTION_AUX_NAME_HPP_


#include <boost/local_function/config.hpp>
#include <boost/local_function/aux_/macro/decl.hpp>
#include <boost/local_function/aux_/macro/code_/functor.hpp>
#include <boost/local_function/aux_/preprocessor/traits/name.hpp>
#include <boost/local_function/aux_/function.hpp>
#include <boost/local_function/aux_/symbol.hpp>
#include <boost/typeof/typeof.hpp>
#include <boost/preprocessor/control/iif.hpp>
#include <boost/preprocessor/control/expr_iif.hpp>
#include <boost/preprocessor/logical/bitor.hpp>
#include <boost/preprocessor/tuple/eat.hpp>

// PRIVATE //

#define BOOST_LOCAL_FUNCTION_AUX_NAME_INIT_RECURSION_FUNC_ \
    BOOST_LOCAL_FUNCTION_AUX_SYMBOL( (init_recursion) )

#define BOOST_LOCAL_FUNCTION_AUX_NAME_RECURSIVE_FUNC_(name_traits) \
    BOOST_PP_IIF(BOOST_LOCAL_FUNCTION_AUX_PP_NAME_TRAITS_IS_RECURSIVE( \
            name_traits), \
        BOOST_LOCAL_FUNCTION_AUX_PP_NAME_TRAITS_FUNCTION_NAME \
    , \
        BOOST_LOCAL_FUNCTION_AUX_SYMBOL( (nonrecursive_local_function_name) ) \
        BOOST_PP_TUPLE_EAT(1) \
    )(name_traits)
    
#define BOOST_LOCAL_FUNCTION_AUX_NAME_FUNCTOR_TYPEOF_( \
        typename01, name_traits, local_functor_name) \
    BOOST_PP_IIF(typename01, \
        BOOST_TYPEOF_TPL \
    , \
        BOOST_TYPEOF \
    )(local_functor_name.BOOST_LOCAL_FUNCTION_AUX_NAME_RECURSIVE_FUNC_( \
            name_traits))

#define BOOST_LOCAL_FUNCTION_AUX_NAME_FUNCTOR_TYPED_( \
        typename01, name_traits, local_functor_name) \
    BOOST_PP_EXPR_IIF(typename01, typename) \
    BOOST_IDENTITY_TYPE((::boost::local_function::aux::function< \
          BOOST_LOCAL_FUNCTION_AUX_PP_NAME_TRAITS_FUNCTION_TYPE( \
                name_traits) \
        , BOOST_LOCAL_FUNCTION_AUX_PP_NAME_TRAITS_DEFAULTS(name_traits) \
    >))

#define BOOST_LOCAL_FUNCTION_AUX_NAME_FUNCTOR_TYPE_( \
        typename01, name_traits, local_functor_name) \
    BOOST_PP_IIF(BOOST_PP_IS_EMPTY( \
            BOOST_LOCAL_FUNCTION_AUX_PP_NAME_TRAITS_FUNCTION_TYPE( \
                    name_traits)), \
        BOOST_LOCAL_FUNCTION_AUX_NAME_FUNCTOR_TYPEOF_ \
    , \
        BOOST_LOCAL_FUNCTION_AUX_NAME_FUNCTOR_TYPED_ \
    )(typename01, name_traits, local_functor_name)

#define BOOST_LOCAL_FUNCTION_AUX_NAME_LOCAL_FUNCTOR_(typename01, name_traits, \
        local_functor_name, nonlocal_functor_name) \
    /* `PARAMS() { ... }` expandsion here -- still within functor class */ \
    /* class functor ## __LINE__ { ... */ \
    public: \
        /* member var with function name for recursive calls; must be */ \
        /* `public` because is it also used by this macro but outside */ \
        /* the functor class to deduce the functor type; it cannot be */ \
        /* `const` because it is init after construction (because */ \
        /* constructor doesn't know local function name) */ \
        /* run-time: even when optimizing, recursive calls cannot be */ \
        /* optimized (i.e., they must be via the non-local functor) */ \
        /* because this cannot be a mem ref because its name is not known */ \
        /* by the constructor so it cannot be set by the mem init list */ \
        BOOST_LOCAL_FUNCTION_AUX_CODE_FUNCTOR_TYPE \
                BOOST_LOCAL_FUNCTION_AUX_NAME_RECURSIVE_FUNC_(name_traits); \
        BOOST_PP_EXPR_IIF(BOOST_LOCAL_FUNCTION_AUX_PP_NAME_TRAITS_IS_RECURSIVE(\
                name_traits), \
            /* run-time: the `init_recursion()` function cannot be called */ \
            /* by the constructor to allow for compiler optimization */ \
            /* (inlining) so it must be public */ \
            inline void BOOST_LOCAL_FUNCTION_AUX_NAME_INIT_RECURSION_FUNC_( \
                    BOOST_LOCAL_FUNCTION_AUX_CODE_FUNCTOR_TYPE& functor) { \
                BOOST_LOCAL_FUNCTION_AUX_PP_NAME_TRAITS_FUNCTION_NAME( \
                        name_traits) = functor; \
            } \
        ) \
    /* local functor can be passed as tparam only on C++11 (faster) */ \
    } local_functor_name(BOOST_LOCAL_FUNCTION_AUX_DECL_ARGS_VAR.value); \
    /* non-local functor can always be passed as tparam (but slower) */ \
    BOOST_LOCAL_FUNCTION_AUX_NAME_FUNCTOR_TYPE_(typename01, name_traits, \
            local_functor_name) nonlocal_functor_name; /* functor variable */ \
    /* the order of the following 2 function calls cannot be changed */ \
    /* because init_recursion uses the local_functor so the local_functor */ \
    /* must be init first */ \
    local_functor_name.BOOST_LOCAL_FUNCTION_AUX_FUNCTION_INIT_CALL_FUNC( \
            &local_functor_name, nonlocal_functor_name); \
    BOOST_PP_EXPR_IIF(BOOST_LOCAL_FUNCTION_AUX_PP_NAME_TRAITS_IS_RECURSIVE( \
            name_traits), \
        /* init recursion causes MSVC to not optimize local function not */ \
        /* even when local functor is used as template parameter so no */ \
        /* recursion unless all inlining optimizations are specified off */ \
        local_functor_name.BOOST_LOCAL_FUNCTION_AUX_NAME_INIT_RECURSION_FUNC_( \
                nonlocal_functor_name); \
    )

#define BOOST_LOCAL_FUNCTION_AUX_NAME_FUNCTOR_(local_function_name) \
    BOOST_LOCAL_FUNCTION_AUX_SYMBOL( (local_function_name) )

// PUBLIC //

// If !INLINE(name_traits) && !RECURSIVE(name_traits):
//      This can always be passed as a template parameters (on all compilers).
//      However, it is slower because it cannot be inlined.
// If !INLINE(name_traits) && RECURSIVE(name_traits):
//      This is slower on all compilers (C++11 and non) because recursion and
//      its initialization can never be inlined.
// If INLINE(name_traits) && !RECURSIVE(name_traits):
//      This is faster on some compilers but not all (e.g., it is faster on GCC
//      because its optimization inlines it but not on MSVC). However, it
//      cannot be passed as a template parameter on non C++11 compilers.
// If INLINE(name_traits) && RECURSIVE(name_traits):
//      Same as RECURSIVE && !INLINE.
#define BOOST_LOCAL_FUNCTION_AUX_NAME(typename01, name_traits) \
    BOOST_PP_EXPAND( \
        BOOST_LOCAL_FUNCTION_AUX_NAME_LOCAL_FUNCTOR_ \
        BOOST_PP_IIF( /* !RECURSIVE && (C++11 || INLINE) => FASTER */ \
                BOOST_PP_BITAND( \
                      BOOST_PP_COMPL( \
                        BOOST_LOCAL_FUNCTION_AUX_PP_NAME_TRAITS_IS_RECURSIVE( \
                                name_traits)) \
                    , BOOST_PP_BITOR( \
                        /* on C++11 always use inlining because compilers */ \
                        /* might optimize it to be faster and it can also */ \
                        /* be passed as template parameter */ \
                          BOOST_LOCAL_FUNCTION_CONFIG_LOCALS_AS_TPARAMS \
                        , BOOST_LOCAL_FUNCTION_AUX_PP_NAME_TRAITS_IS_INLINE( \
                                name_traits) \
                    ) \
                ), \
            /* inlined local function declared as local functor: it maybe */ \
            /* always be inlined (faster) but it can be passed as template */ \
            /* parameter only by C++11 -- never recursive */ \
            ( \
                typename01 \
            , \
                name_traits \
            , \
                BOOST_LOCAL_FUNCTION_AUX_PP_NAME_TRAITS_FUNCTION_NAME( \
                        name_traits) \
            , \
                BOOST_LOCAL_FUNCTION_AUX_NAME_FUNCTOR_( \
                        BOOST_LOCAL_FUNCTION_AUX_PP_NAME_TRAITS_FUNCTION_NAME( \
                                name_traits)) \
            ) \
        , /* RECURSIVE || (!C++11 && !INLINE) => SLOWER */ \
            /* local function declared as non-local functor: it can always */ \
            /* be passed as template parameter but slower even on C++11 if */ \
            /* declared recursive -- it can be inlined (faster) only by */ \
            /* C++11 and if not recursive */ \
            ( \
                typename01 \
            , \
                name_traits \
            , \
                BOOST_LOCAL_FUNCTION_AUX_NAME_FUNCTOR_( \
                        BOOST_LOCAL_FUNCTION_AUX_PP_NAME_TRAITS_FUNCTION_NAME( \
                                name_traits)) \
            , \
                BOOST_LOCAL_FUNCTION_AUX_PP_NAME_TRAITS_FUNCTION_NAME( \
                        name_traits) \
            ) \
        ) \
    )

#endif // #include guard

