///////////////////////////////////////////////////////////////////////////////
/// /file op_base.hpp
/// Contains definitions of unary_op/</>, binary_op/</> and nary_op/</>,
/// as well as the is_op/</> and the make_op() helper function.
//
//  Copyright 2004 Eric Niebler. Distributed under the Boost
//  Software License, Version 1.0. (See accompanying file
//  LICENSE_1_0.txt or copy at http://www.boost.org/LICENSE_1_0.txt)

#ifndef BOOST_PROTO_OP_BASE_HPP_EAN_04_01_2005
#define BOOST_PROTO_OP_BASE_HPP_EAN_04_01_2005

#include <boost/ref.hpp>
#include <boost/mpl/if.hpp>
#include <boost/mpl/or.hpp>
#include <boost/preprocessor/arithmetic/inc.hpp>
#include <boost/preprocessor/facilities/intercept.hpp>
#include <boost/preprocessor/punctuation/paren.hpp>
#include <boost/preprocessor/repetition/enum_params.hpp>
#include <boost/preprocessor/repetition/enum_trailing_params.hpp>
#include <boost/preprocessor/repetition/enum_binary_params.hpp>
#include <boost/preprocessor/repetition/enum_trailing_binary_params.hpp>
#include <boost/preprocessor/repetition/repeat.hpp>
#include <boost/preprocessor/repetition/repeat_from_to.hpp>
#include <boost/type_traits/is_same.hpp>
#include <boost/type_traits/remove_reference.hpp>
#include <boost/type_traits/is_base_and_derived.hpp>
#include <boost/xpressive/proto/proto_fwd.hpp>
#include <boost/xpressive/proto/arg_traits.hpp>

#ifdef BOOST_PROTO_FUSION_V2
# include <boost/fusion/support/sequence_base.hpp>
# include <boost/fusion/tuple.hpp>
#else
# include <boost/spirit/fusion/sequence/detail/sequence_base.hpp>
# include <boost/spirit/fusion/sequence/tuple.hpp>
#endif

namespace boost { namespace proto
{

    ///////////////////////////////////////////////////////////////////////////////
    // op_root
    struct op_root
      : fusion::sequence_root // TODO do NOT inherit from sequence_root because of the ADL implications.
    {};

    ///////////////////////////////////////////////////////////////////////////////
    // is_proxy
    template<typename T>
    struct is_proxy
      : mpl::false_
    {};

    template<typename Node, typename Param>
    struct is_proxy<op_proxy<Node, Param> >
      : mpl::true_
    {};

    template<typename T>
    struct is_proxy<T &>
      : is_proxy<T>
    {};

    template<typename T>
    struct is_proxy<T const>
      : is_proxy<T>
    {};

    ///////////////////////////////////////////////////////////////////////////////
    // is_op
    template<typename T>
    struct is_op
      : mpl::or_<is_proxy<T>, is_base_and_derived<op_root, T> >
    {};

    template<typename T>
    struct is_op<T &>
      : is_op<T>
    {};

    template<typename T>
    struct is_op<T const>
      : is_op<T>
    {};

    ///////////////////////////////////////////////////////////////////////////////
    // as_op
    template<typename Node>
    struct as_op<Node, true>
    {
        typedef typename Node::type type;
        typedef typename Node::reference reference;

        static reference make(Node const &node)
        {
            return node.cast();
        }
    };

    template<typename T>
    struct as_op<T, false>
    {
        typedef unary_op<typename call_traits<T>::param_type, noop_tag> type;
        typedef type const reference;

