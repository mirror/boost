/*=============================================================================
    Copyright (c) 2010 Christopher Schmidt

    Distributed under the Boost Software License, Version 1.0. (See accompanying
    file LICENSE_1_0.txt or copy at http://www.boost.org/LICENSE_1_0.txt)
==============================================================================*/

#ifndef BOOST_FUSION_ADAPTED_DETAIL_CLASS_DEREF_IMPL_HPP
#define BOOST_FUSION_ADAPTED_DETAIL_CLASS_DEREF_IMPL_HPP

#include <boost/mpl/if.hpp>
#include <boost/type_traits/is_const.hpp>
#include <boost/type_traits/remove_const.hpp>

namespace boost { namespace fusion { namespace extension
{
    template <typename>
    struct deref_impl;

    template <>
    struct deref_impl<class_iterator_tag>
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
                mpl::if_<
                    is_const<typename It::seq_type>
                  , typename member::get_type
                  , typename member::proxy
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
    struct deref_impl<assoc_class_iterator_tag>
       : deref_impl<class_iterator_tag>
    {};
}}}

#endif
