/*=============================================================================
    Copyright (c) 2001-2006 Joel de Guzman

    Use, modification and distribution is subject to the Boost Software
    License, Version 1.0. (See accompanying file LICENSE_1_0.txt or copy at
    http://www.boost.org/LICENSE_1_0.txt)
==============================================================================*/
#if !defined(FUSION_DEREF_IMPL_09302005_1846)
#define FUSION_DEREF_IMPL_09302005_1846

#include <boost/fusion/support/detail/access.hpp>
#include <boost/type_traits/is_const.hpp>
#include <boost/static_assert.hpp>
#include <boost/mpl/if.hpp>

namespace boost { namespace fusion
{
    struct std_pair_iterator_tag;

    namespace extension
    {
        template <typename Tag>
        struct deref_impl;

        template <>
        struct deref_impl<std_pair_iterator_tag>
        {
            template <typename Iterator>
            struct apply 
            {
                typedef typename Iterator::pair_type pair_type;
                typedef typename Iterator::index index;
                static int const index_val = index::value;

                BOOST_STATIC_ASSERT(index_val >= 0 && index_val <= 2);
                typedef typename
                    mpl::if_c<
                        (index::value == 0)
                      , typename pair_type::first_type
                      , typename pair_type::second_type
                    >
                element;
                
                typedef typename
                    mpl::eval_if<
                        is_const<pair_type>
                      , fusion::detail::cref_result<element>
                      , fusion::detail::ref_result<element>
                    >::type
                type;

                template <typename RT>
                static RT get(pair_type& p, mpl::int_<0>)
                {
                    return  p.first;
                }

                template <typename RT>
                static RT get(pair_type& p, mpl::int_<1>)
                {
                    return  p.second;
                }

                static type
                call(Iterator const& iter)
                {
                    return get<type>(iter.pair, index());
                }
            };
        };
    }
}}

#endif
