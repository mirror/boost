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
#include <boost/preprocessor/repetition/repeat.hpp>

#include <boost/mpl/if.hpp>
//#include <boost/mpl/at.hpp>
//#include <boost/mpl/size.hpp>
//#include <boost/mpl/deref.hpp>
//#include <boost/mpl/advance.hpp>
//#include <boost/mpl/distance.hpp>
//#include <boost/mpl/begin_end.hpp>
//#include <boost/mpl/next_prior.hpp>
//#include <boost/mpl/sequence_tag_fwd.hpp>

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
#include <boost/fusion/sequence/view/ext_/segmented_iterator.hpp>

namespace boost { namespace proto
{
    namespace detail
    {
        template<typename Expr, long N>
        struct arg_impl;

    #define BOOST_PROTO_DEFINE_GET_IMPL(z, N, data)\
        template<typename Expr>\
        struct arg_impl<Expr, N>\
        {\
            typedef typename Expr::BOOST_PP_CAT(BOOST_PP_CAT(arg, N), _type) type;\
            \
            static type const &call(Expr const &expr)\
            {\
                return expr.cast().BOOST_PP_CAT(arg, N);\
            }\
        };\
        /**/

        BOOST_PP_REPEAT(BOOST_PROTO_MAX_ARITY, BOOST_PROTO_DEFINE_GET_IMPL, _)

        template<typename Expr, int Pos>
        struct ref_iterator
          : fusion::iterator_base<ref_iterator<Expr, Pos> >
        {
            typedef Expr expr_type;
            typedef mpl::long_<Pos> index;
            typedef fusion::forward_traversal_tag category;
            typedef proto_ref_iterator_tag fusion_tag;

            ref_iterator(Expr expr)
              : expr_(expr)
            {}

            Expr expr_;
        };
    }

    template<long N, typename Expr>
    typename detail::arg_impl<Expr, N>::type const &
    arg_c(Expr const &expr)
    {
        return detail::arg_impl<Expr, N>::call(expr);
    }

}}

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
              : mpl::at<typename Iterator::expr_type::args_type, typename Iterator::index>
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
                typedef typename mpl::at<typename Iterator::expr_type::args_type, typename Iterator::index>::type const &type;

                static type call(Iterator const &iter)
                {
                    return proto::arg_c<Iterator::index::value>(iter.expr_);
                }
            };
        };

        template<typename Tag>
        struct next_impl;

        template<>
        struct next_impl<proto::proto_ref_iterator_tag>
        {
            template<typename Iterator>
            struct apply
            {
                typedef typename Iterator::expr_type expr_type;
                typedef typename Iterator::index index;
                typedef proto::detail::ref_iterator<expr_type, index::value + 1> type;

                static type call(Iterator const &iter)
                {
                    return type(iter.expr_);
                }
            };
        };

        template<typename Tag>
        struct category_of_impl;

        template<>
        struct category_of_impl<proto::proto_ref_tag>
        {
            template<typename Sequence>
            struct apply
            {
                typedef forward_traversal_tag type;
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
                  , typename Expr::expr_type const &
                  , fusion::single_view<typename Expr::expr_type const &>
                >
            {};

            template<typename Expr>
            typename result<Expr>::type operator()(Expr &expr) const
            {
                return typename result<Expr>::type(expr.cast());
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
    }
}}

//namespace boost { namespace mpl
//{
//    template<typename Tag, typename Args, long Arity>
//    struct sequence_tag<proto::basic_expr<Tag, Args, Arity> >
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

//namespace boost { namespace mpl
//{
//    template<typename Tag, typename Args, long Arity>
//    struct sequence_tag<proto::basic_expr<Tag, Args, Arity> >
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
