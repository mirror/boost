/*=============================================================================
    Copyright (c) 2001-2007 Joel de Guzman

    Distributed under the Boost Software License, Version 1.0. (See accompanying 
    file LICENSE_1_0.txt or copy at http://www.boost.org/LICENSE_1_0.txt)
==============================================================================*/

#if !BOOST_PHOENIX_IS_ITERATING

#ifndef PHOENIX_BIND_BIND_FUNCTION_OBJECT_HPP
#define PHOENIX_BIND_BIND_FUNCTION_OBJECT_HPP

#include <boost/phoenix/core/expression.hpp>
#include <boost/phoenix/core/detail/function_eval.hpp>

namespace boost { namespace phoenix {
    template <typename F>
    inline
    typename detail::expression::function_eval<F>::type const
    bind(F f)
    {
        return detail::expression::function_eval<F>::make(f);
    }
        
#define BOOST_PHOENIX_ITERATION_PARAMS                                          \
    (3, (1, BOOST_PP_DEC(BOOST_PHOENIX_ACTOR_LIMIT),                            \
            <boost/phoenix/bind/bind_function_object.hpp>))
#include BOOST_PHOENIX_ITERATE()

}}

#endif

#else

    template <
        typename F
      , BOOST_PHOENIX_typename_A
    >
    inline
    typename detail::expression::function_eval<
        F
      , BOOST_PHOENIX_A
    >::type const
    bind(F f, BOOST_PHOENIX_A_const_ref_a)
    {
        return
            detail::expression::function_eval<F, BOOST_PHOENIX_A>::make(
                f
              , BOOST_PHOENIX_a
            );
    }

#endif
