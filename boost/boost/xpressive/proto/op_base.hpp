///////////////////////////////////////////////////////////////////////////////
// op_base.hpp
//
//  Copyright 2004 Eric Niebler. Distributed under the Boost
//  Software License, Version 1.0. (See accompanying file
//  LICENSE_1_0.txt or copy at http://www.boost.org/LICENSE_1_0.txt)

#ifndef BOOST_PROTO_OP_BASE_HPP_EAN_04_01_2005
#define BOOST_PROTO_OP_BASE_HPP_EAN_04_01_2005

#include <boost/mpl/if.hpp>
#include <boost/mpl/or.hpp>
#include <boost/preprocessor/arithmetic/inc.hpp>
#include <boost/preprocessor/facilities/intercept.hpp>
#include <boost/preprocessor/repetition/enum_params.hpp>
#include <boost/preprocessor/repetition/enum_trailing_params.hpp>
#include <boost/preprocessor/repetition/enum_binary_params.hpp>
#include <boost/preprocessor/repetition/enum_trailing_binary_params.hpp>
#include <boost/preprocessor/repetition/repeat.hpp>
#include <boost/preprocessor/repetition/repeat_from_to.hpp>
#include <boost/type_traits/is_same.hpp>
#include <boost/type_traits/is_base_and_derived.hpp>
#include <boost/spirit/fusion/sequence/tuple.hpp>
#include <boost/xpressive/proto/proto_fwd.hpp>
#include <boost/xpressive/proto/arg_traits.hpp>

namespace boost { namespace proto
{

    ///////////////////////////////////////////////////////////////////////////////
    // op_root
    struct op_root
    {
    };

    ///////////////////////////////////////////////////////////////////////////////
    // is_proxy
    template<typename T>
    struct is_proxy
      : mpl::false_
    {
    };

    template<typename OpT, typename ParamT>
    struct is_proxy<op_proxy<OpT, ParamT> >
      : mpl::true_
    {
    };

    ///////////////////////////////////////////////////////////////////////////////
    // is_op
    template<typename T>
    struct is_op
      : mpl::or_<is_proxy<T>, is_base_and_derived<op_root, T> >
    {
    };

    ///////////////////////////////////////////////////////////////////////////////
    // as_op
    template<typename OpT>
    struct as_op<OpT, true>
    {
        typedef typename OpT::type type;

        static typename mpl::if_<
            is_proxy<OpT>
          , type const
          , type const &
        >::type make(OpT const &op)
        {
            return op.cast();
        }
    };

    template<typename T>
    struct as_op<T, false>
    {
        typedef unary_op<T, noop_tag> type;

        static type const make(T const &t)
        {
            return noop(t);
        }
    };

// These operators must be members.
#define BOOST_PROTO_DEFINE_MEMBER_OPS()                                                         \
    template<typename ArgT>                                                                     \
    binary_op<OpT, typename as_op<ArgT>::type, assign_tag> const                                \
    operator =(ArgT const &arg) const                                                           \
    {                                                                                           \
        return make_op<assign_tag>(this->cast(), as_op<ArgT>::make(arg));                       \
    }                                                                                           \
    template<typename ArgT>                                                                     \
    binary_op<OpT, typename as_op<ArgT>::type, subscript_tag> const                             \
    operator [](ArgT const &arg) const                                                          \
    {                                                                                           \
        return make_op<subscript_tag>(this->cast(), as_op<ArgT>::make(arg));                    \
    }                                                                                           \
    nary_op<OpT> operator ()() const                                                            \
    {                                                                                           \
        return nary_op<OpT>(this->cast());                                                      \
    }                                                                                           \
    BOOST_PP_REPEAT_FROM_TO(1, BOOST_PP_INC(BOOST_PROTO_MAX_ARITY), BOOST_PROTO_FUN_OP, _)

#define BOOST_PROTO_FUN_OP(z, n, _)                                                             \
    template<BOOST_PP_ENUM_PARAMS(n, typename A)>                                               \
    nary_op<OpT BOOST_PP_ENUM_TRAILING_PARAMS(n, A)>                                            \
    operator ()(BOOST_PP_ENUM_BINARY_PARAMS(n, A, const &a)) const                              \
    {                                                                                           \
        return nary_op<OpT BOOST_PP_ENUM_TRAILING_PARAMS(n, A)>                                 \
            (this->cast() BOOST_PP_ENUM_TRAILING_PARAMS(n, a));                                 \
    }

    ///////////////////////////////////////////////////////////////////////////////
    // op_base
    template<typename OpT>
    struct op_base : op_root
    {
        typedef OpT type;

