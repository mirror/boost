///////////////////////////////////////////////////////////////////////////////
/// \file fusion.hpp
/// Make any Proto parse tree a valid Fusion sequence
//
//  Copyright 2004 Eric Niebler. Distributed under the Boost
//  Software License, Version 1.0. (See accompanying file
//  LICENSE_1_0.txt or copy at http://www.boost.org/LICENSE_1_0.txt)

#ifndef BOOST_PROTO_FUSION_HPP_EAN_04_29_2006
#define BOOST_PROTO_FUSION_HPP_EAN_04_29_2006

#include <boost/xpressive/proto/proto.hpp>

#include <boost/mpl/if.hpp>
#include <boost/mpl/at.hpp>
#include <boost/mpl/size.hpp>
#include <boost/mpl/deref.hpp>
#include <boost/mpl/advance.hpp>
#include <boost/mpl/distance.hpp>
#include <boost/mpl/begin_end.hpp>
#include <boost/mpl/next_prior.hpp>

#include <boost/fusion/support/is_view.hpp>
#include <boost/fusion/support/tag_of_fwd.hpp>
#include <boost/fusion/support/category_of.hpp>
#include <boost/fusion/support/iterator_base.hpp>
#include <boost/fusion/sequence/intrinsic/mpl.hpp>
#include <boost/fusion/sequence/intrinsic.hpp>
#include <boost/fusion/sequence/view/single_view.hpp>
#include <boost/fusion/sequence/view/transform_view.hpp>

#include <boost/fusion/support/ext_/is_segmented.hpp>
#include <boost/fusion/sequence/intrinsic/ext_/segments.hpp>
#include <boost/fusion/sequence/intrinsic/ext_/size_s.hpp>
#include <boost/fusion/sequence/view/ext_/segmented_iterator.hpp>

namespace boost { namespace proto { namespace detail
{
    template<typename Expr, int Pos>
    struct ref_iterator
      : fusion::iterator_base<ref_iterator<Expr, Pos> >
    {
        typedef Expr expr_type;
        typedef mpl::long_<Pos> index;
        typedef fusion::forward_traversal_tag category;
        typedef proto_ref_iterator_tag fusion_tag;

        ref_iterator(Expr const &expr)
          : expr_(expr)
        {}

        Expr expr_;
    };
}}}

namespace boost { namespace fusion
{
    namespace extension
    {
        template<typename Tag>
        struct is_view_impl;

        template<>
        struct is_view_impl<proto::proto_ref_tag>
        {
            template<typename Iterator>
            struct apply
              : mpl::true_
            {};
        };

        template<>
        struct is_view_impl<proto::proto_expr_tag>
        {
            template<typename Iterator>
            struct apply
              : mpl::false_
            {};
        };

        template<typename Tag>
        struct value_of_impl;

        template<>
        struct value_of_impl<proto::proto_ref_iterator_tag>
        {
            template<typename Iterator>
            struct apply
              : proto::meta::arg<typename Iterator::expr_type, typename Iterator::index>
            {};
        };

        template<typename Tag>
        struct deref_impl;

        template<>
        struct deref_impl<proto::proto_ref_iterator_tag>
        {
            template<typename Iterator>
            struct apply
            {
                typedef typename proto::meta::arg<
                    typename Iterator::expr_type
                  , typename Iterator::index
                >::type const &type;

                static type call(Iterator const &iter)
                {
                    return proto::arg<typename Iterator::index>(iter.expr_);
                }
            };
        };

        template<typename Tag>
        struct advance_impl;

        template<>
        struct advance_impl<proto::proto_ref_iterator_tag>
        {
            template<typename Iterator, typename N>
            struct apply
            {
                typedef typename proto::detail::ref_iterator<
                    typename Iterator::expr_type
                  , Iterator::index::value + N::value
                > type;

                static type call(Iterator const &iter)
                {
                    return type(iter.expr_);
                }
            };
        };

        template<typename Tag>
        struct distance_impl;

        template<>
        struct distance_impl<proto::proto_ref_iterator_tag>
        {
            template<typename IteratorFrom, typename IteratorTo>
            struct apply
            {
                typedef mpl::long_<IteratorTo::index::value - IteratorFrom::index::value> type;
            };
        };

