/*=============================================================================
    Copyright (c) 2001-2006 Joel de Guzman
    Copyright (c) 2006 Dan Marsden

    Distributed under the Boost Software License, Version 1.0. (See accompanying 
    file LICENSE_1_0.txt or copy at http://www.boost.org/LICENSE_1_0.txt)
==============================================================================*/
#if !defined(FUSION_BEGIN_IMPL_20060123_2147)
#define FUSION_BEGIN_IMPL_20060123_2147

#include <boost/fusion/sequence/intrinsic/begin.hpp>
#include <boost/fusion/sequence/view/zip_view/zip_view_iterator_fwd.hpp>
#include <boost/fusion/algorithm/transformation/transform.hpp>
#include <boost/type_traits/remove_reference.hpp>
#include <boost/type_traits/is_reference.hpp>
#include <boost/mpl/assert.hpp>

namespace boost { namespace fusion {

    struct zip_view_tag;

    namespace detail
    {
        struct poly_begin
        {
            template<typename SeqRef>
            struct result
                : result_of::begin<typename remove_reference<SeqRef>::type>
            {
                BOOST_MPL_ASSERT((is_reference<SeqRef>));
            };

            template<typename Seq>
            typename result<Seq&>::type
            operator()(Seq& seq) const
            {
                return fusion::begin(seq);
            }

            template<typename Seq>
            typename result<Seq const&>::type
            operator()(Seq const& seq) const
            {
                return fusion::begin(seq);
            }

        };
    }

    namespace extension
    {
        template<typename Tag>
        struct begin_impl;

        template<>
        struct begin_impl<zip_view_tag>
        {
            template<typename Sequence>
            struct apply
            {
                typedef zip_view_iterator<
                    typename result_of::transform<typename Sequence::sequences, detail::poly_begin>::type,
                    typename Sequence::category> type;

                static type
                call(Sequence& sequence)
                {
                    return type(
                        fusion::transform(sequence.sequences_, detail::poly_begin()));
                }
            };


            
        };
    }
}}

#endif
