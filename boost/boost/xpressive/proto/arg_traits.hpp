///////////////////////////////////////////////////////////////////////////////
// arg_traits.hpp
//
//  Copyright 2004 Eric Niebler. Distributed under the Boost
//  Software License, Version 1.0. (See accompanying file
//  LICENSE_1_0.txt or copy at http://www.boost.org/LICENSE_1_0.txt)

#ifndef BOOST_PROTO_ARG_TRAITS_HPP_EAN_04_01_2005
#define BOOST_PROTO_ARG_TRAITS_HPP_EAN_04_01_2005

#include <boost/call_traits.hpp>
#include <boost/xpressive/proto/proto_fwd.hpp>

namespace boost { namespace proto
{

    ///////////////////////////////////////////////////////////////////////////////
    // value_type
    //  specialize this to control how user-defined types are stored in the parse tree
    template<typename T>
    struct value_type
    {
        typedef typename boost::call_traits<T>::value_type type;
    };

    template<>
    struct value_type<fusion::void_t>
    {
        typedef fusion::void_t type;
    };

    ///////////////////////////////////////////////////////////////////////////////
    // argument type extractors
    template<typename OpT>
    struct arg_type
    {
        typedef typename OpT::arg_type type;
    };

    template<typename OpT, typename ParamT>
    struct arg_type<op_proxy<OpT, ParamT> >
      : arg_type<OpT>
    {
    };

    ///////////////////////////////////////////////////////////////////////////////
    // argument type extractors
    template<typename OpT>
    struct left_type
    {
        typedef typename OpT::left_type type;
    };

    template<typename OpT, typename ParamT>
    struct left_type<op_proxy<OpT, ParamT> >
      : left_type<OpT>
    {
    };

    ///////////////////////////////////////////////////////////////////////////////
    // argument type extractors
    template<typename OpT>
    struct right_type
    {
        typedef typename OpT::right_type type;
    };

    template<typename OpT, typename ParamT>
    struct right_type<op_proxy<OpT, ParamT> >
      : right_type<OpT>
    {
    };

    ///////////////////////////////////////////////////////////////////////////////
    // tag extractor
    template<typename OpT>
    struct tag_type
    {
        typedef typename OpT::tag_type type;
    };

    template<typename OpT, typename ParamT>
    struct tag_type<op_proxy<OpT, ParamT> >
      : tag_type<OpT>
    {
    };

    ///////////////////////////////////////////////////////////////////////////////
    // arg
    template<typename ArgT, typename TagT>
    inline typename value_type<ArgT>::type const &arg(unary_op<ArgT, TagT> const &op)
    {
        return op.arg;
    }

    template<typename ArgT, typename TagT, typename ParamT>
    inline typename value_type<ArgT>::type const arg(op_proxy<unary_op<ArgT, TagT>, ParamT> const &op)
    {
        return op.cast().arg;
    }

    ///////////////////////////////////////////////////////////////////////////////
    // left
    template<typename LeftT, typename RightT, typename TagT>
    inline typename value_type<LeftT>::type const &left(binary_op<LeftT, RightT, TagT> const &op)
    {
        return op.left;
    }

    template<typename LeftT, typename RightT, typename TagT, typename ParamT>
    inline typename value_type<LeftT>::type const left(op_proxy<binary_op<LeftT, RightT, TagT>, ParamT> const &op)
    {
        return op.cast().left;
    }

    ///////////////////////////////////////////////////////////////////////////////
    // right
    template<typename LeftT, typename RightT, typename TagT>
    inline typename value_type<RightT>::type const &right(binary_op<LeftT, RightT, TagT> const &op)
    {
        return op.right;
    }

    template<typename LeftT, typename RightT, typename TagT, typename ParamT>
    inline typename value_type<RightT>::type const right(op_proxy<binary_op<LeftT, RightT, TagT>, ParamT> const &op)
    {
        return op.cast().right;
    }

}}

#endif
