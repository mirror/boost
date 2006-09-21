/*=============================================================================
    Copyright (c) 2001-2006 Joel de Guzman
    Copyright (c) 2006 Dan Marsden

    Use, modification and distribution is subject to the Boost Software
    License, Version 1.0. (See accompanying file LICENSE_1_0.txt or copy at
    http://www.boost.org/LICENSE_1_0.txt)
==============================================================================*/
#if !defined(FUSION_ZIP_VIEW_23012006_0813)
#define FUSION_ZIP_VIEW_23012006_0813

#include <boost/fusion/support/sequence_base.hpp>
#include <boost/fusion/iterator/equal_to.hpp>
#include <boost/fusion/sequence/view/zip_view/detail/strictest_traversal.hpp>
#include <boost/fusion/sequence/view/zip_view/detail/begin_impl.hpp>
#include <boost/fusion/sequence/view/zip_view/detail/end_impl.hpp>
#include <boost/fusion/sequence/view/zip_view/detail/size_impl.hpp>
#include <boost/fusion/sequence/view/zip_view/detail/at_impl.hpp>
#include <boost/fusion/sequence/view/zip_view/detail/value_at_impl.hpp>
#include <boost/fusion/sequence/conversion/as_vector.hpp>
#include <boost/fusion/algorithm/query/find_if.hpp>
#include <boost/fusion/sequence/intrinsic/end.hpp>
#include <boost/fusion/sequence/intrinsic/size.hpp>
#include <boost/fusion/sequence/intrinsic/mpl.hpp>

#include <boost/mpl/assert.hpp>
#include <boost/mpl/not.hpp>
#include <boost/mpl/placeholders.hpp>
#include <boost/mpl/transform_view.hpp>
#include <boost/mpl/at.hpp>
#include <boost/mpl/find_if.hpp>
#include <boost/mpl/equal_to.hpp>
#include <boost/mpl/bool.hpp>

#include <boost/type_traits/remove_reference.hpp>
#include <boost/type_traits/is_reference.hpp>

namespace boost { namespace fusion {

    namespace detail
    {
        template<typename Sequences>
        struct all_references
            : fusion::result_of::equal_to<typename fusion::result_of::find_if<Sequences, mpl::not_<is_reference<mpl::_> > >::type, typename fusion::result_of::end<Sequences>::type>
        {};

        template<typename Sequences>
        struct all_same_size_impl
        {
            typedef mpl::transform_view<Sequences, fusion::result_of::size<remove_reference<mpl::_> > > sizes;
            typedef typename mpl::at_c<sizes, 0>::type first_size;
            typedef mpl::iterator_range<
                typename mpl::next<typename mpl::begin<sizes>::type>::type,
                typename mpl::end<sizes>::type> remainder;
            typedef typename mpl::find_if<remainder, mpl::not_<is_same<mpl::_, first_size> > >::type found_difference;
            typedef typename is_same<found_difference, typename mpl::end<remainder>::type>::type type;
        };

        template<typename Sequences>
        struct all_same_size
            : all_same_size_impl<Sequences>::type
        {};
    }

    struct zip_view_tag;
    struct fusion_sequence_tag;

    template<typename Sequences>
    struct zip_view : sequence_base< zip_view<Sequences> >
    {
        BOOST_MPL_ASSERT((detail::all_references<Sequences>));
        BOOST_MPL_ASSERT((detail::all_same_size<Sequences>));
        typedef typename detail::strictest_traversal<Sequences>::type category;
        typedef zip_view_tag fusion_tag;
        typedef fusion_sequence_tag tag; // this gets picked up by MPL
        typedef mpl::true_ is_view;
        typedef typename fusion::result_of::as_vector<Sequences>::type sequences;

        zip_view(
            const Sequences& seqs)
            : sequences_(seqs)
        {};

        sequences sequences_;
    };
}}

#endif
