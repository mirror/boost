///////////////////////////////////////////////////////////////////////////////
/// \file proto_fwd.hpp
/// Forward declarations of all of proto's public types and functions.
//
//  Copyright 2004 Eric Niebler. Distributed under the Boost
//  Software License, Version 1.0. (See accompanying file
//  LICENSE_1_0.txt or copy at http://www.boost.org/LICENSE_1_0.txt)

#ifndef BOOST_PROTO_FWD_HPP_EAN_04_01_2005
#define BOOST_PROTO_FWD_HPP_EAN_04_01_2005

#include <boost/type_traits/remove_cv.hpp>
#include <boost/type_traits/remove_reference.hpp>
#include <boost/mpl/long.hpp>
#include <boost/preprocessor/arithmetic/sub.hpp>
#include <boost/preprocessor/repetition/enum_params_with_a_default.hpp>

#ifndef BOOST_PROTO_MAX_ARITY
# define BOOST_PROTO_MAX_ARITY 5
#endif

namespace boost { namespace proto
{
    ///////////////////////////////////////////////////////////////////////////////
    // Operator tags
    namespace tag
    {
        struct unary;
        struct binary;
        struct nary;

        struct terminal;
        struct unary_plus;
        struct unary_minus;
        struct unary_star;
        struct complement;
        struct address_of;
        struct logical_not;
        struct pre_inc;
        struct pre_dec;
        struct post_inc;
        struct post_dec;

        struct left_shift;
        struct right_shift;
        struct multiply;
        struct divide;
        struct modulus;
        struct add;
        struct subtract;
        struct less;
        struct greater;
        struct less_equal;
        struct greater_equal;
        struct equal;
        struct not_equal;
        struct logical_or;
        struct logical_and;
        struct bitwise_and;
        struct bitwise_or;
        struct bitwise_xor;
        struct comma;
        struct mem_ptr;

        struct assign;
        struct left_shift_assign;
        struct right_shift_assign;
        struct multiply_assign;
        struct divide_assign;
        struct modulus_assign;
        struct add_assign;
        struct subtract_assign;
        struct bitwise_and_assign;
        struct bitwise_or_assign;
        struct bitwise_xor_assign;
        struct subscript;

        struct function;
    }

    // for backwards compatibility
    typedef tag::unary unary_type;
    typedef tag::binary binary_tag;
    typedef tag::nary nary_tag;
    typedef tag::terminal terminal_tag;
    typedef tag::unary_plus unary_plus_tag;
    typedef tag::unary_minus unary_minus_tag;
    typedef tag::unary_star unary_star_tag;
    typedef tag::complement complement_tag;
    typedef tag::address_of address_of_tag;
    typedef tag::logical_not logical_not_tag;
    typedef tag::pre_inc pre_inc_tag;
    typedef tag::pre_dec pre_dec_tag;
    typedef tag::post_inc post_inc_tag;
    typedef tag::post_dec post_dec_tag;
    typedef tag::left_shift left_shift_tag;
    typedef tag::right_shift right_shift_tag;
    typedef tag::multiply multiply_tag;
    typedef tag::divide divide_tag;
    typedef tag::modulus modulus_tag;
    typedef tag::add add_tag;
    typedef tag::subtract subtract_tag;
    typedef tag::less less_tag;
    typedef tag::greater greater_tag;
    typedef tag::less_equal less_equal_tag;
    typedef tag::greater_equal greater_equal_tag;
    typedef tag::equal equal_tag;
    typedef tag::not_equal not_equal_tag;
    typedef tag::logical_or logical_or_tag;
    typedef tag::logical_and logical_and_tag;
    typedef tag::bitwise_and bitwise_and_tag;
    typedef tag::bitwise_or bitwise_or_tag;
    typedef tag::bitwise_xor bitwise_xor_tag;
    typedef tag::comma comma_tag;
    typedef tag::mem_ptr mem_ptr_tag;
    typedef tag::assign assign_tag;
    typedef tag::left_shift_assign left_shift_assign_tag;
    typedef tag::right_shift_assign right_shift_assign_tag;
    typedef tag::multiply_assign multiply_assign_tag;
    typedef tag::divide_assign divide_assign_tag;
    typedef tag::modulus_assign modulus_assign_tag;
    typedef tag::add_assign add_assign_tag;
    typedef tag::subtract_assign subtract_assign_tag;
    typedef tag::bitwise_and_assign bitwise_and_assign_tag;
    typedef tag::bitwise_or_assign bitwise_or_assign_tag;
    typedef tag::bitwise_xor_assign bitwise_xor_assign_tag;
    typedef tag::subscript subscript_tag;
    typedef tag::function function_tag;
    typedef bitwise_or_tag bitor_tag;
    typedef bitwise_and_tag bitand_tag;
    typedef bitwise_xor_tag bitxor_tag;
    typedef bitwise_or_assign_tag bitor_assign_tag;
    typedef bitwise_and_assign_tag bitand_assign_tag;
    typedef bitwise_xor_assign_tag bitxor_assign_tag;

