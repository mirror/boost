///////////////////////////////////////////////////////////////////////////////
/// \file fusion.hpp
/// Make any Proto expression a valid Fusion sequence
//
//  Copyright 2007 Eric Niebler. Distributed under the Boost
//  Software License, Version 1.0. (See accompanying file
//  LICENSE_1_0.txt or copy at http://www.boost.org/LICENSE_1_0.txt)

#ifndef BOOST_PROTO_FUSION_HPP_EAN_11_04_2006
#define BOOST_PROTO_FUSION_HPP_EAN_11_04_2006

#include <boost/xpressive/proto/detail/prefix.hpp>
#include <boost/version.hpp>
#include <boost/type_traits/remove_reference.hpp>
#include <boost/mpl/long.hpp>
#if BOOST_VERSION >= 103500
#include <boost/fusion/include/is_view.hpp>
#include <boost/fusion/include/tag_of_fwd.hpp>
#include <boost/fusion/include/category_of.hpp>
#include <boost/fusion/include/iterator_base.hpp>
#include <boost/fusion/include/intrinsic.hpp>
#include <boost/fusion/include/pop_front.hpp>
#include <boost/fusion/include/reverse.hpp>
#include <boost/fusion/include/single_view.hpp>
#include <boost/fusion/include/transform_view.hpp>
#include <boost/fusion/support/ext_/is_segmented.hpp>
#include <boost/fusion/sequence/intrinsic/ext_/segments.hpp>
#include <boost/fusion/sequence/intrinsic/ext_/size_s.hpp>
#include <boost/fusion/view/ext_/segmented_iterator.hpp>
#else
#include <boost/spirit/fusion/sequence/is_sequence.hpp>
#include <boost/spirit/fusion/sequence/begin.hpp>
#include <boost/spirit/fusion/sequence/end.hpp>
#include <boost/spirit/fusion/sequence/at.hpp>
#include <boost/spirit/fusion/sequence/value_at.hpp>
#include <boost/spirit/fusion/sequence/single_view.hpp>
#include <boost/spirit/fusion/sequence/transform_view.hpp>
#include <boost/xpressive/proto/detail/reverse.hpp>
#include <boost/xpressive/proto/detail/pop_front.hpp>
#endif
#include <boost/xpressive/proto/proto_fwd.hpp>
#include <boost/xpressive/proto/traits.hpp>
#include <boost/xpressive/proto/eval.hpp>
#include <boost/xpressive/proto/detail/suffix.hpp>

namespace boost { namespace proto
{

/// INTERNAL ONLY
///
#define UNREF(x) typename boost::remove_reference<x>::type

    namespace detail
    {

        template<typename Expr, long Pos>
        struct expr_iterator
          : fusion::iterator_base<expr_iterator<Expr, Pos> >
        {
            typedef Expr expr_type;
            static long const index = Pos;
            BOOST_PROTO_DEFINE_FUSION_CATEGORY(fusion::random_access_traversal_tag)
            BOOST_PROTO_DEFINE_FUSION_TAG(tag::proto_expr_iterator)

            expr_iterator(Expr const &e)
              : expr(e)
            {}

            Expr const &expr;
        };

    }

    template<typename Expr>
    struct flat_view
    {
        typedef Expr expr_type;
        typedef typename Expr::proto_tag proto_tag;
        BOOST_PROTO_DEFINE_FUSION_CATEGORY(fusion::forward_traversal_tag)
        BOOST_PROTO_DEFINE_FUSION_TAG(tag::proto_flat_view)

        explicit flat_view(Expr &expr)
          : expr_(expr)
        {}

        Expr &expr_;
    };

    namespace functional
    {
        struct flatten
        {
            template<typename Sig>
            struct result {};

            template<typename This, typename Expr>
            struct result<This(Expr)>
            {
                typedef flat_view<UNREF(Expr) const> type;
            };

            template<typename Expr>
            flat_view<Expr const> operator ()(Expr const &expr) const
            {
                return flat_view<Expr const>(expr);
            }
        };

        struct pop_front
        {
            template<typename Sig>
            struct result {};

            template<typename This, typename Expr>
            struct result<This(Expr)>
              : fusion::BOOST_PROTO_FUSION_RESULT_OF::pop_front<UNREF(Expr) const>
            {};

            template<typename Expr>
            typename fusion::BOOST_PROTO_FUSION_RESULT_OF::pop_front<Expr const>::type
            operator ()(Expr const &expr) const
            {
                return fusion::pop_front(expr);
            }
        };

