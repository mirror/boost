/*=============================================================================
    Copyright (c) 2005-2013 Joel de Guzman
    Copyright (c) 2006 Dan Marsden

    Distributed under the Boost Software License, Version 1.0. (See accompanying
    file LICENSE_1_0.txt or copy at http://www.boost.org/LICENSE_1_0.txt)
==============================================================================*/
#if !defined(FUSION_CONVERT_20061213_2207)
#define FUSION_CONVERT_20061213_2207

#include <boost/fusion/container/deque/detail/convert_impl.hpp>
#include <boost/fusion/container/deque/deque.hpp>

#if defined(BOOST_FUSION_HAS_VARIADIC_DEQUE)

#include <boost/fusion/iterator/equal_to.hpp>
#include <boost/fusion/iterator/next.hpp>
#include <boost/fusion/iterator/value_of.hpp>
#include <boost/fusion/iterator/deref.hpp>
#include <boost/fusion/sequence/intrinsic/begin.hpp>
#include <boost/fusion/sequence/intrinsic/end.hpp>
#include <boost/fusion/container/deque/front_extended_deque.hpp>

///////////////////////////////////////////////////////////////////////////////
// C++11 variadic implementation
///////////////////////////////////////////////////////////////////////////////
namespace boost { namespace fusion
{
    namespace detail
    {
        template <typename First, typename Last
          , bool is_empty = result_of::equal_to<First, Last>::value>
        struct build_deque;

        template <typename First, typename Last>
        struct build_deque<First, Last, true>
        {
            typedef deque<> type;
            static type
            call(First const&, Last const&)
            {
                return type();
            }
        };

        template <typename T, typename Rest>
        struct push_front_deque;

        template <typename T>
        struct push_front_deque<T, deque<>>
        {
            typedef deque<T> type;

            static type
            call(T const& first, deque<>)
            {
                return type(first);
            }
        };

        template <typename T, typename ...Rest>
        struct push_front_deque<T, deque<Rest...>>
        {
            typedef deque<T, Rest...> type;

            static type
            call(T const& first, deque<Rest...> const& rest)
            {
                typedef
                    front_extended_deque<deque<Rest...>, T>
                front_extended;
                return type(front_extended(rest, first));
            }
        };

        template <typename First, typename Last>
        struct build_deque<First, Last, false>
        {
            typedef
                build_deque<typename result_of::next<First>::type, Last>
            next_build_deque;

            typedef push_front_deque<
                typename result_of::value_of<First>::type
              , typename next_build_deque::type>
            push_front;

            typedef typename push_front::type type;

            static type
            call(First const& f, Last const& l)
            {
                typename result_of::value_of<First>::type v = *f;
                return push_front::call(
                    v, next_build_deque::call(fusion::next(f), l));
            }
        };
    }

    namespace result_of
    {
        template <typename Sequence>
        struct as_deque :
            detail::build_deque<
                typename result_of::begin<Sequence>::type
              , typename result_of::end<Sequence>::type
            >
        {
        };
    }

    template <typename Sequence>
    inline typename result_of::as_deque<Sequence>::type
    as_deque(Sequence& seq)
    {
        typedef typename result_of::as_deque<Sequence>::gen gen;
        return gen::call(fusion::begin(seq), fusion::end(seq));
    }

    template <typename Sequence>
    inline typename result_of::as_deque<Sequence const>::type
    as_deque(Sequence const& seq)
    {
        typedef typename result_of::as_deque<Sequence const>::gen gen;
        return gen::call(fusion::begin(seq), fusion::end(seq));
    }
}}

#else

///////////////////////////////////////////////////////////////////////////////
// C++03 (non-variadic) implementation
///////////////////////////////////////////////////////////////////////////////

#include <boost/fusion/sequence/intrinsic/begin.hpp>
#include <boost/fusion/sequence/intrinsic/size.hpp>
#include <boost/fusion/container/deque/detail/pp_as_deque.hpp>
#include <boost/fusion/container/deque/front_extended_deque.hpp>

namespace boost { namespace fusion
{
    namespace result_of
    {
        template <typename Sequence>
        struct as_deque
        {
            typedef typename
                detail::as_deque<result_of::size<Sequence>::value>
            gen;
            typedef typename gen::
                template apply<typename result_of::begin<Sequence>::type>::type
            type;
        };
    }

    template <typename Sequence>
    inline typename result_of::as_deque<Sequence>::type
    as_deque(Sequence& seq)
    {
        typedef typename result_of::as_deque<Sequence>::gen gen;
        return gen::call(fusion::begin(seq));
    }

    template <typename Sequence>
    inline typename result_of::as_deque<Sequence const>::type
    as_deque(Sequence const& seq)
    {
        typedef typename result_of::as_deque<Sequence const>::gen gen;
        return gen::call(fusion::begin(seq));
    }
}}

#endif
#endif
