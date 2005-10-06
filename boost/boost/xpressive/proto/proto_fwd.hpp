///////////////////////////////////////////////////////////////////////////////
// proto_fwd.hpp
//
//  Copyright 2004 Eric Niebler. Distributed under the Boost
//  Software License, Version 1.0. (See accompanying file
//  LICENSE_1_0.txt or copy at http://www.boost.org/LICENSE_1_0.txt)

#ifndef BOOST_PROTO_FWD_HPP_EAN_04_01_2005
#define BOOST_PROTO_FWD_HPP_EAN_04_01_2005

#include <boost/utility/enable_if.hpp>
#include <boost/mpl/bool.hpp>
#include <boost/mpl/apply_fwd.hpp>
#include <boost/spirit/fusion/sequence/tuple_forward.hpp>
#include <boost/preprocessor/repetition/enum_params_with_a_default.hpp>

#ifndef BOOST_PROTO_MAX_ARITY
# define BOOST_PROTO_MAX_ARITY FUSION_MAX_TUPLE_SIZE
#endif

namespace boost { namespace proto
{

    ///////////////////////////////////////////////////////////////////////////////
    // Operator tags
    struct unary_tag;
    struct binary_tag;
    struct nary_tag;

    struct noop_tag;
    struct unary_plus_tag;
    struct unary_minus_tag;
    struct unary_star_tag;
    struct complement_tag;
    struct address_of_tag;
    struct logical_not_tag;
    struct pre_inc_tag;
    struct pre_dec_tag;
    struct post_inc_tag;
    struct post_dec_tag;

    struct left_shift_tag;
    struct right_shift_tag;
    struct multiply_tag;
    struct divide_tag;
    struct modulus_tag;
    struct add_tag;
    struct subtract_tag;
    struct less_tag;
    struct greater_tag;
    struct less_equal_tag;
    struct greater_equal_tag;
    struct equal_tag;
    struct not_equal_tag;
    struct logical_or_tag;
    struct logical_and_tag;
    struct bitand_tag;
    struct bitor_tag;
    struct bitxor_tag;
    struct comma_tag;
    struct mem_ptr_tag;

    struct assign_tag;
    struct left_shift_assign_tag;
    struct right_shift_assign_tag;
    struct multiply_assign_tag;
    struct divide_assign_tag;
    struct modulus_assign_tag;
    struct add_assign_tag;
    struct subtract_assign_tag;
    struct bitand_assign_tag;
    struct bitor_assign_tag;
    struct bitxor_assign_tag;
    struct subscript_tag;

    struct function_tag;

    template<typename TagT>
    struct is_unary;

    template<typename TagT>
    struct is_binary;

    template<typename TagT>
    struct is_nary;

    template<typename ArgT, typename OpT>
    struct unary_op;

    template<typename LeftT, typename RightT, typename OpT>
    struct binary_op;

    template<typename OpT, typename ParamT = void>
    struct op_proxy;

    template
    <
        typename FunT
      , BOOST_PP_ENUM_PARAMS_WITH_A_DEFAULT(BOOST_PROTO_MAX_ARITY, typename A, fusion::void_t)
    >
    struct nary_op;

    template<typename OpT, typename ArgT>
    unary_op<ArgT, OpT> const
    make_op(ArgT const &arg);

    template<typename OpT, typename LeftT, typename RightT>
    binary_op<LeftT, RightT, OpT> const
    make_op(LeftT const &left, RightT const &right);

    template<typename ArgT>
    unary_op<ArgT, noop_tag> const
    noop(ArgT const &arg);

    struct op_root;

    template<typename T>
    struct is_proxy;

    template<typename T>
    struct is_op;

    template<typename T, bool IsOpT = is_op<T>::value>
    struct as_op;

    template<typename OpT>
    struct op_base;

    template<typename T>
    struct value_type;

    template<typename OpT>
    struct arg_type;

    template<typename OpT>
    struct left_type;

    template<typename OpT>
    struct right_type;

    template<typename OpT>
    struct tag_type;

    template<typename OpTagT, typename DomainTagT, typename DummyT = void>
    struct compiler;

    template<typename OpTagT, typename DomainTagT, bool RightFirstT = true>
    struct fold_compiler;

    template<typename LambdaT, typename DomainTagT, typename CompilerT = void>
    struct transform_compiler;

    template<typename LambdaT, typename DomainTagT>
    struct branch_compiler;

    template<typename PredicateT, typename IfCompilerT, typename ElseCompilerT>
    struct conditional_compiler;

    template<typename LambdaT, typename MapT>
    struct switch_compiler;

    struct error_compiler;

    struct arg_transform;

    struct left_transform;

    struct right_transform;

    template<typename FirstT, typename SecondT>
    struct compose_transforms;

    template<typename ArgT, typename TagT>
    typename value_type<ArgT>::type const &arg(unary_op<ArgT, TagT> const &op);

    template<typename ArgT, typename TagT, typename ParamT>
    typename value_type<ArgT>::type const arg(op_proxy<unary_op<ArgT, TagT>, ParamT> const &op);

    template<typename LeftT, typename RightT, typename TagT>
    typename value_type<LeftT>::type const &left(binary_op<LeftT, RightT, TagT> const &op);

    template<typename LeftT, typename RightT, typename TagT, typename ParamT>
    typename value_type<LeftT>::type const left(op_proxy<binary_op<LeftT, RightT, TagT>, ParamT> const &op);

    template<typename LeftT, typename RightT, typename TagT>
    typename value_type<RightT>::type const &right(binary_op<LeftT, RightT, TagT> const &op);

    template<typename LeftT, typename RightT, typename TagT, typename ParamT>
    typename value_type<RightT>::type const right(op_proxy<binary_op<LeftT, RightT, TagT>, ParamT> const &op);

    template<typename OpT, typename StateT, typename VisitorT, typename DomainTagT>
    typename lazy_enable_if<
        is_op<OpT>
      , typename compiler<typename tag_type<OpT>::type, DomainTagT>::BOOST_NESTED_TEMPLATE apply
        <
            OpT
          , StateT
          , VisitorT
        >
    >::type const
    compile(OpT const &op, StateT const &state, VisitorT &visitor, DomainTagT tag_type);

}} // namespace boost::proto

#endif
