// Copyright David Abrahams, Daniel Wallin 2003. Use, modification and 
// distribution is subject to the Boost Software License, Version 1.0. 
// (See accompanying file LICENSE_1_0.txt or copy at 
// http://www.boost.org/LICENSE_1_0.txt)

// This file generates overloads in this format:
//
//     template<class A0, class A1>
//     detail::arg_list<
//         BOOST_DEDUCED_TYPENAME aux::as_tagged_argument<PS0, A0>::type
//       , detail::arg_list<
//             BOOST_DEDUCED_TYPENAME aux::as_tagged_argument<PS1, A1>::type
//         >
//     >
//     operator()(const A0& a0, const A1& a1) const
//     {
//         typedef arg_list<
//             BOOST_DEDUCED_TYPENAME aux::as_tagged_argument<PS0, A0>::type
//           , arg_list<
//                 BOOST_DEDUCED_TYPENAME aux::as_tagged_argument<PS1, A1>::type
//                 ...
//             >
//         > arg_tuple;
//
//         typename aux::as_tagged_argument<PS0, A0>::type tagged0(a0);
//         typename aux::as_tagged_argument<PS1, A1>::type tagged1(a1);
// 
//         return arg_tuple(
//             tagged0
//           , tagged1
//           , aux::void_()
//             ...
//         );
//     }
//

#if !defined(BOOST_PP_IS_ITERATING)
# error Boost.Parameters - do not include this file!
#endif

#define N BOOST_PP_ITERATION()

#define BOOST_PARAMETER_open_list(z, n, text) \
    aux::arg_list< \
        BOOST_DEDUCED_TYPENAME aux::as_tagged_argument< \
            BOOST_PP_CAT(PS, n), BOOST_PP_CAT(A, n) \
        >::type

#define BOOST_PARAMETER_close_list(z, n, text) > 

#define BOOST_PARAMETER_tagged_argument(z, n, text) \
    typename aux::as_tagged_argument< \
        BOOST_PP_CAT(PS, n), BOOST_PP_CAT(A, n) \
    >::type BOOST_PP_CAT(tagged, n)(BOOST_PP_CAT(a, n));

#define BOOST_PARAMETER_arg_list(n) \
    BOOST_PP_ENUM(N, BOOST_PARAMETER_open_list, _) \
    BOOST_PP_REPEAT(N, BOOST_PARAMETER_close_list, _)

template<BOOST_PP_ENUM_PARAMS(N, class A)>
BOOST_PARAMETER_arg_list(N)
operator()(BOOST_PP_ENUM_BINARY_PARAMS(N, A, const& a)) const
{
    typedef BOOST_PARAMETER_arg_list(N) arg_tuple;

    BOOST_PP_REPEAT(N, BOOST_PARAMETER_tagged_argument, _)

    return arg_tuple(
        BOOST_PP_ENUM_PARAMS(N, tagged)
        BOOST_PP_ENUM_TRAILING_PARAMS(
            BOOST_PP_SUB(BOOST_PARAMETER_MAX_ARITY, N)
          , aux::void_() BOOST_PP_INTERCEPT
        ));
}

#undef BOOST_PARAMETER_arg_list
#undef BOOST_PARAMETER_open_list
#undef BOOST_PARAMETER_close_list
#undef BOOST_PARAMETER_tagged_argument
#undef N

