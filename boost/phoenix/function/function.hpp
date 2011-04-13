/*==============================================================================
    Copyright (c) 2001-2010 Joel de Guzman
    Copyright (c) 2010 Eric Niebler

    Distributed under the Boost Software License, Version 1.0. (See accompanying
    file LICENSE_1_0.txt or copy at http://www.boost.org/LICENSE_1_0.txt)
==============================================================================*/
#ifndef BOOST_PHOENIX_FUNCTION_FUNCTION_HPP
#define BOOST_PHOENIX_FUNCTION_FUNCTION_HPP

#include <boost/phoenix/function/function_handling.hpp>
#include <boost/phoenix/function/adapt_function.hpp>
#include <boost/preprocessor/facilities/expand.hpp>
#include <boost/preprocessor/logical/or.hpp>
#include <boost/utility/result_of.hpp>

namespace boost { namespace phoenix
{
    /////////////////////////////////////////////////////////////////////////////
    // Functions
    /////////////////////////////////////////////////////////////////////////////

    // functor which returns our lazy function call extension
    template<typename F>
    struct function
    {
        function() {}

        function(F f)
          : f(f)
        {}

        template <typename Sig>
        struct result;

        typename expression::function<F>::type const
        operator()() const
        {
            return expression::function<F>::make(f);
        }

        // Bring in the rest
        #include <boost/phoenix/function/detail/function_operator.hpp>

        F f;
    };

}

    template<typename F>
    struct result_of<phoenix::function<F>()>
      : phoenix::expression::function<F>
    {};

}

#endif

