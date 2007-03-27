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

#include <boost/mpl/int.hpp>
#include <boost/lexical_cast.hpp>
#include <boost/xpressive/detail/detail_fwd.hpp>
#include <boost/xpressive/detail/core/state.hpp>
#include <boost/xpressive/detail/core/matcher/action_matcher.hpp>
#include <boost/xpressive/detail/core/matcher/predicate_matcher.hpp>
#include <boost/xpressive/detail/utility/ignore_unused.hpp>

namespace boost { namespace xpressive
{

    namespace detail
    {
        template<typename T, typename U>
        struct action_arg
        {
            typedef T type;
            typedef typename add_reference<T>::type reference;

            reference cast(void *pv) const
            {
                return *static_cast<typename remove_reference<T>::type *>(pv);
            }
        };

        template<typename T>
        T &unconst(T const &t)
        {
            return const_cast<T &>(t);
        }
    }

    namespace op
    {
        struct push
        {
            typedef void result_type;

            template<typename Sequence, typename Value>
            void operator()(Sequence &seq, Value const &val) const
            {
                detail::unconst(seq).push(val);
            }
        };

        struct push_back
        {
            typedef void result_type;

            template<typename Sequence, typename Value>
            void operator()(Sequence &seq, Value const &val) const
            {
                detail::unconst(seq).push_back(val);
            }
        };

        struct push_front
        {
            typedef void result_type;

            template<typename Sequence, typename Value>
            void operator()(Sequence &seq, Value const &val) const
            {
                detail::unconst(seq).push_front(val);
            }
        };

        struct pop
        {
            typedef void result_type;

            template<typename Sequence>
            void operator()(Sequence &seq) const
            {
                detail::unconst(seq).pop();
            }
        };

        struct pop_back
        {
            typedef void result_type;

            template<typename Sequence>
            void operator()(Sequence &seq) const
            {
                detail::unconst(seq).pop_back();
            }
        };

        struct pop_front
        {
            typedef void result_type;

            template<typename Sequence>
            void operator()(Sequence &seq) const
            {
                detail::unconst(seq).pop_front();
            }
        };

        struct front
        {
            template<typename Sig>
            struct result;

            template<typename This, typename Sequence>
            struct result<This(Sequence &)>
            {
                typedef typename Sequence::value_type type;
            };

            template<typename Sequence>
            typename Sequence::value_type operator()(Sequence &seq) const
            {
                return seq.front();
            }
        };

        struct back
        {
            template<typename Sig>
            struct result;

            template<typename This, typename Sequence>
            struct result<This(Sequence &)>
            {
                typedef typename Sequence::value_type type;
            };

            template<typename Sequence>
            typename Sequence::value_type operator()(Sequence &seq) const
            {
                return seq.back();
            }
        };

        struct top
        {
            template<typename Sig>
            struct result;

            template<typename This, typename Sequence>
            struct result<This(Sequence &)>
            {
                typedef typename Sequence::value_type type;
            };

            template<typename Sequence>
            typename Sequence::value_type operator()(Sequence &seq) const
            {
                return seq.top();
            }
        };

        struct first
        {
            template<typename Sig>
            struct result;

            template<typename This, typename Pair>
            struct result<This(Pair &)>
            {
                typedef typename Pair::first_type type;
            };

            template<typename Pair>
            typename Pair::first_type operator()(Pair &p) const
            {
                return p.first;
            }
        };

        struct second
        {
            template<typename Sig>
            struct result;

            template<typename This, typename Pair>
            struct result<This(Pair &)>
            {
                typedef typename Pair::second_type type;
            };

            template<typename Pair>
            typename Pair::second_type operator()(Pair &p) const
            {
                return p.second;
            }
        };

        struct length
        {
            template<typename Sig>
            struct result;

            template<typename This, typename Sub>
            struct result<This(Sub &)>
            {
                typedef typename Sub::difference_type type;
            };

            template<typename Sub>
            typename Sub::difference_type operator()(Sub &sub) const
            {
                return sub.length();
            }
        };

        struct str
        {
            template<typename Sig>
            struct result;

            template<typename This, typename Sub>
            struct result<This(Sub &)>
            {
                typedef typename Sub::string_type type;
            };

            template<typename Sub>
            typename Sub::string_type operator()(Sub &sub) const
            {
                return sub.str();
            }
        };

        template<typename T>
        struct as
        {
            typedef T result_type;

            template<typename Value>
            T operator()(Value const &val) const
            {
                return lexical_cast<T>(val);
            }
        };

        template<typename T>
        struct construct
        {
            typedef T result_type;

            T operator()() const
            {
                return T();
            }

            template<typename A0>
            T operator()(A0 &a0) const
            {
                return T(a0);
            }

            template<typename A0, typename A1>
            T operator()(A0 &a0, A1 &a1) const
            {
                return T(a0, a1);
            }

            template<typename A0, typename A1, typename A2>
            T operator()(A0 &a0, A1 &a1, A2 &a2) const
            {
                return T(a0, a1, a2);
            }
        };
    }

