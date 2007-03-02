/*=============================================================================
    Copyright (c) 2001-2006 Joel de Guzman
    Copyright (c) 2005-2006 Dan Marsden

    Distributed under the Boost Software License, Version 1.0. (See accompanying 
    file LICENSE_1_0.txt or copy at http://www.boost.org/LICENSE_1_0.txt)
==============================================================================*/
#if !defined(BOOST_FUSION_TAG_OF_31122005_1153)
#define BOOST_FUSION_TAG_OF_31122005_1153

#include <boost/fusion/support/tag_of_fwd.hpp>
#include <boost/fusion/support/detail/is_mpl_sequence.hpp>
#include <boost/utility/enable_if.hpp>

namespace boost { namespace fusion 
{
    struct mpl_sequence_tag;

    namespace traits
    {
        template <typename Sequence>
        struct tag_of<Sequence, typename boost::enable_if<detail::is_mpl_sequence<Sequence> >::type>
        {
            typedef mpl_sequence_tag type;
        };
    }
}}

#endif