        template<typename Tag>
        struct next_impl;

        template<>
        struct next_impl<proto::proto_ref_iterator_tag>
        {
            template<typename Iterator>
            struct apply
              : advance_impl<proto::proto_ref_iterator_tag>::template apply<Iterator, mpl::long_<1> >
            {};
        };

        template<typename Tag>
        struct prior_impl;

        template<>
        struct prior_impl<proto::proto_ref_iterator_tag>
        {
            template<typename Iterator>
            struct apply
              : advance_impl<proto::proto_ref_iterator_tag>::template apply<Iterator, mpl::long_<-1> >
            {};
        };

        template<typename Tag>
        struct category_of_impl;

        template<>
        struct category_of_impl<proto::proto_ref_tag>
        {
            template<typename Sequence>
            struct apply
            {
                typedef random_access_traversal_tag type;
            };
        };

        template<typename Tag>
        struct size_impl;

        template<>
        struct size_impl<proto::proto_ref_tag>
        {
            template<typename Sequence>
            struct apply
            {
                typedef typename Sequence::arity type;
            };
        };

        template<typename Tag>
        struct begin_impl;

        template<>
        struct begin_impl<proto::proto_ref_tag>
        {
            template<typename Sequence>
            struct apply
            {
                typedef proto::detail::ref_iterator<Sequence const, 0> type;

                static type call(Sequence& seq)
                {
                    return type(seq);
                }
            };
        };

        template<typename Tag>
        struct end_impl;

        template<>
        struct end_impl<proto::proto_ref_tag>
        {
            template<typename Sequence>
            struct apply
            {
                typedef proto::detail::ref_iterator<Sequence const, Sequence::arity::value> type;

                static type call(Sequence& seq)
                {
                    return type(seq);
                }
            };
        };

        template<typename Tag>
        struct value_at_impl;

        template<>
        struct value_at_impl<proto::proto_ref_tag>
        {
            template<typename Sequence, typename N>
            struct apply
            {
                typedef typename proto::meta::arg<Sequence, N>::type type;
            };
        };

        template<typename Tag>
        struct at_impl;

        template<>
        struct at_impl<proto::proto_ref_tag>
        {
            template<typename Sequence, typename N>
            struct apply
            {
                typedef typename proto::meta::arg<Sequence, N>::type const &type;

                static type call(Sequence &seq)
                {
                    return proto::arg_c<N::value>(seq);
                }
            };
        };

        template<typename Tag>
        struct is_segmented_impl;

        template<>
        struct is_segmented_impl<proto::proto_expr_tag>
        {
            template<typename Iterator>
            struct apply
              : mpl::true_
            {};
        };

        template<typename Tag>
        struct as_element
        {
            template<typename Expr>
            struct result
              : mpl::if_<
                    is_same<Tag, typename Expr::tag_type>
                  , Expr const &
                  , fusion::single_view<Expr const &>
                >
            {};

            template<typename Expr>
            typename result<Expr>::type
            operator()(Expr &expr) const
            {
                return typename result<Expr>::type(expr);
            }
        };

        template<typename Tag>
        struct segments_impl;

        template<>
        struct segments_impl<proto::proto_expr_tag>
        {
            template<typename Sequence>
            struct apply
            {
                typedef typename Sequence::tag_type tag_type;

                typedef fusion::transform_view<
                    proto::ref<Sequence>
                  , as_element<tag_type>
                > type;

                static type call(Sequence &sequence)
                {
                    proto::ref<Sequence> r = {sequence};
                    return type(r, as_element<tag_type>());
                }
            };
        };

        template<>
        struct category_of_impl<proto::proto_expr_tag>
        {
            template<typename Sequence>
            struct apply
            {
                typedef forward_traversal_tag type;
            };
        };

        template<>
        struct begin_impl<proto::proto_expr_tag>
        {
            template<typename Sequence>
            struct apply
              : fusion::segmented_begin<Sequence>
            {};
        };

        template<>
        struct end_impl<proto::proto_expr_tag>
        {
            template<typename Sequence>
            struct apply
              : fusion::segmented_end<Sequence>
            {};
        };