        struct reverse
        {
            template<typename Sig>
            struct result {};

            template<typename This, typename Expr>
            struct result<This(Expr)>
              : fusion::BOOST_PROTO_FUSION_RESULT_OF::reverse<UNREF(Expr) const>
            {};

            template<typename Expr>
            typename fusion::BOOST_PROTO_FUSION_RESULT_OF::reverse<Expr const>::type
            operator ()(Expr const &expr) const
            {
                return fusion::reverse(expr);
            }
        };
    }

    template<>
    struct is_callable<functional::flatten>
      : mpl::true_
    {};

    template<>
    struct is_callable<functional::pop_front>
      : mpl::true_
    {};

    template<>
    struct is_callable<functional::reverse>
      : mpl::true_
    {};

    functional::flatten const flatten = {};

    template<typename Context>
    struct eval_fun
    {
        explicit eval_fun(Context &ctx)
          : ctx_(ctx)
        {}

        template<typename Sig>
        struct result {};

        template<typename This, typename Expr>
        struct result<This(Expr)>
          : proto::result_of::eval<UNREF(Expr), Context>
        {};

        template<typename Expr>
        typename proto::result_of::eval<Expr, Context>::type
        operator ()(Expr &expr) const
        {
            return proto::eval(expr, this->ctx_);
        }

    private:
        Context &ctx_;
    };
}}

namespace boost { namespace fusion
{
    #if BOOST_VERSION < 103500
    template<typename Tag, typename Args, long Arity>
    struct is_sequence<proto::expr<Tag, Args, Arity> >
      : mpl::true_
    {};

    template<typename Tag, typename Args, long Arity>
    struct is_sequence<proto::expr<Tag, Args, Arity> const>
      : mpl::true_
    {};
    #endif

    namespace BOOST_PROTO_FUSION_EXTENSION
    {

        template<typename Tag>
        struct is_view_impl;

        template<>
        struct is_view_impl<proto::tag::proto_flat_view>
        {
            template<typename Iterator>
            struct apply
              : mpl::true_
            {};
        };

        template<>
        struct is_view_impl<proto::tag::proto_expr>
        {
            template<typename Iterator>
            struct apply
              : mpl::false_
            {};
        };

        template<typename Tag>
        struct value_of_impl;

        template<>
        struct value_of_impl<proto::tag::proto_expr_iterator>
        {
            template<typename Iterator>
            struct apply
              : proto::result_of::arg_c<
                    typename Iterator::expr_type
                  , Iterator::index
                >
            {};
        };

        #if BOOST_VERSION < 103500
        template<typename Tag>
        struct value_impl;

        template<>
        struct value_impl<proto::tag::proto_expr_iterator>
          : value_of_impl<proto::tag::proto_expr_iterator>
        {};
        #endif

        template<typename Tag>
        struct deref_impl;

        template<>
        struct deref_impl<proto::tag::proto_expr_iterator>
        {
            template<typename Iterator>
            struct apply
            {
                typedef
                    typename proto::result_of::arg_c<
                        typename Iterator::expr_type const
                      , Iterator::index
                    >::type const &
                type;

                static type call(Iterator const &iter)
                {
                    return proto::arg_c<Iterator::index>(iter.expr);
                }
            };
        };

        template<typename Tag>
        struct advance_impl;

        template<>
        struct advance_impl<proto::tag::proto_expr_iterator>
        {
            template<typename Iterator, typename N>
            struct apply
            {
                typedef
                    typename proto::detail::expr_iterator<
                        typename Iterator::expr_type
                      , Iterator::index + N::value
                    >
                type;

                static type call(Iterator const &iter)
                {
                    return type(iter.expr);
                }
            };
        };

        template<typename Tag>
        struct distance_impl;

        template<>
        struct distance_impl<proto::tag::proto_expr_iterator>
        {
            template<typename IteratorFrom, typename IteratorTo>
            struct apply
              : mpl::long_<IteratorTo::index - IteratorFrom::index>
            {};
        };

        template<typename Tag>
        struct next_impl;

        template<>
        struct next_impl<proto::tag::proto_expr_iterator>
        {
            template<typename Iterator>
            struct apply
              : advance_impl<proto::tag::proto_expr_iterator>::template apply<Iterator, mpl::long_<1> >
            {};
        };

        template<typename Tag>
        struct prior_impl;

