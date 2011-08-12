/*=============================================================================
    Copyright (c) 2001-2011 Joel de Guzman

    Distributed under the Boost Software License, Version 1.0. (See accompanying
    file LICENSE_1_0.txt or copy at http://www.boost.org/LICENSE_1_0.txt)
==============================================================================*/
#if !defined(FUSION_POP_BACK_09172005_1038)
#define FUSION_POP_BACK_09172005_1038

#include <boost/fusion/view/iterator_range/iterator_range.hpp>
#include <boost/fusion/sequence/intrinsic/begin.hpp>
#include <boost/fusion/sequence/intrinsic/end.hpp>
#include <boost/fusion/sequence/intrinsic/size.hpp>
#include <boost/fusion/sequence/intrinsic/empty.hpp>
#include <boost/fusion/iterator/advance.hpp>

namespace boost { namespace fusion
{
    namespace result_of
    {
        template <typename Sequence>
        struct pop_back
        {
            static int const size = size<Sequence>::value;
            BOOST_STATIC_ASSERT(size > 0);
            typedef typename begin<Sequence>::type begin_type;
            typedef mpl::int_<size-1> end_index;
            typedef typename advance<begin_type, end_index>::type end_type;

            typedef
                iterator_range<begin_type, end_type>
            type;
        };
    }

    template <typename Sequence>
    inline typename result_of::pop_back<Sequence const>::type
    pop_back(Sequence const& seq)
    {
        typedef typename
            result_of::pop_back<Sequence const>::end_index
        end_index;

        typedef typename result_of::pop_back<Sequence const>::type result;
        return result(fusion::begin(seq), fusion::advance<end_index>(fusion::begin(seq)));
    }
}}

#endif

