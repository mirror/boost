/*=============================================================================
    Copyright (c) 2001-2006 Joel de Guzman
    Copyright (c) 2006 Dan Marsden

    Distributed under the Boost Software License, Version 1.0. (See accompanying 
    file LICENSE_1_0.txt or copy at http://www.boost.org/LICENSE_1_0.txt)
==============================================================================*/
#if !defined(FUSION_END_IMPL_20060123_2208)
#define FUSION_END_IMPL_20060123_2208

#include <boost/fusion/sequence/view/zip_view/zip_view_iterator_fwd.hpp>
#include <boost/fusion/sequence/intrinsic/end.hpp>
#include <boost/fusion/sequence/intrinsic/begin.hpp>
#include <boost/fusion/sequence/intrinsic/size.hpp>
#include <boost/fusion/sequence/intrinsic/front.hpp>
#include <boost/fusion/iterator/advance.hpp>
#include <boost/fusion/algorithm/transformation/transform.hpp>
#include <boost/type_traits/remove_reference.hpp>
#include <boost/type_traits/is_reference.hpp>
#include <boost/mpl/assert.hpp>
#include <boost/mpl/min.hpp>

namespace boost { namespace fusion {

    struct zip_view_tag;

    namespace detail
    {
        template<typename M>
        struct endpoints
        {
            template<typename SeqRef>
            struct result
            {
                typedef typename remove_reference<SeqRef>::type Seq;
                typedef typename result_of::begin<Seq>::type begin;
                typedef typename result_of::advance<begin, M>::type type;
            };

            template<typename Seq>
            typename result<Seq&>::type
            operator()(Seq& seq) const
            {
                return fusion::advance<M>(fusion::begin(seq));
            }

            template<typename Seq>
            typename result<Seq const&>::type
            operator()(Seq const& seq)
            {
                return fusion::advance<M>(fusion::begin(seq));
            }
        };
    }

    namespace extension
    {
        template<typename Tag>
        struct end_impl;

        template<>
        struct end_impl<zip_view_tag>
        {
            template<typename Sequence>
            struct apply
            {
                typedef zip_view_iterator<
                    typename result_of::transform<typename Sequence::sequences, detail::endpoints<typename Sequence::size> >::type,
                    typename Sequence::category> type;

                static type
                call(Sequence& sequence)
                {
                    return type(
                        fusion::transform(sequence.sequences_, detail::endpoints<typename Sequence::size>()));
                }
            };
        };
    }
}}

#endif
