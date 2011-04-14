/*=============================================================================
    Copyright (c) 2001-2007 Joel de Guzman

    Distributed under the Boost Software License, Version 1.0. (See accompanying 
    file LICENSE_1_0.txt or copy at http://www.boost.org/LICENSE_1_0.txt)
==============================================================================*/

#if !BOOST_PHOENIX_IS_ITERATING

#ifndef PHOENIX_BIND_BIND_FUNCTION_HPP
#define PHOENIX_BIND_BIND_FUNCTION_HPP

#include <boost/phoenix/core/expression.hpp>
#include <boost/phoenix/core/detail/function_eval.hpp>
#include <boost/phoenix/bind/detail/function_ptr.hpp>

namespace boost { namespace phoenix {

    template <
        typename RT
    >
    inline
    typename detail::expression::function_eval<
        detail::function_ptr<0, RT, RT(*)()>
    >::type const
    bind(RT(*f)())
    {
        typedef detail::function_ptr<0, RT, RT(*)()> fp_type;
        return detail::expression::function_eval<fp_type>::make(fp_type(f));
    }

    template <
        typename RT
      , typename T0
      , typename A0
    >
    inline
    typename detail::expression::function_eval<
        detail::function_ptr<1, RT, RT(*)(T0 &)>
      , A0
    >::type const
    bind(RT(*f)(T0 &), A0 const & a0)
    {
        typedef detail::function_ptr<1, RT, RT(*)(T0 &)> fp_type;
        return detail::expression::function_eval<fp_type, A0>::make(fp_type(f), a0);
    }
        
#define BOOST_PHOENIX_ITERATION_PARAMS                                          \
    (3, (2, BOOST_PP_DEC(BOOST_PHOENIX_ACTOR_LIMIT),                            \
            <boost/phoenix/bind/bind_function.hpp>))
#include BOOST_PHOENIX_ITERATE()

}}

#endif

#else

    template <
        typename RT
      , BOOST_PP_ENUM_PARAMS(BOOST_PHOENIX_ITERATION, typename T)
      , BOOST_PHOENIX_typename_A
    >
    inline
    typename detail::expression::function_eval<
        detail::function_ptr<
            BOOST_PHOENIX_ITERATION
          , RT
          , RT(*)(BOOST_PP_ENUM_PARAMS(BOOST_PHOENIX_ITERATION, T))
        >
      , BOOST_PHOENIX_A
    >::type const
    bind(
        RT(*f)(BOOST_PP_ENUM_PARAMS(BOOST_PHOENIX_ITERATION, T))
      , BOOST_PHOENIX_A_const_ref_a
    )
    {
        typedef detail::function_ptr<
            BOOST_PHOENIX_ITERATION
          , RT
          , RT(*)(BOOST_PP_ENUM_PARAMS(BOOST_PHOENIX_ITERATION, T))
        > fp_type;
        return
            detail::expression::function_eval<
                fp_type
              , BOOST_PHOENIX_A
            >::make(
                fp_type(f)
              , BOOST_PHOENIX_a
            );
    }

#endif
