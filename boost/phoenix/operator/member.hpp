
#if !defined(BOOST_PHOENIX_DONT_USE_PREPROCESSED_FILES)
#ifndef BOOST_PHOENIX_OPERATOR_MEMBER_HPP
#define BOOST_PHOENIX_OPERATOR_MEMBER_HPP

#include <boost/phoenix/core/limits.hpp>
#include <boost/get_pointer.hpp>
#include <boost/phoenix/core/domain.hpp>
#include <boost/phoenix/core/expression.hpp>
#include <boost/phoenix/core/meta_grammar.hpp>
#include <boost/phoenix/core/call.hpp>
#include <boost/phoenix/operator/detail/mem_fun_ptr_gen.hpp>
#include <boost/phoenix/support/iterate.hpp>
#include <boost/type_traits/is_member_function_pointer.hpp>

#include <boost/phoenix/operator/preprocessed/member.hpp>

#endif
#else

#if !BOOST_PHOENIX_IS_ITERATING

#ifndef BOOST_PHOENIX_OPERATOR_MEMBER_HPP
#define BOOST_PHOENIX_OPERATOR_MEMBER_HPP

#include <boost/phoenix/core/limits.hpp>
#include <boost/get_pointer.hpp>
#include <boost/phoenix/core/domain.hpp>
#include <boost/phoenix/core/expression.hpp>
#include <boost/phoenix/core/meta_grammar.hpp>
#include <boost/phoenix/core/call.hpp>
#include <boost/phoenix/operator/detail/mem_fun_ptr_gen.hpp>
#include <boost/phoenix/support/iterate.hpp>
#include <boost/type_traits/is_member_function_pointer.hpp>

#if defined(__WAVE__) && defined(BOOST_PHOENIX_CREATE_PREPROCESSED_FILES)
#pragma wave option(preserve: 2, line: 0, output: "preprocessed/member_" BOOST_PHOENIX_LIMIT_STR ".hpp")
#endif

/*==============================================================================
    Copyright (c) 2005-2010 Joel de Guzman
    Copyright (c) 2010 Thomas Heller

    Distributed under the Boost Software License, Version 1.0. (See accompanying
    file LICENSE_1_0.txt or copy at http://www.boost.org/LICENSE_1_0.txt)
==============================================================================*/

#if defined(__WAVE__) && defined(BOOST_PHOENIX_CREATE_PREPROCESSED_FILES)
#pragma wave option(preserve: 1)
#endif

#include <boost/phoenix/operator/detail/define_operator.hpp>

BOOST_PHOENIX_DEFINE_EXPRESSION_VARARG(
    (boost)(phoenix)(mem_fun_ptr)
  , (meta_grammar)
  , BOOST_PHOENIX_LIMIT
)

namespace boost { namespace phoenix
{
    BOOST_PHOENIX_BINARY_OPERATORS(
        (mem_ptr)
    )

    template <typename Object, typename MemPtr>
    inline
    typename enable_if<
        is_member_function_pointer<MemPtr>
      , detail::mem_fun_ptr_gen<actor<Object>, MemPtr> const
      >::type
    operator->*(actor<Object> const& obj, MemPtr ptr)
    {
        return detail::mem_fun_ptr_gen<actor<Object>, MemPtr>(obj, ptr);
    }

    namespace result_of
    {
        template <
            typename Context
          , BOOST_PHOENIX_typename_A_void(BOOST_PHOENIX_LIMIT)
          , typename Dummy = void
        >
        struct mem_fun_ptr_eval;

        #include <boost/phoenix/operator/detail/mem_fun_ptr_eval_result_of.hpp>
    }

    struct mem_fun_ptr_eval
    {
        template<typename Sig>
        struct result;

    #define BOOST_PHOENIX_MEMBER_EVAL(Z, N, D)                                  \
        BOOST_PP_COMMA_IF(BOOST_PP_NOT(BOOST_PP_EQUAL(N, 2)))                   \
        eval(BOOST_PP_CAT(a, N), ctx)                                           \
    /**/

    #define BOOST_PHOENIX_ITERATION_PARAMS                                      \
        (4, (2, BOOST_PHOENIX_LIMIT,                                            \
        <boost/phoenix/operator/member.hpp>,                                    \
        BOOST_PHOENIX_ITERATE_OPERATOR))                                        \
    /**/
        #include BOOST_PHOENIX_ITERATE()
    #undef BOOST_PHOENIX_MEMBER_EVAL
    };

    template <typename Dummy>
    struct default_actions::when<rule::mem_fun_ptr, Dummy>
        : call<mem_fun_ptr_eval>
    {};
}}

#include <boost/phoenix/operator/detail/undef_operator.hpp>

#if defined(__WAVE__) && defined(BOOST_PHOENIX_CREATE_PREPROCESSED_FILES)
#pragma wave option(output: null)
#endif

#endif

#else // BOOST_PHOENIX_IS_ITERATING

        template <typename This, typename Context, BOOST_PHOENIX_typename_A>
        struct result<This(Context, BOOST_PHOENIX_A)>
            : result<This(Context, BOOST_PHOENIX_A_const_ref)>
        {};

        template <typename This, typename Context, BOOST_PHOENIX_typename_A>
        struct result<This(Context, BOOST_PHOENIX_A_ref)>
            : result_of::mem_fun_ptr_eval<Context, BOOST_PHOENIX_A>
        {};

        template <typename Context, BOOST_PHOENIX_typename_A>
        typename result_of::mem_fun_ptr_eval<Context, BOOST_PHOENIX_A>::type
        operator()(
            Context const & ctx, BOOST_PHOENIX_A_const_ref_a
        ) const
        {
            return
                (
                    get_pointer(eval(a0, ctx))
                    ->*eval(a1, ctx)
                )(
                    BOOST_PP_REPEAT_FROM_TO(
                        2
                      , BOOST_PHOENIX_ITERATION
                      , BOOST_PHOENIX_MEMBER_EVAL
                      , BOOST_PHOENIX_ITERATION
                    )
                );
        }
        

#endif

#endif // BOOST_PHOENIX_DONT_USE_PREPROCESSED_FILES