        OpT &cast()
        {
            return *static_cast<OpT *>(this);
        }

        OpT const &cast() const
        {
            return *static_cast<OpT const *>(this);
        }

        BOOST_PROTO_DEFINE_MEMBER_OPS()
    };

    ///////////////////////////////////////////////////////////////////////////////
    // unary_op
    template<typename ArgT, typename OpT>
    struct unary_op : op_base<unary_op<ArgT, OpT> >
    {
        typedef typename value_type<ArgT>::type arg_type;
        typedef OpT tag_type;

        arg_type arg;

        unary_op()
          : arg()
        {}

        explicit unary_op(typename boost::call_traits<ArgT>::param_type arg_)
          : arg(arg_)
        {}

        using op_base<unary_op<ArgT, OpT> >::operator =;
    };

    ///////////////////////////////////////////////////////////////////////////////
    // binary_op
    template<typename LeftT, typename RightT, typename OpT>
    struct binary_op : op_base<binary_op<LeftT, RightT, OpT> >
    {
        typedef typename value_type<LeftT>::type left_type;
        typedef typename value_type<RightT>::type right_type;
        typedef OpT tag_type;

        left_type left;
        right_type right;

        binary_op()
          : left()
          , right()
        {}

        binary_op(
            typename boost::call_traits<LeftT>::param_type left_
          , typename boost::call_traits<RightT>::param_type right_)
          : left(left_)
          , right(right_)
        {}

        using op_base<binary_op<LeftT, RightT, OpT> >::operator =;
    };

    ///////////////////////////////////////////////////////////////////////////////
    // nary_op
    //
    template<typename FunT, BOOST_PP_ENUM_PARAMS(BOOST_PROTO_MAX_ARITY, typename A)>
    struct nary_op
      : op_base<nary_op<FunT, BOOST_PP_ENUM_PARAMS(BOOST_PROTO_MAX_ARITY, A)> >
    {
        typedef function_tag tag_type;
        typedef FunT functor_type;
        typedef fusion::tuple<
            BOOST_PP_ENUM_BINARY_PARAMS(
                BOOST_PROTO_MAX_ARITY, typename value_type<A, >::type BOOST_PP_INTERCEPT)
        > args_type;

        functor_type functor;
        args_type args;

        nary_op()
          : functor()
          , args()
        {}

    #define BOOST_PROTO_NARY_OP_CTOR(z, n, _)                                                   \
        nary_op(                                                                                \
            typename call_traits<FunT>::param_type fun                                          \
            BOOST_PP_ENUM_TRAILING_BINARY_PARAMS(n, typename call_traits<A, >::param_type a))   \
          : functor(fun)                                                                        \
          , args(BOOST_PP_ENUM_PARAMS(n, a))                                                    \
        {}

        BOOST_PP_REPEAT(BOOST_PP_INC(BOOST_PROTO_MAX_ARITY), BOOST_PROTO_NARY_OP_CTOR, _)

    #undef BOOST_PROTO_NARY_OP_CTOR

        using op_base<nary_op<FunT, BOOST_PP_ENUM_PARAMS(BOOST_PROTO_MAX_ARITY, A)> >::operator =;
    };

    ///////////////////////////////////////////////////////////////////////////////
    // op_proxy
    template<typename OpT, typename ParamT>
    struct op_proxy
    {
        typedef OpT type;
        ParamT param_;

        OpT const cast() const
        {
            return OpT(this->param_);
        }

        operator OpT const() const
        {
            return this->cast();
        }

        BOOST_PROTO_DEFINE_MEMBER_OPS()
    };

    template<typename OpT>
    struct op_proxy<OpT, void>
    {
        typedef OpT type;

        OpT const cast() const
        {
            return OpT();
        }

        operator OpT const() const
        {
            return this->cast();
        }

        BOOST_PROTO_DEFINE_MEMBER_OPS()
    };

    ///////////////////////////////////////////////////////////////////////////////
    // make_op
    template<typename OpT, typename ArgT>
    unary_op<ArgT, OpT> const
    make_op(ArgT const &arg)
    {
        return unary_op<ArgT, OpT>(arg);
    }

    ///////////////////////////////////////////////////////////////////////////////
    // make_op
    template<typename OpT, typename LeftT, typename RightT>
    binary_op<LeftT, RightT, OpT> const
    make_op(LeftT const &left, RightT const &right)
    {
        return binary_op<LeftT, RightT, OpT>(left, right);
    }

}}

#endif
