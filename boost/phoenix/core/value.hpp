/*==============================================================================
    Copyright (c) 2001-2010 Joel de Guzman
    Copyright (c) 2010 Thomas Heller

    Distributed under the Boost Software License, Version 1.0. (See accompanying
    file LICENSE_1_0.txt or copy at http://www.boost.org/LICENSE_1_0.txt)
==============================================================================*/
#ifndef BOOST_PHOENIX_CORE_VALUE_HPP
#define BOOST_PHOENIX_CORE_VALUE_HPP

#include <boost/phoenix/core/limits.hpp>
#include <boost/phoenix/core/actor.hpp>
#include <boost/phoenix/core/terminal.hpp>
#include <boost/utility/result_of.hpp>

namespace boost { namespace phoenix
{
    ////////////////////////////////////////////////////////////////////////////
    //
    // values
    //
    //      function for evaluating values, e.g. val(123)
    //
    ////////////////////////////////////////////////////////////////////////////
 
    namespace expression
    {
        template <typename T>
        struct value
            : expression::terminal<T>
        {};
    }

    template <typename T>
    typename expression::value<T>::type const
    inline val(T t)
    {
        return expression::value<T>::make(t);
    }

    // Call out actor for special handling
    template<typename Expr>
    struct is_custom_terminal<actor<Expr> >
      : mpl::true_
    {};
    
    // Special handling for actor
    template<typename Expr>
    struct custom_terminal<actor<Expr> >
    {
        template <typename Sig>
        struct result;

        template <typename This, typename Actor, typename Context>
        struct result<This(Actor, Context)>
            : boost::remove_reference<
                typename evaluator::impl<Actor, Context, int>::result_type
            >
        {};     

        template <typename Context>
        typename result<custom_terminal(actor<Expr> const &, Context &)>::type
        operator()(actor<Expr> const & expr, Context & ctx) const
        {
            return eval(expr, ctx);
        }
    };
}}

#endif