        static reference make(T const &t)
        {
            return type(t);
        }
    };

// These operators must be members.
#define BOOST_PROTO_DEFINE_MEMBER_OPS()                                                         \
    template<typename Arg>                                                                      \
    binary_op<reference, typename as_op<Arg>::reference, assign_tag> const                      \
    operator =(Arg const &arg) const                                                            \
    {                                                                                           \
        return binary_op<reference, typename as_op<Arg>::reference, assign_tag>(                \
            this->cast(), as_op<Arg>::make(arg));                                               \
    }                                                                                           \
    template<typename Arg>                                                                      \
    binary_op<reference, typename as_op<Arg>::reference, subscript_tag> const                   \
    operator [](Arg const &arg) const                                                           \
    {                                                                                           \
        return binary_op<reference, typename as_op<Arg>::reference, subscript_tag>(             \
            this->cast(), as_op<Arg>::make(arg));                                               \
    }                                                                                           \
    nary_op<reference> operator ()() const                                                      \
    {                                                                                           \
        return nary_op<reference>(this->cast());                                                \
    }                                                                                           \
    BOOST_PP_REPEAT_FROM_TO(1, BOOST_PP_INC(BOOST_PROTO_MAX_ARITY), BOOST_PROTO_FUN_OP, _)

#define BOOST_PROTO_AS_OP_FUN(z, n, _)                                                          \
    , as_op<BOOST_PP_CAT(A, n)>::make(BOOST_PP_CAT(a, n))

#define BOOST_PROTO_FUN_OP(z, n, _)                                                             \
    template<BOOST_PP_ENUM_PARAMS_Z(z, n, typename A)>                                          \
    nary_op<reference                                                                           \
        BOOST_PP_ENUM_TRAILING_BINARY_PARAMS_Z(                                                 \
            z, n, typename as_op<A, >::reference BOOST_PP_INTERCEPT)>                           \
    operator ()(BOOST_PP_ENUM_BINARY_PARAMS_Z(z, n, A, const &a)) const                         \
    {                                                                                           \
        return nary_op<reference                                                                \
            BOOST_PP_ENUM_TRAILING_BINARY_PARAMS_Z(                                             \
                z, n, typename as_op<A, >::reference BOOST_PP_INTERCEPT)>                       \
            (this->cast() BOOST_PP_REPEAT_ ## z(n, BOOST_PROTO_AS_OP_FUN, _));                  \
    }

    struct proto_sequence_tag
    {};

    ///////////////////////////////////////////////////////////////////////////////
    // op_base
    template<typename Node>
    struct op_base : op_root
    {
        typedef Node type;
        typedef type const &reference;

        reference cast() const
        {
            return *static_cast<Node const *>(this);
        }

        BOOST_PROTO_DEFINE_MEMBER_OPS()
    };

    ///////////////////////////////////////////////////////////////////////////////
    // unary_op
    template<typename Arg, typename Tag>
    struct unary_op : op_base<unary_op<Arg, Tag> >
    {
        typedef Arg arg_type;
        typedef Tag tag_type;
        typedef proto_sequence_tag fusion_tag;    // for Fusion-2 compatibility
        typedef proto_sequence_tag tag;           // for Fusion-1 compatibility

        arg_type arg;

        unary_op()
          : arg()
        {}

        explicit unary_op(typename call_traits<arg_type>::param_type arg_)
          : arg(arg_)
        {}

        unary_op(unary_op<Arg, Tag> const &that)
          : arg(that.arg)
        {}

        template<typename OtherArg>
        unary_op(unary_op<OtherArg, Tag> const &that)
          : arg(proto::arg(that))
        {}

        using op_base<unary_op>::operator =;
    };

    ///////////////////////////////////////////////////////////////////////////////
    // binary_op
    template<typename Left, typename Right, typename Tag>
    struct binary_op : op_base<binary_op<Left, Right, Tag> >
    {
        typedef Left left_type;
        typedef Right right_type;
        typedef Tag tag_type;
        typedef proto_sequence_tag fusion_tag;    // for Fusion-2 compatibility
        typedef proto_sequence_tag tag;           // for Fusion-1 compatibility

        left_type left;
        right_type right;

        binary_op()
          : left()
          , right()
        {}

        binary_op(
            typename call_traits<Left>::param_type left_
          , typename call_traits<Right>::param_type right_
        )
          : left(left_)
          , right(right_)
        {}

        binary_op(binary_op<Left, Right, Tag> const &that)
          : left(that.left)
          , right(that.right)
        {}

        template<typename OtherLeft, typename OtherRight>
        binary_op(binary_op<OtherLeft, OtherRight, Tag> const &that)
          : left(proto::left(that))
          , right(proto::right(that))
        {}

        using op_base<binary_op>::operator =;
    };

    ///////////////////////////////////////////////////////////////////////////////
    // nary_op
    template<typename Fun, BOOST_PP_ENUM_PARAMS(BOOST_PROTO_MAX_ARITY, typename A)>
    struct nary_op
      : op_base<nary_op<Fun, BOOST_PP_ENUM_PARAMS(BOOST_PROTO_MAX_ARITY, A)> >
    {
        typedef function_tag tag_type;
        typedef proto_sequence_tag fusion_tag;   // for Fusion-2 compatibility
        typedef proto_sequence_tag tag;          // for Fusion-1 compatibility
        typedef Fun functor_type;
        typedef fusion::tuple<
            BOOST_PP_ENUM_PARAMS(BOOST_PROTO_MAX_ARITY, A)
        > args_type;

        functor_type functor;
        args_type args;

        nary_op()
          : functor()
          , args()
        {}

    #define BOOST_PROTO_NARY_OP_CTOR(z, n, _)                                                   \
        nary_op(                                                                                \
            typename call_traits<Fun>::param_type fun                                           \
            BOOST_PP_ENUM_TRAILING_BINARY_PARAMS_Z(z, n, typename call_traits<A, >::param_type a))\
          : functor(fun)                                                                        \
          , args(BOOST_PP_ENUM_PARAMS_Z(z, n, a))                                               \
        {}

        BOOST_PP_REPEAT(BOOST_PP_INC(BOOST_PROTO_MAX_ARITY), BOOST_PROTO_NARY_OP_CTOR, _)

    #undef BOOST_PROTO_NARY_OP_CTOR

        nary_op(nary_op const &that)
          : functor(that.functor)
          , args(that.args)
        {}

        template<typename OtherFun, BOOST_PP_ENUM_PARAMS(BOOST_PROTO_MAX_ARITY, typename O)>
        nary_op(nary_op<OtherFun, BOOST_PP_ENUM_PARAMS(BOOST_PROTO_MAX_ARITY, O)> const &that)
          : functor(that.functor)
          , args(that.args)
        {}

        using op_base<nary_op>::operator =;
    };

    ///////////////////////////////////////////////////////////////////////////////
    // op_proxy
    template<typename Node, typename Param>
    struct op_proxy
    {
        typedef Node type;
        typedef type const reference;
        Param param_;

        Node const cast() const
        {
            return Node(this->param_);
        }

        operator Node const() const
        {
            return this->cast();
        }

        BOOST_PROTO_DEFINE_MEMBER_OPS()
    };

    template<typename Node>
    struct op_proxy<Node, void>
    {
        typedef Node type;
        typedef type const reference;

        Node const cast() const
        {
            return Node();
        }

        operator Node const() const
        {
            return this->cast();
        }

        BOOST_PROTO_DEFINE_MEMBER_OPS()
    };

    ///////////////////////////////////////////////////////////////////////////////
    // make_op (unary)
    template<typename Node, typename Arg>
    unary_op<Arg, Node> const
    make_op(Arg const &arg)
    {
        return unary_op<Arg, Node>(arg);
    }

    template<typename Node, typename Arg>
    unary_op<Arg &, Node> const
    make_op(reference_wrapper<Arg> const &arg)
    {
        return unary_op<Arg &, Node>(arg.get());
    }

    ///////////////////////////////////////////////////////////////////////////////
    // make_op (binary)
    template<typename Node, typename Left, typename Right>
    binary_op<Left, Right, Node> const
    make_op(Left const &left, Right const &right)
    {
        return binary_op<Left, Right, Node>(left, right);
    }

    template<typename Node, typename Left, typename Right>
    binary_op<Left &, Right, Node> const
    make_op(reference_wrapper<Left> const &left, Right const &right)
    {
        return binary_op<Left &, Right, Node>(left.get(), right);
    }

    template<typename Node, typename Left, typename Right>
    binary_op<Left, Right &, Node> const
    make_op(Left const &left, reference_wrapper<Right> const &right)
    {
        return binary_op<Left, Right &, Node>(left, right.get());
    }

    template<typename Node, typename Left, typename Right>
    binary_op<Left &, Right &, Node> const
    make_op(reference_wrapper<Left> const &left, reference_wrapper<Right> const &right)
    {
        return binary_op<Left &, Right &, Node>(left.get(), right.get());
    }

}}

#endif