    proto::terminal<op::push>::type const push = {{}};
    proto::terminal<op::push_back>::type const push_back = {{}};
    proto::terminal<op::push_front>::type const push_front = {{}};
    proto::terminal<op::pop>::type const pop = {{}};
    proto::terminal<op::pop_back>::type const pop_back = {{}};
    proto::terminal<op::pop_front>::type const pop_front = {{}};
    proto::terminal<op::top>::type const top = {{}};
    proto::terminal<op::back>::type const back = {{}};
    proto::terminal<op::front>::type const front = {{}};
    proto::terminal<op::first>::type const first = {{}};
    proto::terminal<op::second>::type const second = {{}};
    proto::terminal<op::length>::type const length = {{}};
    proto::terminal<op::str>::type const str = {{}};

    template<typename T, typename D>
    typename proto::function<
        typename proto::terminal<op::as<T> >::type
      , typename proto::result_of::as_expr<D const>::type
    >::type as(D const &d)
    {
        typename proto::function<
            typename proto::terminal<op::as<T> >::type
          , typename proto::result_of::as_expr<D const>::type
        >::type that = {{{}}, proto::as_expr(d)};
        return that;
    }

    template<typename T>
    typename proto::terminal<T>::type val(T const &t)
    {
        return proto::terminal<T>::type::make(t);
    }

    template<typename T>
    typename proto::terminal<T &>::type ref(T &t)
    {
        return proto::terminal<T &>::type::make(t);
    }

    template<typename T>
    typename proto::terminal<T const &>::type cref(T const &t)
    {
        return proto::terminal<T const &>::type::make(t);
    }

    template<typename Predicate>
    typename proto::terminal<detail::predicate_placeholder<Predicate> >::type
    check(Predicate const &pred)
    {
        detail::predicate_placeholder<Predicate> p = {pred};
        return proto::as_expr(p);
    }

    template<typename T, int I = 0>
    struct arg
      : proto::extends<typename proto::terminal<detail::action_arg<T, mpl::int_<I> > >::type, arg<T, I> >
    {
        typedef proto::extends<typename proto::terminal<detail::action_arg<T, mpl::int_<I> > >::type, arg<T, I> > base_type;
        using base_type::operator =;
    };

    /// construct
    ///
    template<typename T>
    typename proto::function<
        typename proto::terminal<op::construct<T> >::type
    >::type construct()
    {
        typename proto::function<
            typename proto::terminal<op::construct<T> >::type
        >::type that = {{{}}};
        return that;
    }

    /// \overload
    ///
    template<typename T, typename A0>
    typename proto::function<
        typename proto::terminal<op::construct<T> >::type
      , typename proto::result_of::as_expr<A0>::type
    >::type construct(A0 &a0)
    {
        typename proto::function<
            typename proto::terminal<op::construct<T> >::type
          , typename proto::result_of::as_expr<A0>::type
        >::type that = {{{}}, proto::as_expr(a0)};
        return that;
    }

    /// \overload
    ///
    template<typename T, typename A0, typename A1>
    typename proto::function<
        typename proto::terminal<op::construct<T> >::type
      , typename proto::result_of::as_expr<A0>::type
      , typename proto::result_of::as_expr<A1>::type
    >::type construct(A0 &a0, A1 &a1)
    {
        typename proto::function<
            typename proto::terminal<op::construct<T> >::type
          , typename proto::result_of::as_expr<A0>::type
          , typename proto::result_of::as_expr<A1>::type
        >::type that = {{{}}, proto::as_expr(a0), proto::as_expr(a1)};
        return that;
    }

    /// \overload
    ///
    template<typename T, typename A0, typename A1, typename A2>
    typename proto::function<
        typename proto::terminal<op::construct<T> >::type
      , typename proto::result_of::as_expr<A0>::type
      , typename proto::result_of::as_expr<A1>::type
      , typename proto::result_of::as_expr<A2>::type
    >::type construct(A0 &a0, A1 &a1, A2 &a2)
    {
        typename proto::function<
            typename proto::terminal<op::construct<T> >::type
          , typename proto::result_of::as_expr<A0>::type
          , typename proto::result_of::as_expr<A1>::type
          , typename proto::result_of::as_expr<A2>::type
        >::type that = {{{}}, proto::as_expr(a0), proto::as_expr(a1), proto::as_expr(a2)};
        return that;
    }

    namespace detail
    {
        inline void ignore_unused_regex_actions()
        {
            ignore_unused(repeat_max);
            ignore_unused(push);
            ignore_unused(push_back);
            ignore_unused(push_front);
            ignore_unused(pop);
            ignore_unused(pop_back);
            ignore_unused(pop_front);
            ignore_unused(top);
            ignore_unused(back);
            ignore_unused(front);
            ignore_unused(first);
            ignore_unused(second);
            ignore_unused(length);
            ignore_unused(str);
        }
    }

}}

#endif // BOOST_XPRESSIVE_ACTIONS_HPP_EAN_03_22_2007