    template<typename Tag, typename Args, long Arity = Args::size>
    struct expr;

    template<typename Expr>
    struct ref;

    template<typename OpTag, typename DomainTag, typename EnableIf = void>
    struct compiler;

    template<typename DomainTag>
    struct fold_compiler;

    template<typename DomainTag>
    struct reverse_fold_compiler;

    template<typename Lambda, typename DomainTag, typename Compiler = void>
    struct transform_compiler;

    template<typename Lambda, typename DomainTag>
    struct branch_compiler;

    template<typename Predicate, typename IfCompiler, typename ElseCompiler>
    struct conditional_compiler;

    template<typename Lambda, typename Map>
    struct switch_compiler;

    template<typename DomainTag>
    struct pass_through_compiler;

    struct error_compiler;

    struct identity_transform;

    struct arg_transform;

    struct left_transform;

    struct right_transform;

    template<typename Always>
    struct always_transform;

    template<typename First, typename Second>
    struct compose_transforms;

    template<typename Predicate, typename IfTransform, typename ElseTransform = identity_transform>
    struct conditional_transform;

    template<typename Expr, typename Grammar>
    struct matches;

    template<typename T>
    struct exact;

    template<
        typename Grammar0
      , typename Grammar1
      , BOOST_PP_ENUM_PARAMS_WITH_A_DEFAULT(BOOST_PP_SUB(BOOST_PROTO_MAX_ARITY,2), typename G, void)
    >
    struct or_;

    template<
        typename Grammar0
      , typename Grammar1
      , BOOST_PP_ENUM_PARAMS_WITH_A_DEFAULT(BOOST_PP_SUB(BOOST_PROTO_MAX_ARITY,2), typename G, void)
    >
    struct and_;

    template<typename Pred>
    struct if_;

    template<typename Expr, typename Grammar, typename Return = void>
    struct if_matches;

    template<typename Expr, typename Grammar, typename Return = void>
    struct if_not_matches;

    struct proto_expr_tag;
    struct proto_ref_tag;
    struct proto_ref_iterator_tag;

    template<typename Expr, typename Derived, typename Domain = void>
    struct extends;

    namespace meta
    {
        template<typename T>
        struct value_type
        {
            typedef typename remove_cv<typename remove_reference<T>::type>::type type;
        };

        template<typename T, typename EnableIf = void>
        struct is_ref;

        template<typename T, typename EnableIf = void>
        struct is_expr;

        template<typename T, typename EnableIf = void>
        struct as_expr;

        template<typename T, typename EnableIf = void>
        struct as_expr_ref;

        template<typename Expr, typename State, typename Visitor, typename DomainTag>
        struct compile;

        template<typename Tag, typename Arg>
        struct unary_expr;

        template<typename Tag, typename Left, typename Right>
        struct binary_expr;

        template<typename Expr>
        struct terminal;

        template<typename Expr, typename N = mpl::long_<0> >
        struct arg;

        template<typename Expr, long N>
        struct arg_c;

        template<typename Expr>
        struct left;

        template<typename Expr>
        struct right;

        template<typename Expr>
        struct tag;

        template<typename Expr>
        struct id;

        template<typename Expr>
        struct deep_copy;

