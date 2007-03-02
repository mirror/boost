/*=============================================================================
    Copyright (c) 2001-2006 Joel de Guzman
    Copyright (c) 2006 Dan Marsden

    Distributed under the Boost Software License, Version 1.0. (See accompanying 
    file LICENSE_1_0.txt or copy at http://www.boost.org/LICENSE_1_0.txt)
==============================================================================*/
#if !defined(FUSION_STRICTEST_TRAVERSAL_20060123_2101)
#define FUSION_STRICTEST_TRAVERSAL_20060123_2101

#include <boost/mpl/or.hpp>
#include <boost/mpl/if.hpp>
#include <boost/mpl/placeholders.hpp>
#include <boost/fusion/support/category_of.hpp>
#include <boost/fusion/sequence/intrinsic/mpl.hpp>
#include <boost/fusion/algorithm/iteration/fold.hpp>
#include <boost/type_traits/remove_reference.hpp>
#include <boost/type_traits/is_same.hpp>

namespace boost { namespace fusion {
    
    struct forward_traversal_tag;
    struct bidirectional_traversal_tag;
    struct random_access_traversal_tag;

    namespace detail
    {
        template<typename Next, typename StrictestSoFar>
        struct strictest_traversal_impl
        {
            typedef StrictestSoFar tag1;
            typedef typename traits::category_of<
                typename remove_reference<Next>::type>::type tag2;

            typedef typename mpl::or_<
                is_same<tag1, fusion::forward_traversal_tag>,
                is_same<tag2, fusion::forward_traversal_tag> >::type 
            has_forward_traversal;

            typedef typename mpl::or_<
                is_same<tag1, fusion::bidirectional_traversal_tag>,
                is_same<tag2, fusion::bidirectional_traversal_tag> >::type
            has_bidirectional_traversal;

            typedef typename mpl::if_<
                has_forward_traversal,
                forward_traversal_tag,
                typename mpl::if_<
                has_bidirectional_traversal,
                bidirectional_traversal_tag,
                random_access_traversal_tag>::type>::type type;
        };

        template<typename Sequence>
        struct strictest_traversal
            : result_of::fold<
            Sequence, fusion::random_access_traversal_tag, 
            strictest_traversal_impl<boost::mpl::_,boost::mpl::_> >
        {};
    }
}}

#endif
