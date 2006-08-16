/*=============================================================================
    Copyright (c) 2001-2006 Joel de Guzman

    Use, modification and distribution is subject to the Boost Software
    License, Version 1.0. (See accompanying file LICENSE_1_0.txt or copy at
    http://www.boost.org/LICENSE_1_0.txt)
==============================================================================*/
#if !defined(FUSION_DEREF_05042005_1019)
#define FUSION_DEREF_05042005_1019

#include <boost/fusion/support/iterator_base.hpp>
#include <boost/fusion/support/tag_of.hpp>

namespace boost { namespace fusion
{
    namespace extension
    {
        template <typename Tag>
        struct deref_impl
        {
            template <typename Iterator>
            struct apply {};
        };
    }

    namespace result_of
    {
        template <typename Iterator>
        struct deref
            : extension::deref_impl<typename detail::tag_of<Iterator>::type>::
                template apply<Iterator>
        {};
    }

    template <typename Iterator>
    typename result_of::deref<Iterator>::type
    deref(Iterator const& i)
    {
        typedef result_of::deref<Iterator> deref_meta;
        typename deref_meta::type result(deref_meta::call(i));
        return result;
    }

    template <typename Iterator>
    typename result_of::deref<Iterator>::type
    operator*(iterator_base<Iterator> const& i)
    {
        return fusion::deref(i.cast());
    }
}}

#endif
