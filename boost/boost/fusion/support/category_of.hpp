/*=============================================================================
    Copyright (c) 2001-2006 Joel de Guzman

    Use, modification and distribution is subject to the Boost Software
    License, Version 1.0. (See accompanying file LICENSE_1_0.txt or copy at
    http://www.boost.org/LICENSE_1_0.txt)
==============================================================================*/
#if !defined(FUSION_CATEGORY_OF_07202005_0308)
#define FUSION_CATEGORY_OF_07202005_0308

#include <boost/fusion/support/detail/category_of.hpp>
#include <boost/fusion/support/tag_of.hpp>
#include <boost/fusion/support/tags.hpp>

namespace boost { namespace fusion
{
    struct array_tag; // boost::array tag
    struct mpl_sequence_tag; // mpl sequence tag
    struct std_pair_tag; // std::pair tag

    namespace extension
    {
        template<typename Tag>
        struct category_of_impl
        {
            template<typename T>
            struct apply
                : detail::fusion_category_of<T>
            {};
        };

        template <>
        struct category_of_impl<array_tag>;

        template <>
        struct category_of_impl<mpl_sequence_tag>;

        template <>
        struct category_of_impl<std_pair_tag>;
    }

    namespace traits
    {
        template <typename T>
        struct category_of
            : extension::category_of_impl<typename detail::tag_of<T>::type>::
                template apply<T>
        {};
}}}

#endif
