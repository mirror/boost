/*=============================================================================
    Copyright (c) 2001-2006 Joel de Guzman
    Copyright (c) 2006 Dan Marsden

    Use, modification and distribution is subject to the Boost Software
    License, Version 1.0. (See accompanying file LICENSE_1_0.txt or copy at
    http://www.boost.org/LICENSE_1_0.txt)
==============================================================================*/
#if !defined(FUSION_SIZE_IMPL_20060124_0800)
#define FUSION_SIZE_IMPL_20060124_0800

#include <boost/fusion/support/category_of.hpp>
#include <boost/fusion/iterator/deref.hpp>
#include <boost/fusion/iterator/equal_to.hpp>
#include <boost/fusion/sequence/intrinsic/value_at.hpp>
#include <boost/fusion/algorithm/query/find_if.hpp>
#include <boost/mpl/eval_if.hpp>
#include <boost/mpl/placeholders.hpp>
#include <boost/type_traits/is_same.hpp>
#include <boost/type_traits/remove_reference.hpp>

namespace boost { namespace fusion {
    
    struct zip_view_tag;
    struct random_access_iterator_tag;

    namespace detail
    {
        template<typename Sequence>
        struct zip_view_size
        {
            typedef result_of::find_if<
                typename Sequence::sequences, 
                is_same<traits::category_of<remove_reference<mpl::_> >, random_access_iterator_tag> > finder;
            
            typedef typename remove_reference<typename mpl::eval_if<
                result_of::equal_to<typename finder::type, typename result_of::end<typename Sequence::sequences>::type>,
                result_of::value_at_c<typename Sequence::sequences, 0>,
                result_of::deref<typename finder::type> >::type>::type best_sequence;
                
            typedef typename fusion::result_of::size<best_sequence> type;
        };
    }

    namespace extension
    {
        template<typename Sequence>
        struct size;

        template<typename Tag>
        struct size_impl;

        template<>
        struct size_impl<zip_view_tag>
        {
            template<typename Sequence>
            struct apply
                : detail::zip_view_size<Sequence>::type
            {};
        };
    }
}}

#endif
