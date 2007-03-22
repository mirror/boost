///////////////////////////////////////////////////////////////////////////////
/// \file regex_actions.hpp
/// Defines the syntax elements of xpressive's action expressions.
//
//  Copyright 2004 Eric Niebler. Distributed under the Boost
//  Software License, Version 1.0. (See accompanying file
//  LICENSE_1_0.txt or copy at http://www.boost.org/LICENSE_1_0.txt)

#ifndef BOOST_XPRESSIVE_ACTIONS_HPP_EAN_03_22_2007
#define BOOST_XPRESSIVE_ACTIONS_HPP_EAN_03_22_2007

// MS compatible compilers support #pragma once
#if defined(_MSC_VER) && (_MSC_VER >= 1020)
# pragma once
#endif

#include <boost/lexical_cast.hpp>
#include <boost/xpressive/detail/detail_fwd.hpp>
#include <boost/xpressive/detail/core/state.hpp>
#include <boost/xpressive/detail/core/matcher/action_matcher.hpp>

namespace boost { namespace xpressive
{

    namespace detail
    {
        template<typename T>
        T &unconst(T const &t)
        {
            return const_cast<T &>(t);
        }

        struct push_back_impl
        {
            typedef void result_type;

            template<typename Sequence, typename Value>
            void operator()(Sequence &seq, Value const &val) const
            {
                detail::unconst(seq).push_back(val);
            }
        };

        struct push_front_impl
        {
            typedef void result_type;

            template<typename Sequence, typename Value>
            void operator()(Sequence &seq, Value const &val) const
            {
                detail::unconst(seq).push_front(val);
            }
        };

        template<typename T>
        struct as_impl
        {
            typedef T result_type;

            template<typename Value>
            T operator()(Value const &val) const
            {
                return lexical_cast<T>(val);
            }
        };
    }

    proto::terminal<detail::push_back_impl>::type const push_back = {{}};
    proto::terminal<detail::push_front_impl>::type const push_front = {{}};

    template<typename T, typename D>
    typename proto::function<
        typename proto::terminal<detail::as_impl<T> >::type
      , typename proto::result_of::as_arg<D const>::type
    >::type as(D const &d)
    {
        typename proto::function<
            typename proto::terminal<detail::as_impl<T> >::type
          , typename proto::result_of::as_arg<D const>::type
        >::type that = {{{}}, proto::as_arg(d)};
        return that;
    }

    template<typename T>
    typename proto::result_of::as_arg<T>::type var(T &t)
    {
        return proto::as_arg(t);
    }

}}

#endif // BOOST_XPRESSIVE_ACTIONS_HPP_EAN_03_22_2007
