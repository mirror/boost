/*=============================================================================
    Copyright (c) 2001-2006 Joel de Guzman

    Use, modification and distribution is subject to the Boost Software
    License, Version 1.0. (See accompanying file LICENSE_1_0.txt or copy at
    http://www.boost.org/LICENSE_1_0.txt)
==============================================================================*/
#if !defined(FUSION_HAS_KEY_09232005_1454)
#define FUSION_HAS_KEY_09232005_1454

#include <boost/mpl/not.hpp>
#include <boost/fusion/support/tag_of.hpp>
#include <boost/type_traits/is_same.hpp>

namespace boost { namespace fusion
{
    struct void_;
    struct fusion_sequence_tag;

    namespace extension
    {
        template <typename Tag>
        struct has_key_impl
        {
            template <typename Sequence, typename Key>
            struct apply
                : mpl::not_<is_same<typename Sequence::
                    template meta_at_impl<Key>::type, void_> >
            {};
        };
    }
    
    namespace result_of
    {
        template <typename Sequence, typename Key>
        struct has_key 
            : extension::has_key_impl<typename detail::tag_of<Sequence>::type>::
                template apply<Sequence, Key>
        {};
    }

    template <typename Key, typename Sequence>
    inline typename result_of::has_key<Sequence, Key>::type
    has_key(Sequence const& seq)
    {
        typedef typename result_of::has_key<Sequence, Key>::type result;
        return result();
    }
}}

#endif