        template<>
        struct size_impl<proto::proto_expr_tag>
        {
            template<typename Sequence>
            struct apply
              : fusion::segmented_size<Sequence>
            {};
        };
    }
}}

//namespace boost { namespace mpl
//{
    //template<>
    //struct begin_impl<proto::proto_expr_tag>
    //{
    //    template<typename Sequence>
    //    struct apply
    //      : begin_impl<typename sequence_tag<typename Sequence::args_type>::type>
    //            ::template apply<typename Sequence::args_type>
    //    {};
    //};

    //template<>
    //struct end_impl<proto::proto_expr_tag>
    //{
    //    template<typename Sequence>
    //    struct apply
    //      : end_impl<typename sequence_tag<typename Sequence::args_type>::type>
    //            ::template apply<typename Sequence::args_type>
    //    {};
    //};

    //template<>
    //struct size_impl<proto::proto_expr_tag>
    //{
    //    template<typename Sequence>
    //    struct apply
    //    {
    //        typedef typename Sequence::arity type;
    //    };
    //};

    //template<>
    //struct at_impl<proto::proto_expr_tag>
    //{
    //    template<typename Sequence, typename N>
    //    struct apply
    //      : at_impl<typename sequence_tag<typename Sequence::args_type>::type>
    //            ::template apply<typename Sequence::args_type, N>
    //    {};
    //};


    //template<>
    //struct begin_impl<proto::proto_ref_tag>
    //{
    //    template<typename Sequence>
    //    struct apply
    //      : begin_impl<typename sequence_tag<typename Sequence::args_type>::type>
    //            ::template apply<typename Sequence::args_type>
    //    {};
    //};

    //template<>
    //struct end_impl<proto::proto_ref_tag>
    //{
    //    template<typename Sequence>
    //    struct apply
    //      : end_impl<typename sequence_tag<typename Sequence::args_type>::type>
    //            ::template apply<typename Sequence::args_type>
    //    {};
    //};

    //template<>
    //struct size_impl<proto::proto_ref_tag>
    //{
    //    template<typename Sequence>
    //    struct apply
    //    {
    //        typedef typename Sequence::arity type;
    //    };
    //};

    //template<>
    //struct at_impl<proto::proto_ref_tag>
    //{
    //    template<typename Sequence, typename N>
    //    struct apply
    //      : at_impl<typename sequence_tag<typename Sequence::args_type>::type>
    //            ::template apply<typename Sequence::args_type, N>
    //    {};
    //};


//}} // namespace boost::mpl

//namespace boost { namespace mpl
//{
//    template<typename Tag, typename Args, long Arity>
//    struct sequence_tag<proto::expr<Tag, Args, Arity> >
//    {
//        typedef proto::proto_expr_tag type;
//    };
//
//    template<typename Expr>
//    struct sequence_tag<proto::ref<Expr> >
//    {
//        typedef proto::proto_expr_tag type;
//    };
//
//    template<>
//    struct begin_impl<proto::proto_expr_tag>
//    {
//        template<typename Sequence>
//        struct apply
//          : begin_impl<typename sequence_tag<typename Sequence::args_type>::type>
//                ::template apply<typename Sequence::args_type>
//        {};
//    };
//
//    template<>
//    struct end_impl<proto::proto_expr_tag>
//    {
//        template<typename Sequence>
//        struct apply
//          : end_impl<typename sequence_tag<typename Sequence::args_type>::type>
//                ::template apply<typename Sequence::args_type>
//        {};
//    };
//
//    template<>
//    struct size_impl<proto::proto_expr_tag>
//    {
//        template<typename Sequence>
//        struct apply
//        {
//            typedef typename Sequence::arity type;
//        };
//    };
//
//    template<>
//    struct at_impl<proto::proto_expr_tag>
//    {
//        template<typename Sequence, typename N>
//        struct apply
//          : at_impl<typename sequence_tag<typename Sequence::args_type>::type>
//                ::template apply<typename Sequence::args_type, N>
//        {};
//    };
//
//}} // namespace boost::mpl

#endif