        template<>
        struct prior_impl<proto::tag::proto_expr_iterator>
        {
            template<typename Iterator>
            struct apply
              : advance_impl<proto::tag::proto_expr_iterator>::template apply<Iterator, mpl::long_<-1> >
            {};
        };

        #if BOOST_VERSION >= 103500
        template<typename Tag>
        struct category_of_impl;

        template<>
        struct category_of_impl<proto::tag::proto_expr>
        {
            template<typename Sequence>
            struct apply
            {
                typedef random_access_traversal_tag type;
            };
        };
        #endif

        template<typename Tag>
        struct size_impl;

        template<>
        struct size_impl<proto::tag::proto_expr>
        {
            template<typename Sequence>
            struct apply
              : mpl::long_<0 == Sequence::proto_arity::value ? 1 : Sequence::proto_arity::value>
            {};
        };

        template<typename Tag>
        struct begin_impl;

        template<>
        struct begin_impl<proto::tag::proto_expr>
        {
            template<typename Sequence>
            struct apply
            {
                typedef proto::detail::expr_iterator<Sequence, 0> type;

                static type call(Sequence const &seq)
                {
                    return type(seq);
                }
            };
        };

        template<typename Tag>
        struct end_impl;

        template<>
        struct end_impl<proto::tag::proto_expr>
        {
            template<typename Sequence>
            struct apply
            {
                typedef
                    proto::detail::expr_iterator<
                        Sequence
                      , 0 == Sequence::proto_arity::value ? 1 : Sequence::proto_arity::value
                    >
                type;

                static type call(Sequence const &seq)
                {
                    return type(seq);
                }
            };
        };

        template<typename Tag>
        struct value_at_impl;

        template<>
        struct value_at_impl<proto::tag::proto_expr>
        {
            template<typename Sequence, typename Index>
            struct apply
              : proto::result_of::arg_c<Sequence, Index::value>
            {};
        };

        template<typename Tag>
        struct at_impl;

        template<>
        struct at_impl<proto::tag::proto_expr>
        {
            template<typename Sequence, typename Index>
            struct apply
            {
                typedef typename proto::result_of::arg_c<Sequence, Index::value>::type const &type;

                static type call(Sequence &seq)
                {
                    return proto::arg_c<Index::value>(seq);
                }
            };
        };

        #if BOOST_VERSION >= 103500
        template<typename Tag>
        struct is_segmented_impl;

        template<>
        struct is_segmented_impl<proto::tag::proto_flat_view>
        {
            template<typename Iterator>
            struct apply
              : mpl::true_
            {};
        };

        template<typename Tag>
        struct as_element
        {
            template<typename Sig>
            struct result {};

            template<typename This, typename Expr>
            struct result<This(Expr)>
              : mpl::if_<
                    is_same<Tag, UNREF(Expr)::proto_tag>
                  , proto::flat_view<UNREF(Expr) const>
                  , fusion::single_view<UNREF(Expr) const &>
                >
            {};

            template<typename Expr>
            typename result<as_element(Expr const &)>::type
            operator ()(Expr const &expr) const
            {
                return typename result<as_element(Expr const &)>::type(expr);
            }
        };

        template<typename Tag>
        struct segments_impl;

        template<>
        struct segments_impl<proto::tag::proto_flat_view>
        {
            template<typename Sequence>
            struct apply
            {
                typedef typename Sequence::proto_tag proto_tag;

                typedef fusion::transform_view<
                    typename Sequence::expr_type
                  , as_element<proto_tag>
                > type;

                static type call(Sequence &sequence)
                {
                    return type(sequence.expr_, as_element<proto_tag>());
                }
            };
        };

        template<>
        struct category_of_impl<proto::tag::proto_flat_view>
        {
            template<typename Sequence>
            struct apply
            {
                typedef forward_traversal_tag type;
            };
        };

        template<>
        struct begin_impl<proto::tag::proto_flat_view>
        {
            template<typename Sequence>
            struct apply
              : fusion::segmented_begin<Sequence>
            {};
        };

        template<>
        struct end_impl<proto::tag::proto_flat_view>
        {
            template<typename Sequence>
            struct apply
              : fusion::segmented_end<Sequence>
            {};
        };

        template<>
        struct size_impl<proto::tag::proto_flat_view>
        {
            template<typename Sequence>
            struct apply
              : fusion::segmented_size<Sequence>
            {};
        };
        #endif

    }

}}

#undef UNREF

#endif
