/*=============================================================================
    Copyright (c) 2009-2010 Christopher Schmidt

    Distributed under the Boost Software License, Version 1.0. (See accompanying
    file LICENSE_1_0.txt or copy at http://www.boost.org/LICENSE_1_0.txt)
==============================================================================*/

#ifndef BOOST_FUSION_ADAPTED_DETAIL_STRUCT_DEREF_IMPL_HPP
#define BOOST_FUSION_ADAPTED_DETAIL_STRUCT_DEREF_IMPL_HPP

#include <boost/fusion/support/detail/access.hpp>
#include <boost/mpl/eval_if.hpp>
#include <boost/type_traits/remove_const.hpp>
#include <boost/type_traits/is_const.hpp>

namespace boost { namespace fusion { namespace extension
{
    template <typename>
    struct deref_impl;

    template <>
    struct deref_impl<struct_iterator_tag>
    {
        template <typename It>
        struct apply
        {
            typedef
                extension::struct_member<
                    typename remove_const<typename It::seq_type>::type
                  , It::index::value
                >
            member;

            typedef typename
                mpl::eval_if<
                    is_const<typename It::seq_type>
                  , detail::cref_result<member>
                  , detail::ref_result<member>
                >::type
            type;

            static type
            call(It const& it)
            {
                return member::call(*it.seq);
            }
        };
    };

    template <>
    struct deref_impl<assoc_struct_iterator_tag>
       : deref_impl<struct_iterator_tag>
    {};
}}}

#endif