        template<typename T>
        struct unref;

        template<typename Expr, typename Fun, long Arity = Expr::arity::value>
        struct eval;

        // Specific expression generators, for convenience
        template<typename T> struct unary_plus;
        template<typename T> struct unary_minus;
        template<typename T> struct unary_star;
        template<typename T> struct complement;
        template<typename T> struct address_of;
        template<typename T> struct logical_not;
        template<typename T> struct pre_inc;
        template<typename T> struct pre_dec;
        template<typename T> struct post_inc;
        template<typename T> struct post_dec;

        template<typename T, typename U> struct left_shift;
        template<typename T, typename U> struct right_shift;
        template<typename T, typename U> struct multiply;
        template<typename T, typename U> struct divide;
        template<typename T, typename U> struct modulus;
        template<typename T, typename U> struct add;
        template<typename T, typename U> struct subtract;
        template<typename T, typename U> struct less;
        template<typename T, typename U> struct greater;
        template<typename T, typename U> struct less_equal;
        template<typename T, typename U> struct greater_equal;
        template<typename T, typename U> struct equal;
        template<typename T, typename U> struct not_equal;
        template<typename T, typename U> struct logical_or;
        template<typename T, typename U> struct logical_and;
        template<typename T, typename U> struct bitwise_and;
        template<typename T, typename U> struct bitwise_or;
        template<typename T, typename U> struct bitwise_xor;
        template<typename T, typename U> struct comma;
        template<typename T, typename U> struct mem_ptr;

        template<typename T, typename U> struct assign;
        template<typename T, typename U> struct left_shift_assign;
        template<typename T, typename U> struct right_shift_assign;
        template<typename T, typename U> struct multiply_assign;
        template<typename T, typename U> struct divide_assign;
        template<typename T, typename U> struct modulus_assign;
        template<typename T, typename U> struct add_assign;
        template<typename T, typename U> struct subtract_assign;
        template<typename T, typename U> struct bitwise_and_assign;
        template<typename T, typename U> struct bitwise_or_assign;
        template<typename T, typename U> struct bitwise_xor_assign;
        template<typename T, typename U> struct subscript;

        template<BOOST_PP_ENUM_PARAMS_WITH_A_DEFAULT(BOOST_PROTO_MAX_ARITY, typename A, void), typename Dummy = void>
        struct function;

        template<typename Domain, typename Expr, typename Tag = typename Expr::tag_type>
        struct generate;
    }

    namespace op
    {
        struct compile;
        struct make_terminal;
        struct left;
        struct right;
        struct as_expr;
        struct as_expr_ref;
        struct unref;
        struct deep_copy;

        template<typename N = mpl::long_<0> >
        struct arg;

        template<long N>
        struct arg_c;
    }

    namespace transform
    {
        template<typename Grammar, typename N = mpl::long_<0> >
        struct arg;

        template<typename Grammar, long N>
        struct arg_c;

        template<typename Grammar>
        struct left;

        template<typename Grammar>
        struct right;

        template<typename Grammar, typename BranchState>
        struct branch;

        template<typename Grammar>
        struct fold;

        template<typename Grammar>
        struct reverse_fold;

        template<typename Grammar>
        struct list;

        template<typename Grammar>
        struct pass_through;

        template<
            typename Type
          , BOOST_PP_ENUM_PARAMS_WITH_A_DEFAULT(BOOST_PROTO_MAX_ARITY, typename Grammar, void)
          , typename Dummy = void
        >
        struct construct;
    }

    namespace trans = transform;

#define BOOST_PROTO_IDENTITY_TRANSFORM()\
    template<typename Expr_, typename State_, typename Visitor_>\
    static typename Expr_::type const &call(Expr_ const &expr_, State_ const &, Visitor_ &)\
    {\
        return expr_.cast();\
    }\
    template<typename Expr_, typename, typename>\
    struct apply\
    {\
        typedef typename Expr_::type type;\
    }

    struct has_identity_transform
    {
        BOOST_PROTO_IDENTITY_TRANSFORM();
    };

    template<typename Grammar>
    struct has_pass_through_transform;

}} // namespace boost::proto

#endif
